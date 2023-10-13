#include "PqTnc.h"
#include "Suncq.h"


// EEPROM storage members
#define EEPROM_SIZE_HEADER                  1
#define EEPROM_SIZE_FLIGHT_PATH             (sizeof (FlightPathHeader) + FLIGHT_PATH_MAX_SIZE)
#define EEPROM_SIZE_SETTINGS                (sizeof (TncSettings))

#define EEPROM_OFFSET_HEADER                0
#define EEPROM_OFFSET_FLIGHT_PATH           (EEPROM_OFFSET_HEADER           + EEPROM_SIZE_HEADER)
#define EEPROM_OFFSET_SETTINGS              (EEPROM_OFFSET_FLIGHT_PATH      + EEPROM_SIZE_FLIGHT_PATH)
#define EEPROM_OFFSET_END                   (EEPROM_OFFSET_SETTINGS         + EEPROM_SIZE_SETTINGS)

#define FLIGHT_PATH_TRACKING_INTERVAL       1000

#define SERIAL_DEBUG

void PqTnc::begin()
{   
    beginEEPROM();
}

void PqTnc::update()
{
    updateSerial();
    updateTracking();
}

void PqTnc::beginEEPROM()
{
    EEPROM.begin(EEPROM_OFFSET_END);

    // If the EEPROM has never been initialized, we zero it out
    uint8_t notInitialized = EEPROM.readByte(EEPROM_OFFSET_HEADER);
    const uint8_t zero = 0;
    if (notInitialized)
        EEPROM.writeBytes(0, &zero, EEPROM_OFFSET_END);

    if (gel::Error err = loadFlightPath())
        handleError(err, "Could not load flight path");
}

gel::Error PqTnc::loadFlightPath()
{
    // Our header stores the size, in bytes, of the current flight path. Can be 0.
    FlightPathHeader header;
    EEPROM.readBytes(EEPROM_OFFSET_FLIGHT_PATH, &header, sizeof (FlightPathHeader));

    // Nothing to load
    if (!header.numInstances)
        return gel::Error::None;

    // We store the flight path in a local array
    numPathInstants = header.numInstances;
    EEPROM.readBytes(EEPROM_OFFSET_FLIGHT_PATH + sizeof(FlightPathHeader), path, header.numInstances * sizeof (gel::GeoInstant));

    return gel::Error::None;
}

gel::Error PqTnc::saveFlightPath()
{
    nextPathInstantIdx = 0;
    pathByteIdx = 0;

    if (!numPathInstants)
        return gel::Error::None;

    groundStation->addEstimatedLocation(path[0]);
    groundStation->addEstimatedLocation(path[0]);
    
    // Our header stores the size, in bytes, of the current flight path.
    FlightPathHeader header;
    header.numInstances = numPathInstants;

    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH, &header, sizeof (FlightPathHeader));    
    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH + sizeof(FlightPathHeader), path, header.numInstances * sizeof (gel::GeoInstant));

    EEPROM.commit();
    sendMessage("Successfully added " + String(numPathInstants) + " locations");

    return gel::Error::None;
}

void PqTnc::updateSerial()
{        
    while (Serial.available())
    {
        uint8_t c = Serial.read();
        
        if (settings.tncMode == suncq::TncMode::Normal)
            updateSerialNormal(c);
        else
            updateSerialKISS(c);
    }
}

void PqTnc::updateSerialNormal(uint8_t c)
{   
    // We use the Invalid command as a NONE command
    gel::Error err;
    bool commandFinished = true;

    // Handle command byte
    if (currentCommand == suncq::Command::Invalid)
    {
        switch (c)
        {
        case suncq::Command::Calibrate:
            groundStation->calibrate();
            break;
        case suncq::Command::ReturnToStart:
            groundStation->returnToStart();
            break;
        case suncq::Command::ReturnToStow:
            groundStation->returnToStow();
            break;
        case suncq::Command::GetSignalRSSI:
            sendSignalRSSI();
            break;
        case suncq::Command::Reset:
            reset();
            break;
        default:
            currentCommand = (suncq::Command)c;
            commandFinished = false;
            break;
        }
    }
    else // handle data bytes
    {
        switch (currentCommand)
        {    
        case suncq::Command::SetTncMode:
            setTncMode((suncq::TncMode)c);
            break;
        case suncq::Command::SetTrackMode:
            setTrackMode((suncq::TrackMode)c);
            break;
        case suncq::Command::SetPathData:
            commandFinished = addFlightPathData((uint8_t)c);
            break;
        default:
            break; // Shouldn't get here
        }
    }

    if (commandFinished)
        currentCommand = suncq::Command::Invalid;
}

void PqTnc::updateSerialKISS(uint8_t c)
{
    // Not yet implemented
}

void PqTnc::updateTracking()
{
    if (settings.trackMode & suncq::TrackMode::GpsUploaded)
        updateTrackingGPSUploaded();
}

void PqTnc::updateTrackingGPSUploaded()
{
    // We get the current time, and then run through the path instants to find the next instant
    // after the current one that is past this time. Theoretically, this should be the instant
    // right after the current one, and then the loop should break.
    uint64_t currentSecondsSinceEpoch = groundStation->getCurrentSecondsSinceEpoch();
    gel::GeoInstant& nextInstant = path[nextPathInstantIdx];
    
    // Check if we have passed the instant we were heading towards
    if (currentSecondsSinceEpoch > nextInstant.secondsSinceEpoch)
    {
        // Ensure that all path instants that have happened, as well as the next path instant,
        // have been added as an estimated location to the ground station
        for (nextPathInstantIdx += 1; nextPathInstantIdx < numPathInstants; nextPathInstantIdx++)
        {
            gel::GeoInstant& testInstant = path[nextPathInstantIdx];
            groundStation->addEstimatedLocation(testInstant);
            sendMessage(String("Moving towards ")
                        + "Lat = " + String(testInstant.location.lat)           + ", "
                        + "Lng = " + String(testInstant.location.lng)           + ", "
                        + "Alt = " + String(testInstant.location.altitude));

            if (currentSecondsSinceEpoch < testInstant.secondsSinceEpoch) // we have found the next instant
                break;
        }
    }
}

void PqTnc::setTncMode(suncq::TncMode mode)
{
    settings.tncMode = mode;
}

gel::Error PqTnc::setTrackMode(suncq::TrackMode mode)
{
    settings.trackMode = mode;

    sendMessage("Setting tracking mode to " + String(mode));

    return gel::Error::None;
}

// True is returned if we are done receiving data for the flight path
bool PqTnc::addFlightPathData(uint8_t newData)
{
    bool finishedReceiving = false;

    if (pathByteIdx == 0)
    {
        numPathInstants = newData;
        pathByteIdx++;
    }
    else if (pathByteIdx == 1)
    {
        numPathInstants += newData << 8;
        pathByteIdx++;
    }
    else
    {
        ((uint8_t*)path)[pathByteIdx - 2] = newData;

        size_t numExpectedBytes = numPathInstants * sizeof (gel::GeoInstant) + 2;
        if (pathByteIdx == numExpectedBytes - 1)
        {
            saveFlightPath();
            finishedReceiving = true;
        }
        else
        {
            pathByteIdx++;
        }
    }

    return finishedReceiving;
}

void PqTnc::reset()
{

}

void PqTnc::sendAcknowledge()
{
    uint8_t message[2] = {(uint8_t)suncq::Command::TncStatus, (uint8_t)suncq::StatusCode::Acknowledge};
    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::sendSignalRSSI()
{
    uint8_t message[5];

    float rssi = groundStation->getRadio().getRssi();
    
    message[0] = (uint8_t)suncq::Command::SignalRSSI;
    memcpy(message, &rssi, sizeof(rssi));

    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::sendMessage(String msg)
{
    Serial.write((uint8_t)suncq::Command::TncMessage);
    Serial.println(msg);
}

void PqTnc::handleError(gel::Error err, const char* msg)
{

}
