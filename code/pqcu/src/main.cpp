#include <gel.h>

gel::Radio radio;

void handleError(gel::Error err, const char* msg = nullptr, bool print = true)
{
    if (print)
    {
        Serial.print(msg);
        Serial.print("Error: ");
        Serial.println(err);
    }

    while (1);
}

void setupRadio()
{
    gel::RadioPins pins;
    gel::RadioConfig config;

    pins.nss = 10;
    pins.dio0 = 2;
    pins.reset = 9;

    Serial.println("Initializing RF...");
    if (gel::Error err = radio.begin(pins, config))
    {
        handleError(err, "Could not begin radio.");
    }
    Serial.println("Initialized successfully.");
}

void setup()
{
    Serial.begin(9600);
  
    setupRadio();
    radio.startReceive();
}

void loop()
{
    if (radio.available() > 0)
    {
        auto msg = radio.readData();
    
        if (!msg.has_value())
        {
            handleError(msg.error(), "Message receive error.");
        }
        else
        {
            auto str = msg.value();
            Serial.print("Received: ");
            Serial.print(msg.value());
            Serial.print(" with RSSI = ");
            Serial.println(radio.getRssi());

            // Delay 100 ms then send message back
            radio.sleep();
            radio.startTransmit("I hear you! " + str);

            while (radio.getState() != gel::Radio::Idle);
            radio.startReceive();
        }
    }

}