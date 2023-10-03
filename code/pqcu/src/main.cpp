#include <SoftwareSerial.h>

#include <gel.h>

gel::Radio radio{};
gel::Link link{};
gel::Gps gps{};
SoftwareSerial gpsSerial(7, 6);

gel::Error streamingCallback(gel::span<uint8_t> payload)
{
    static size_t streamMsg = 0;
    
    String msg = "Hello" + String(streamMsg);
    strcpy((char*)payload.data(), msg.c_str());

    streamMsg++;

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

    link.setStreamingCallback(streamingCallback);

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
    gps.update();
    link.update();

    // i

    // if (radio.available() > 0)
    // {
    //     auto msg = radio.readData();
    // 
    //     if (!msg.has_value())
    //     {
    //         handleError(msg.error(), "Message receive error.");
    //     }
    //     else
    //     {
    //         auto str = msg.value();
    //         Serial.print("Received: ");
    //         Serial.print(str);
    //         Serial.print(" with RSSI = ");
    //         Serial.println(radio.getRssi());
// 
    //         // Delay 100 ms then send message back
    //         radio.startTransmit("I hear you! Got " + str);
    //         delay(1000);
// 
    //         while (!(radio.getState() == gel::Radio::Idle));
    //         radio.startReceive();
    //     }
    // }

}