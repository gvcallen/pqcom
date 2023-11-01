#include "PqUnit.h"
#include "Settings.h"

PqUnit* PqUnit::singleton = nullptr;

#define USE_GPS 1

void PqUnit::begin()
{
    gel::Error err;
    
    Serial.begin(BAUD_RATE);
    while (!Serial);
    
    singleton = this;

    // Initialize radio
    if (err = setupRadio())
        handleError(err, "Could not initialize radio.", true);

    // Initialize link
    if (err = setupLink())
        handleError(err, "Could not setup communication link.", true);

    // Initialize GPS
    #if USE_GPS
    if (err = setupGps())
        handleError(err, "Could not initialize GPS.");
    #endif   
    
    // Initialize debug button
    pinMode(BUTTON_P1, INPUT_PULLUP);
    pinMode(BUTTON_P2, OUTPUT);
    digitalWrite(BUTTON_P2, 0);

    Serial.println("System initialized");
}

gel::Error PqUnit::setupLink()
{
    gel::LinkConfig config{};

    config.controller = false;
    if (gel::Error err = link.begin(radio, config))
        return err;

    link.setTelemetryCallback(telemetryCallback);
    link.setTelecommandCallback(telecommandCallback);

    return gel::Error::None;
}

gel::Error PqUnit::setupGps()
{
    gel::GpsPins pins;
    pins.tx = GPS_TX;
    pins.rx = GPS_RX;
    return gps.begin(pins);
}

gel::Error PqUnit::setupRadio()
{
    gel::RadioPins pins{};
    gel::RadioConfig config{};

    pins.nss = RADIO_NSS;
    pins.dio0 = RADIO_DIO0;
    pins.reset = RADIO_RESET;

    return radio.begin(pins, config);
}

void PqUnit::update()
{
    gel::Error err;

    #if USE_GPS
    if (err = gps.update(link.getConfig().transmitInterval - 5))
        handleError(err, "Could not update GPS.");
    #endif

    if (err = link.update())
        handleError(err, "Could not update communication link.");

    updateButton();
}

void PqUnit::updateButton()
{
    int state = digitalRead(BUTTON_P1);

    if (state == prevButtonState)
        return;
    
    if ((millis() - lastBounceTime) > bounceDelay && state == 0)
        handleButtonPress();
    
    lastBounceTime = millis();
    prevButtonState = state;
}

void PqUnit::handleButtonPress()
{
    uint32_t& transmitInterval = link.getConfig().transmitInterval;
    if (transmitInterval < 100)
        transmitInterval = 1000;
    else
        transmitInterval = 0;
}

gel::Error PqUnit::handleTelemetry(gel::span<uint8_t> payload)
{        
    char* payloadStr = (char*)payload.data();
    
    // Body outline
    uint8_t metaData[] =
        "MET:\n"
        "  Num: 000000000\n";
    uint8_t gpsData[] =
        "GPS:\n"
        "  Lat: +00.00000\n"
        "  Lng: +00.00000\n"
        "  Alt: 000000000\n"
        "  Age: 000000000\n";

    const int META_NUM_LENGTH = 9;
    const int GPS_LATLNG_LENGTH = 9; // including plus/minus
    const int GPS_LATLNG_PRECISION = 5;
    const int GPS_ALT_LENGTH = 9;
    const int GPS_AGE_LENGTH = 9;
    
    const int META_NUM_OFFSET = 12;
    const int GPS_LAT_OFFSET = 12;
    const int GPS_LNG_OFFSET = GPS_LAT_OFFSET + GPS_LATLNG_LENGTH + 8;
    const int GPS_ALT_OFFSET = GPS_LNG_OFFSET + GPS_LATLNG_LENGTH + 8;
    const int GPS_AGE_OFFSET = GPS_ALT_OFFSET + GPS_ALT_LENGTH + 8;

    // Populate metadata
    sprintf((char*)(&metaData[META_NUM_OFFSET]), "%09lu", (unsigned long)telemetryCounter);
    metaData[META_NUM_OFFSET + META_NUM_LENGTH] = '\n';
    memcpy(payloadStr, metaData, sizeof(metaData) - 1);
    payloadStr += sizeof(metaData) - 1;

    // Populate gps data
    bool gpsAvailable = gps.getGeoLocation().has_value();
    if (gpsAvailable)
    {
        auto geoLocation = gps.getGeoLocation().value();
        auto age = gps.getGeoLocationAge();
     
        if (geoLocation.lat < 0)
            gpsData[GPS_LAT_OFFSET] = '-';
        if (geoLocation.lng < 0)
            gpsData[GPS_LNG_OFFSET] = '-';

        dtostrf(fabs(geoLocation.lat), GPS_LATLNG_LENGTH - 1, GPS_LATLNG_PRECISION, (char*)&gpsData[GPS_LAT_OFFSET + 1]);
        gpsData[GPS_LAT_OFFSET + GPS_LATLNG_LENGTH] = '\n';
        
        dtostrf(fabs(geoLocation.lng), GPS_LATLNG_LENGTH - 1, GPS_LATLNG_PRECISION, (char*)&gpsData[GPS_LNG_OFFSET + 1]);
        gpsData[GPS_LNG_OFFSET + GPS_LATLNG_LENGTH] = '\n';
        
        sprintf((char*)&gpsData[GPS_ALT_OFFSET], "%09lu", (unsigned long)geoLocation.altitude);
        gpsData[GPS_ALT_OFFSET + GPS_ALT_LENGTH] = '\n';
        
        sprintf((char*)&gpsData[GPS_AGE_OFFSET], "%09lu", (unsigned long)age);
        gpsData[GPS_AGE_OFFSET + GPS_AGE_LENGTH] = '\n';
    
        memcpy(payloadStr, gpsData, sizeof(gpsData) - 1);
        payloadStr += sizeof(gpsData) - 1;
    }

    while (payloadStr != (char*)payload.end())
    {
        *payloadStr = '\0';
        payloadStr++;
    }

    Serial.println((const char*)payload.data());

    telemetryCounter++; 
    return gel::Error::None;
}

gel::Error PqUnit::handleTelecommand(gel::span<uint8_t> command, gel::span<uint8_t> response)
{
    // auto* data = command.data();
    // if (data[0] == 'T' && data[1] == 'M')
        // link.setState(gel::Link::State::Telemetry);
    // else
        // link.setState(gel::Link::State::Telecommand);
    
    memcpy(response.data(), command.data(), command.size_bytes());
    return gel::Error::None;
}

void PqUnit::handleError(gel::Error err, const char* msg, bool critical)
{
    if (msg)
        Serial.println(msg);
    Serial.println(err);
    
    if (critical)
        while (1);
}