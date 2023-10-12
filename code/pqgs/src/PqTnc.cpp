#include "PqTnc.h"
#include "Suncq.h"

#define EEPROM_HEADER_SIZE                  1

#define EEPROM_OFFSET_HEADER                0
#define EEPROM_OFFSET_FLIGHT_PATH           (EEPROM_HEADER_SIZE)
#define EEPROM_END                          (EEPROM_OFFSET_FLIGHT_PATH + sizeof (FlightPathHeader) + FLIGHT_PATH_MAX_SIZE)

#define FLIGHT_PATH_TRACKING_INTERVAL       1000

#define SERIAL_DEBUG

void PqTnc::begin()
{   
    gel::Error err;
    Serial.begin(BAUD_RATE);
    
    setupEEPROM();
    
    if (err = loadFlightPath())
        handleError(err, "Could not load flight path");
}

void PqTnc::update()
{
    updateSerial();
}

void PqTnc::setupEEPROM()
{
    EEPROM.begin(EEPROM_END);

    // If the EEPROM has never been initialized, we zero it out
    uint8_t notInitialized = EEPROM.readByte(EEPROM_OFFSET_HEADER);
    const uint8_t zero = 0;
    if (notInitialized)
        EEPROM.writeBytes(0, &zero, EEPROM_END);
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
    if (!numPathInstants)
        return gel::Error::None;
    
    // Our header stores the size, in bytes, of the current flight path.
    FlightPathHeader header;
    header.numInstances = numPathInstants * sizeof(gel::GeoInstant);

    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH, &header, sizeof (FlightPathHeader));    
    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH + sizeof(FlightPathHeader), path, header.numInstances * sizeof (gel::GeoInstant));
    
    return gel::Error::None;
}

void PqTnc::updateSerial()
{        
    while (Serial.available())
    {
        uint8_t c = Serial.read();
        
        if (tncMode == suncq::TncMode::Normal)
            updateSerialNormal(c);
        else
            updateSerialKISS(c);
    }
}

void PqTnc::updateSerialNormal(uint8_t c)
{   
    // We use the Invalid command as a NONE command
    gel::Error err;
    if (currentCommand == suncq::Command::Invalid);
        currentCommand = (suncq::Command)c;

    bool commandFinished = true;
    switch (currentCommand)
    {    
        case suncq::Command::Calibrate:
            groundStation->calibrate();
            break;
        
        case suncq::Command::SetTncMode:
            setTncMode((suncq::TncMode)c);
            break;

        case suncq::Command::SetTrackMode:
            setTrackMode((suncq::TrackMode)c);
            break;

        case suncq::Command::SetPathData:
            err = addFlightPathData((uint8_t)c);

            if (err == gel::Error::None)
                commandFinished = false;
            else if (err != gel::Error::Ignored)
                handleError(err);
            break;
        
        case suncq::Command::GetSignalRSSI:
            sendSignalRSSI();
            break;

        case suncq::Command::Reset:
            reset();
            break;

        default:
            break; // Shouldn't get here
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
    switch (trackMode)
    {
        case suncq::TrackMode::None:
            break;

        case suncq::TrackMode::GpsUploaded:
            updateTrackingGPSUploaded();
            // No break

        // case suncq::TrackMode::
    }
}

void PqTnc::updateTrackingGPSUploaded()
{
    // We get the current time, and then run through the path instants to find the next instant
    // after the current one that is past this time. Theoretically, this should be the instant
    // right after the current one, and then the loop should break.
    uint64_t currentSecondsSinceEpoch = groundStation->getCurrentSecondsSinceEpoch();

    gel::GeoInstant& nextPathInstant = path[nextPathInstantIdx];
    if (currentSecondsSinceEpoch < nextPathInstant.secondsSinceEpoch)
        return; // the instant we are heading towards is still the next instant

    // We need to find the latest path instant that has not happened yet
    size_t i;
    for (i = nextPathInstantIdx + 1; i < numPathInstants; i++)
    {
        gel::GeoInstant& testInstant = path[i];
        if (currentSecondsSinceEpoch < testInstant.secondsSinceEpoch)
            break;
    }

    // Update the next path instant and add it to the ground station as a new estimated location
    if (i < numPathInstants)
    {
        gel::GeoInstant& nextInstant = path[i];
        groundStation->addEstimatedLocation(nextInstant);
        nextPathInstantIdx = i;
    }

    return;
}

void PqTnc::setTncMode(suncq::TncMode mode)
{
    tncMode = mode;
}

gel::Error PqTnc::setTrackMode(suncq::TrackMode mode)
{
    if (mode > suncq::TrackMode::SignalStrength)
        mode = suncq::TrackMode::None;
    
    this->trackMode = mode;

    return gel::Error::None;
}

gel::Error PqTnc::addFlightPathData(uint8_t newData)
{
    // First byte in binary stream
    if (flightPathByteIdx == 0)
        numPathInstants = newData << 8;
    else if (flightPathByteIdx == 1)
        numPathInstants += newData << 8;
    else
    {
        size_t flightPathDataByteIdx = flightPathByteIdx - 2;
        bool finished = flightPathDataByteIdx >= numPathInstants * sizeof (gel::GeoInstant);
        if (finished)
        {
            saveFlightPath();
            nextPathInstantIdx = 0;
            flightPathByteIdx = 0;
            receivingByteStream = false;
            return gel::Error::Ignored;
        }
        else
        {
            receivingByteStream = true;
            uint8_t* data = (uint8_t*)path;
            data[flightPathDataByteIdx] = newData;
        }

    }

    flightPathByteIdx++;
    return gel::Error::None;
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

void PqTnc::handleError(gel::Error err, const char* msg)
{

}