// #include <SoftwareSerial.h>
#include <gel.h>

#include "Message.h"

gel::Radio radio;
gel::Link link;

// gel::Gps gps{};
// SoftwareSerial gpsSerial(7, 6);

gel::Error telemetryCallback(gel::span<uint8_t> payload)
{
    char c = 'a';
    for (int i = 0; i < payload.size(); i++)
    {
        payload[i] = c;
        c++;

        if (c > 'z')
            c = 'a';
    }
    payload[payload.size()-1] = '\0';

    return gel::Error::None;
}

gel::Error telecommandCallback(gel::span<uint8_t> command, gel::span<uint8_t> response)
{
    memcpy(response.data(), command.data(), command.size_bytes());
    return gel::Error::None;
}

void handleError(gel::Error err, const __FlashStringHelper* msg = nullptr, bool critical = true)
{
    if (msg)
        Serial.println(msg);
    Serial.println(err);
    
    delay(1000);
    if (critical)
        while (1);
}

gel::Error setupRadio()
{
    gel::RadioPins pins{};
    gel::RadioConfig config{};

    config.modConfig.lora = gel::LoRaConfig{};

    pins.nss = 10;
    pins.dio0 = 2;
    pins.reset = 9;

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
// 
// gel::Error setupGps()
// {
//     gpsSerial.begin(9600);
//     return gps.begin(&gpsSerial);
// }

void setup()
{
    Serial.begin(9600);
    while(!Serial);

    // Initialize radio
    if (gel::Error err = setupRadio())
        handleError(err, F("Could not initialize radio."), true);
    else
        Serial.println(F("Radio initialized."));

    // Initialize link
    if (gel::Error err = setupLink())
        handleError(err, F("Could not setup communication link."), true);
    else
        Serial.println(F("Link initialized."));

    // Initialize GPS
    // if (gel::Error err = setupGps())
        // handleError(err, "Could not initialize GPS.");
    // else
        // Serial.println("GPS initialized.");
}

unsigned long lastPrintTime = 0, printInterval = 1000;
void loop()
{
    // gps.update();
    if (gel::Error err = link.update())
        handleError(err, F("Could not update communication link."));

    if (millis() - lastPrintTime > printInterval)
    {
        lastPrintTime = millis();
        Serial.print("Bit rate = "); Serial.print(link.getDataRate()); Serial.println(" bps");
    }
}