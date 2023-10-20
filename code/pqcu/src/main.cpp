#include "Settings.h"
#include <gel.h>
// #include "Message.h"

gel::Radio radio;
gel::Link link;

gel::Gps gps{};

gel::Error telemetryCallback(gel::span<uint8_t> payload)
{
    auto instantMaybe = gps.getGeoInstant();
    char* dest = (char*)payload.data();
    char* destEnd = dest + payload.size() - 1;
    
    if (instantMaybe.has_value())
    {
        auto instant = instantMaybe.value();

        auto latString = "Lat: " + String(instant.location.lat) + "\n";
        auto longString = "Long: " + String(instant.location.lng) + "\n";
        auto altString = "Alt: " + String(instant.location.altitude) + "\n";
        auto timeString = "Time: " + String((unsigned long)instant.secondsSinceEpoch) + "\n";
        
        memcpy(dest, latString.c_str(), latString.length());
        dest += latString.length();
        memcpy(dest, longString.c_str(), longString.length());
        dest += longString.length();
        memcpy(dest, altString.c_str(), altString.length());
        dest += altString.length();
        memcpy(dest, timeString.c_str(), timeString.length());
        dest += timeString.length();
    }
    
    char c = 'a';
    while (dest != destEnd)
    {
        *dest = c;
        c++;
        dest++;

        if (c > 'z')
            c = 'a';

    }
    *destEnd = '\0';

    return gel::Error::None;
}

gel::Error telecommandCallback(gel::span<uint8_t> command, gel::span<uint8_t> response)
{
    auto* data = command.data();
    if (data[0] == 'T' && data[1] == 'M')
        link.setState(gel::Link::State::Telemetry);
    else
        link.setState(gel::Link::State::Telecommand);
    
    memcpy(response.data(), command.data(), command.size_bytes());
    return gel::Error::None;
}

void handleError(gel::Error err, const __FlashStringHelper* msg = nullptr, bool critical = true)
{
    if (msg)
        Serial.println(msg);
    Serial.println(err);
    
    if (critical)
        while (1);
}

gel::Error setupRadio()
{
    gel::RadioPins pins{};
    gel::RadioConfig config{};

    // config.modConfig.lora = gel::LoRaConfig{};

    pins.nss = RADIO_NSS;
    pins.dio0 = RADIO_DIO0;
    pins.reset = RADIO_RESET;

    return radio.begin(pins, config);
}

gel::Error setupLink()
{
    gel::LinkConfig config{};

    config.controller = false;
    if (gel::Error err = link.begin(radio, config))
        return err;

    link.setTelemetryCallback(telemetryCallback);
    link.setTelecommandCallback(telecommandCallback);

    return gel::Error::None;
}

gel::Error setupGps()
{
    gel::GpsPins pins;
    pins.tx = GPS_TX;
    pins.rx = GPS_RX;
    return gps.begin(pins);
}

void setup()
{
    OSCCAL = OSCCAL_VALUE;
    
    Serial.begin(BAUD_RATE);
    while(!Serial);

    gel::Error err;

    // Initialize radio
    if (err = setupRadio())
        handleError(err, F("Could not initialize radio."), true);

    // Initialize link
    if (err = setupLink())
        handleError(err, F("Could not setup communication link."), true);

    // Initialize GPS
    if (err = setupGps())
        handleError(err, F("Could not initialize GPS."));

    Serial.println("System initialized");
}

void loop()
{
    gel::Error err;

    if (err = gps.update())
        handleError(err, F("Could not update GPS."));

    if (err = link.update())
        handleError(err, F("Could not update communication link."));

    static gel::RunEvery run(1000);
    if (run)
        Serial.println(gps.getLatitude().value());
    // if (run)
        // Serial.println("Bit rate = " + String(link.getDataRate()) + " bps");
}