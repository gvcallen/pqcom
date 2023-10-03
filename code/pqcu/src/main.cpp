#include <SoftwareSerial.h>
#include <gel.h>

#include "Message.h"

gel::Radio radio{};
gel::Link link{};
gel::Gps gps{};
SoftwareSerial gpsSerial(7, 6);

gel::Error telemetryCallback(gel::span<uint8_t> payload)
{
    static size_t streamMsg = 0;
    
    String msg = "Dummy telemetry number #" + String(streamMsg) + "\n";
    strcpy((char*)payload.data(), msg.c_str());

    streamMsg++;

    return gel::Error::None;
}

gel::Error telecommandCallback(gel::span<uint8_t> command, gel::span<uint8_t> response)
{
    String msg = "Responding to " + String((const char*)command.data());
    strcpy((char*)response.data(), msg.c_str());   

    return gel::Error::None;
}

void handleError(gel::Error err, const char* msg = nullptr, bool critical = false)
{
    Serial.print(msg);
    Serial.print("Error: ");
    Serial.println(err);

    while (1);
}

gel::Error setupRadio()
{
    gel::RadioPins pins{};
    gel::RadioConfig config{};

    pins.nss = 10;
    pins.dio0 = 2;
    pins.reset = 9;

    config.modConfig.lora = gel::LoRaConfig{};
    config.modType = gel::ModulationType::LoRa;

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
    gpsSerial.begin(9600);
    return gps.begin(&gpsSerial);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Initialize radio
    if (gel::Error err = setupRadio())
        handleError(err, "Could not initialize radio.", true);
    else
        Serial.println("Radio initialized.");
    
    // Initialize link
    if (gel::Error err = setupLink())
        handleError(err, "Could not setup communication link.", true);
    else
        Serial.println("Link initialized.");
    
    // Initialize GPS
    if (gel::Error err = setupGps())
        handleError(err, "Could not initialize GPS.");
    else
        Serial.println("GPS initialized.");
}

void loop()
{
    // gps.update();
    if (gel::Error err = link.update())
        handleError(err, "Could not setup communication link.", true);
    else
        Serial.println("Link initialized.");
}