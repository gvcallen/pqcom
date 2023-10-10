#include "PqTnc.h"

#define EEPROM_HEADER_SIZE                  1

#define EEPROM_OFFSET_HEADER                0
#define EEPROM_OFFSET_FLIGHT_PATH           (EEPROM_HEADER_SIZE)
#define EEPROM_END                          (EEPROM_OFFSET_FLIGHT_PATH + FLIGHT_PATH_CSV_MAX_SIZE)

void PqTnc::setup()
{
    setupSerial();
    setupEEPROM();
    setupFlightPath();
    setupGroundStation();
}

void PqTnc::update()
{
    updateSerial();
}

void PqTnc::setupSerial()
{
    Serial.begin(BAUD_RATE);
    delay(1000);
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

void PqTnc::setupGroundStation()
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
    config.mount.azimuthalRevolutionNumSteps = MOUNT_AZ_NUM_STEPS; // 200 * 60/15
    config.mount.elevationRevolutionNumSteps = MOUNT_EL_NUM_STEPS; // 200 * 92/20 * 140/80    
    config.mount.reverseElevationDirection = MOUNT_EL_REVERSE_DIRECTION;

    // LINK CONFIG
    config.link.controller = true;
    
    // RADIO PINS
    pins.radio.nss = PIN_RADIO_NSS;
    pins.radio.dio0 = PIN_RADIO_DIO0;
    pins.radio.reset = PIN_RADIO_RESET;

    // IMU PINS
    pins.imu.nss = PIN_IMU_NSS;
    pins.imu.interrupt = PIN_IMU_INT;
    
    Serial.println("Initializing...");

    // BEGIN GROUND STATION
    if (gel::Error err = groundStation.begin(config, pins))
        handleError(err, "Error initializing ground station.");
    else
        Serial.println("Ground station initialized.");

    delay(1000);
}

void PqTnc::setupFlightPath()
{
    // Our header stores the size, in bytes, of the current csv file. Can be 0.
    struct FlightPathHeader
    {
        size_t size;
    } header;

    EEPROM.readBytes(EEPROM_OFFSET_FLIGHT_PATH, &header, sizeof (FlightPathHeader));

    if (!header.size)
        return;
    
    // We store the flight path on a local array
    EEPROM.readBytes(EEPROM_OFFSET_FLIGHT_PATH + sizeof(FlightPathHeader), flightPathCsv, FLIGHT_PATH_CSV_MAX_SIZE);
}

void PqTnc::updateSerial()
{    
    while (Serial.available())
    {
        uint8_t c = Serial.read();
        
        if (tncMode == TncMode::Normal)
            updateSerialNormal(c);
        else
            updateSerialKISS(c);
    }
}

void PqTnc::updateSerialNormal(uint8_t c)
{
    // We use the RESERVED command as a NONE command
    static ProtocolCommand currentCommand = ProtocolCommand::Reserved;
    switch (currentCommand)
    {    
        case ProtocolCommand::Reserved:
            // If and no else as we silently ignore invalid commands
            if (c < (uint8_t)ProtocolCommand::TncStatus)
                currentCommand = ProtocolCommand::Reserved;
            break;
        
        case ProtocolCommand::SetTncMode:
            setTncMode((TncMode)c);
            break;

        case ProtocolCommand::SetTrackMode:
            setTrackingMode((TrackMode)c);
            break;

        case ProtocolCommand::SetPathData:
            updatePathData((uint8_t)c);
            break;
        
        case ProtocolCommand::GetSignalRSSI:
            sendSignalRSSI();
            break;

        case ProtocolCommand::Reset:
            reset();
            break;

        default:
            break; // Shouldn't get here
    }
}

void PqTnc::updateSerialKISS(uint8_t c)
{
    // Not yet implemented
}

void PqTnc::setTncMode(TncMode mode)
{
    tncMode = mode;
}

void PqTnc::setTrackingMode(TrackMode mode)
{
    groundStation.setTrackingMode((gel::TrackingMode)mode);
}

void PqTnc::updatePathData(uint8_t newData)
{

}

void PqTnc::reset()
{

}

void PqTnc::sendAcknowledge()
{
    uint8_t message[2] = {(uint8_t)ProtocolCommand::TncStatus, (uint8_t)StatusCode::Acknowledge};

    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::sendSignalRSSI()
{
    uint8_t message[5];

    float rssi = groundStation.getRadio().getRssi();
    
    message[0] = (uint8_t)ProtocolCommand::SignalRSSI;
    memcpy(message, &rssi, sizeof(rssi));

    Serial.write((const char*)message, sizeof(message));
}

void PqTnc::handleError(gel::Error err, const char* msg)
{
    if (msg)
        Serial.println(msg);
    Serial.println(err);

    while (1);
}