#include "PqTnc.h"
#include "Suncq.h"

PqTnc* PqTnc::singletonTnc = nullptr;

// EEPROM storage members
#define EEPROM_SIZE_HEADER                  1
#define EEPROM_SIZE_FLIGHT_PATH             (sizeof (FlightPathHeader) + FLIGHT_PATH_MAX_SIZE)
#define EEPROM_SIZE_SETTINGS                (sizeof (TncSettings))

#define EEPROM_OFFSET_HEADER                0
#define EEPROM_OFFSET_FLIGHT_PATH           (EEPROM_OFFSET_HEADER           + EEPROM_SIZE_HEADER)
#define EEPROM_OFFSET_SETTINGS              (EEPROM_OFFSET_FLIGHT_PATH      + EEPROM_SIZE_FLIGHT_PATH)
#define EEPROM_OFFSET_END                   (EEPROM_OFFSET_SETTINGS         + EEPROM_SIZE_SETTINGS)

void PqTnc::begin()
{   
    gel::Error err;

    // This is a quick hack to compensate for the mount drive being synchronous.
    // If the mount needs to move too far from one side to the other, the buffer overflows
    // and the commands go out of sync. Ideally we should make the mount async with an update(),
    // but this was not done due to time constraints. With a command coming in once every second,
    // the buffer reaches around 425 when the mount needs to move far, so 10000 should be enough for now.
    Serial.setRxBufferSize(10000);
    Serial.begin(BAUD_RATE);
    while (!Serial);
    delay(500);
    sendMessage("Initialized Serial");
    
    if (err = setupEEPROM())
        handleError(err, "Could not setup EEPROM");

    if (err = setupGroundStation())
        handleError(err, "Could not setup ground station");
    else
        sendMessage("Initialized Ground Station");
    
    PqTnc::singletonTnc = this;  
}

gel::Error PqTnc::setupGroundStation()
{
    gel::GroundStationConfig config;
    gel::GroundStationPins pins;

    // MOUNT PINS
    pins.mount.azimuthalZeroSensor = PIN_AZ_ZERO_SENSOR;
    pins.mount.azimuthalPins.i01 = PIN_AZ_IO1;
    pins.mount.azimuthalPins.i02 = PIN_AZ_IO2;
    pins.mount.azimuthalPins.i11 = PIN_AZ_I11;
    pins.mount.azimuthalPins.i12 = PIN_AZ_I12;
    pins.mount.azimuthalPins.ph1 = PIN_AZ_PH1;
    pins.mount.azimuthalPins.ph2 = PIN_AZ_PH2;
    pins.mount.elevationPins.i01 = PIN_EL_IO1;
    pins.mount.elevationPins.i02 = PIN_EL_IO2;
    pins.mount.elevationPins.i11 = PIN_EL_I11;
    pins.mount.elevationPins.i12 = PIN_EL_I12;
    pins.mount.elevationPins.ph1 = PIN_EL_PH1;
    pins.mount.elevationPins.ph2 = PIN_EL_PH2;

    // MOUNT CONFIG
    config.mount.elevationAngleBounds.min = MOUNT_EL_ANGLE_MIN  * GEL_PI_OVER_180;
    config.mount.elevationAngleBounds.max = MOUNT_EL_ANGLE_MAX * GEL_PI_OVER_180;
    config.mount.azelRatio = MOUNT_AZEL_RATIO;
    config.mount.azimuthalRevolutionNumSteps = MOUNT_AZ_NUM_STEPS;
    config.mount.elevationRevolutionNumSteps = MOUNT_EL_NUM_STEPS;
    config.mount.reverseElevationDirection = !MOUNT_EL_START_NEAR_CUTOUT;
    config.mount.calibrateElevationNearMax = MOUNT_EL_START_NEAR_CUTOUT;

    // LINK CONFIG
    config.link.controller = true;
    
    // RADIO PINS
    pins.radio.nss = PIN_RADIO_NSS;
    pins.radio.dio0 = PIN_RADIO_DIO0;
    pins.radio.reset = PIN_RADIO_RESET;

    // IMU PINS
    pins.imu.nss = PIN_IMU_NSS;

    // GPS PINS
    pins.gps.rx = PIN_GPS_RX;
    pins.gps.tx = PIN_GPS_TX;
    
    // GROUND STATION CONFIG
    config.tracking.estimatedBeamwidth = GEL_RADIANS(GS_ESTIMATED_BEAMWIDTH);
    config.tracking.numBeamwidthScanSegments = GS_NUM_BEAMWIDTH_SCAN_SEGMENTS;
    config.tracking.numAzimuthScanSamples = GS_NUM_AZIMUTH_SCAN_SAMPLES;
    config.tracking.scanTimeout = GS_SCAN_TIMEOUT;
    config.tracking.updateInterval = GS_UPDATE_INTERVAL;
    config.tracking.magneticNorthDeltaAzAngle = GEL_RADIANS(GS_MNORTH_DELTA_AZ);
    config.tracking.mapProjectionOrigin.lat = GS_MAP_PROJECTION_ORIGIN_LAT;
    config.tracking.mapProjectionOrigin.lng = GS_MAP_PROJECTION_ORIGIN_LONG;
    config.tracking.knownLocationTrustTimeout = GS_KNOWN_LOCATION_TRUST_TIMEOUT;

    // Setup
    if (gel::Error err = groundStation.begin(config, pins))
        return err;

    groundStation.getLink().setTelemetryCallback(PqTnc::telemetryCallback);

    return gel::Error::None;
}

gel::Error PqTnc::setupEEPROM()
{
    EEPROM.begin(EEPROM_OFFSET_END);

    // If the EEPROM has never been initialized, we zero it out
    uint8_t notInitialized = EEPROM.readByte(EEPROM_OFFSET_HEADER);
    const uint8_t zero = 0;
    if (notInitialized)
        EEPROM.writeBytes(0, &zero, EEPROM_OFFSET_END);

    if (gel::Error err = loadFlightPath())
        return err;

    return gel::Error::None;
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
    byteStreamIdx = 0;

    if (!numPathInstants)
        return gel::Error::None;

    groundStation.addEstimatedLocation(path[0]);
    groundStation.addEstimatedLocation(path[0]);
    
    // Our header stores the size, in bytes, of the current flight path.
    FlightPathHeader header;
    header.numInstances = numPathInstants;

    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH, &header, sizeof (FlightPathHeader));    
    EEPROM.writeBytes(EEPROM_OFFSET_FLIGHT_PATH + sizeof(FlightPathHeader), path, header.numInstances * sizeof (gel::GeoInstant));

    EEPROM.commit();

    return gel::Error::None;
}

void PqTnc::update()
{
    gel::Error err;
    
    if (err = updateSerial())
        sendError(err);

    auto trackingErrors = updateTracking();
    for (auto& err : trackingErrors)
        sendError(err);
    
    auto gsErrors = groundStation.update();
    for (auto& err : gsErrors)
        sendError(err);
}

gel::Error PqTnc::updateSerial()
{        
    while (Serial.available())
    {
        uint8_t c = Serial.read();
        
        if (settings.tncMode == suncq::TncMode::Normal)
            return updateSerialNormal(c);
        else
            updateSerialKISS(c);
    }

    return gel::Error::None;
}

gel::Error PqTnc::updateSerialNormal(uint8_t c)
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
            sendMessage("Calibrating Ground Station");
            err = groundStation.calibrate();
            sendMessage("Calibration complete");
            break;
        case suncq::Command::ReturnToStart:
            sendMessage("Returning to Start");
            err = groundStation.returnToStart();
            break;
        case suncq::Command::ReturnToStow:
            sendMessage("Returning to Stow");
            err = groundStation.returnToStow();
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
            err = setTncMode((suncq::TncMode)c);
            break;
        case suncq::Command::SetTrackMode:
            err = setTrackMode((suncq::TrackMode)c);
            break;
        case suncq::Command::SetPathData:
            commandFinished = addFlightPathData((uint8_t)c);
            break;
        case suncq::Command::SetTrackTarget:
            // sendMessage(String(c));
            break;
        case suncq::Command::SetTrackLocation:
            commandFinished = addKnownLocationData((uint8_t)c);
            break;
        default:
            break; // Shouldn't get here
        }
    }

    if (commandFinished)
        currentCommand = suncq::Command::Invalid;

    return err;
}

gel::Error PqTnc::updateSerialKISS(uint8_t c)
{
    return gel::Error::NotImplemented;
}

gel::vector<gel::Error, 2> PqTnc::updateTracking()
{
    gel::vector<gel::Error, 2> errors;
    if (settings.trackMode & suncq::TrackMode::GpsReceived)
    {
        if (gel::Error err = updateTrackingGPSReceived())
            errors.push_back(err);
    }
    if (settings.trackMode & suncq::TrackMode::GpsUploaded)
    {
        if (gel::Error err = updateTrackingGPSUploaded())
            errors.push_back(err);
    }

    return errors;
}

gel::Error PqTnc::updateTrackingGPSUploaded()
{
    // We get the current time, and then run through the path instants to find the next instant
    // after the current one that is past this time. Theoretically, this should be the instant
    // right after the current one, and then the loop should break.
    uint64_t currentSecondsSinceEpoch = groundStation.getCurrentSecondsSinceEpoch();
    gel::GeoInstant& nextInstant = path[nextPathInstantIdx];

    // Check if we have passed the instant we were heading towards
    if (currentSecondsSinceEpoch > nextInstant.secondsSinceEpoch)
    {
        // Ensure that all path instants that have happened, as well as the next path instant,
        // have been added as an estimated location to the ground station
        for (nextPathInstantIdx += 1; nextPathInstantIdx < numPathInstants; nextPathInstantIdx++)
        {
            gel::GeoInstant& testInstant = path[nextPathInstantIdx];
            groundStation.addEstimatedLocation(testInstant);
            sendMessage(String("Approaching location in path: ")
                        + "Lat = " + String(testInstant.location.lat)           + ", "
                        + "Lng = " + String(testInstant.location.lng)           + ", "
                        + "Alt = " + String(testInstant.location.altitude));

            if (currentSecondsSinceEpoch < testInstant.secondsSinceEpoch) // we have found the next instant
                break;
        }
    }

    return gel::Error::None;
}

gel::Error PqTnc::updateTrackingGPSReceived()
{
    if (!gpsRecieved)
        return gel::Error::None;;

    // sendMessage("Adding known location to GS");
    return groundStation.addKnownLocation(latestReceivedInstant);
}

gel::Error PqTnc::setTncMode(suncq::TncMode mode)
{
    settings.tncMode = mode;
    return gel::Error::None;
}

gel::Error PqTnc::setTrackMode(suncq::TrackMode mode)
{
    settings.trackMode = mode;

    String modeString;
    switch ((int)mode)
    {
        case (int)suncq::TrackMode::None:
            modeString = "None";
            break;

        case (int)suncq::TrackMode::GpsReceived:
            modeString = "GPS Received";
            break;

        case (int)suncq::TrackMode::GpsUploaded:
            modeString = "GPS Uploaded";
            break;

        case ((int)suncq::TrackMode::GpsUploaded | (int)suncq::TrackMode::GpsReceived):
            modeString = "GPS Uploaded and Recieved";
            break;

        default:
            modeString = "Not Supported";
            break;
    }

    sendMessage("Setting tracking mode to " + String(modeString));

    if (mode & suncq::TrackMode::SignalStrengthInitial)
        return groundStation.scanBruteForce();

    return gel::Error::None;
}

bool PqTnc::addKnownLocationData(uint8_t newData)
{
    if (byteStreamIdx < sizeof (gel::GeoInstant))
        ((uint8_t*)&latestReceivedInstant)[byteStreamIdx] = newData;
    
    byteStreamIdx++;
    if (byteStreamIdx < sizeof (gel::GeoInstant))
    {
        return false;
    }
    else
    {
        byteStreamIdx = 0;

        if (latestReceivedInstant.secondsSinceEpoch == 0)
            latestReceivedInstant.secondsSinceEpoch = groundStation.getCurrentSecondsSinceEpoch();
            
        auto log = String("Adding received location: ")
                 + String("Lat = ") + String(latestReceivedInstant.location.lat) + ", "
                 + String("Lng = ") + String(latestReceivedInstant.location.lng) + ", "
                 + String("Alt = ") + String(latestReceivedInstant.location.altitude) + ", "
                 + String("Sec = ") + String(latestReceivedInstant.secondsSinceEpoch);
        sendMessage(log);

        
        gpsRecieved = true;
        return true;
    }

    return true;
}

// True is returned if we are done receiving data for the flight path
bool PqTnc::addFlightPathData(uint8_t newData)
{
    bool finishedReceiving = false;

    if (byteStreamIdx == 0)
    {
        numPathInstants = newData;
        byteStreamIdx++;
    }
    else if (byteStreamIdx == 1)
    {
        numPathInstants += newData << 8;
        byteStreamIdx++;
    }
    else
    {
        ((uint8_t*)path)[byteStreamIdx - 2] = newData;

        size_t numExpectedBytes = numPathInstants * sizeof (gel::GeoInstant) + 2;
        if (byteStreamIdx == numExpectedBytes - 1)
        {
            saveFlightPath();
            finishedReceiving = true;
            sendMessage("Added " + String(numPathInstants) + " Path Instants");
        }
        else
        {
            byteStreamIdx++;
        }
    }

    return finishedReceiving;
}

void PqTnc::reset()
{
    sendMessage("Resetting System...");
    groundStation.returnToStow();
    #ifdef ESP32
    ESP.restart();
    #endif
    
    // void(* resetFunc) (void) = 0;
    // resetFunc();
}

void PqTnc::sendAcknowledge()
{
    uint8_t message[2] = {(uint8_t)suncq::Command::TncTelemetry, (uint8_t)suncq::StatusCode::Acknowledge};
    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::sendSignalRSSI()
{
    uint8_t message[5];

    float rssi = groundStation.getRadio().getRssi();
    
    message[0] = (uint8_t)suncq::Command::SignalRSSI;
    memcpy(message, &rssi, sizeof(rssi));

    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::sendMessage(String msg)
{
    Serial.write((uint8_t)suncq::Command::TncMessage);
    Serial.print("[PqTnc] ");
    Serial.println(msg.c_str());
}

void PqTnc::sendTelemetry(String msg)
{
    Serial.write((uint8_t)suncq::Command::TncTelemetry);
    Serial.println(msg.c_str());
}

void PqTnc::sendError(gel::Error& err)
{
    Serial.println(err);
}

gel::Error PqTnc::handleTelemetry(gel::span<uint8_t> payload)
{
    String payloadStr{(const char*)payload.data()};
    String log = "";

    // sendMessage("Continuous bit rate = " + String(groundStation.getLink().getDataRate()));
    // sendMessage(String(payload.data(), payload.size()));

    auto numIdx = payloadStr.indexOf("Num: ");
    auto num = payloadStr.substring(numIdx + 5, numIdx + 5 + 9).toInt();
    log = log + "PID = " + String(num) + ", ";

    if (payloadStr.indexOf("GPS") > 0)
    {
        auto latIdx = payloadStr.indexOf("Lat: ");
        auto lngIdx = payloadStr.indexOf("Lng: ");
        auto altIdx = payloadStr.indexOf("Alt: ");
        auto ageIdx = payloadStr.indexOf("Age: ");
        auto lat = payloadStr.substring(latIdx + 5).toFloat();
        auto lng = payloadStr.substring(lngIdx + 5).toFloat();
        auto altitude = payloadStr.substring(altIdx + 5).toFloat();
        auto age = payloadStr.substring(ageIdx + 5).toInt();

        log = log + String("Lat = ") + String(lat) + ", "
                  + String("Lng = ") + String(lng) + ", "
                  + String("Alt = ") + String(altitude) + ", ";

        gpsRecieved = true;
        latestReceivedInstant.location.lat = lat;
        latestReceivedInstant.location.lng = lng;
        latestReceivedInstant.location.altitude = altitude;
        latestReceivedInstant.secondsSinceEpoch = groundStation.getCurrentSecondsSinceEpoch() - age;

        auto gsLocationMaybe = groundStation.getLocation();
        if (gsLocationMaybe.has_value())
        {
            auto gsLocation = gsLocationMaybe.value();
            auto origin = groundStation.getTrackingConfig().mapProjectionOrigin;
            
            auto gsLocationCart = gsLocation.toCartesian(origin);
            auto pqLocationCart = latestReceivedInstant.location.toCartesian(origin);

            auto deltaVec = pqLocationCart - gsLocationCart;
            float distance = gel::length(deltaVec);

            // sendMessage("Calculated distance = " + String(distance / 1000.0) + " km");
            log = log + "Dist = " + String(distance / 1000.0) + " km, ";
        }
    }

    log = log + "RSSI = " + String(groundStation.getRadio().getRssi()) + ", ";
    log = log + "SNR = " + String(groundStation.getRadio().getSNR()) + ", ";
    log = log + "CBR = " + String(groundStation.getLink().getDataRate()) + " bps";
    sendTelemetry(log);
    // sendMessage("RSSI = " + String(groundStation.getRadio().getRssi()));
    // sendMessage("SNR = " + String(groundStation.getRadio().getSNR()));

    return gel::Error::None;
}

void PqTnc::handleError(gel::Error err, const char* msg)
{
    sendMessage(msg);
}
