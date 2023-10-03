#include <Arduino.h>

#include "gel.h"

// Objects
gel::Radio radio;
gel::Imu imu;
// gel::Mount mount;
gel::StepperMotor azMotor;
gel::StepperMotor elMotor;

void handleError(gel::Error err, const char* msg = nullptr, bool print = true)
{
    if (print)
    {
        if (msg)
            Serial.print(msg);
        Serial.println(err);
    }

    while (1);
}

void setupRadio()
{
    gel::RadioPins pins;
    gel::RadioConfig config;

    pins.nss = 27;
    pins.dio0 = 15;
    pins.reset = 13;

    // TODO: Fix this.
    config.modConfig.lora = gel::LoRaConfig{};
    config.modType = gel::ModulationType::LoRa;
    // config.modConfig.fsk = gel::FSKConfig{};
    // config.modType = gel::ModulationType::FSK;

    Serial.println("Initializing RF...");
    if (gel::Error err = radio.begin(pins, config))
    {
        handleError(err, "Could not begin radio.");
    }
    Serial.println("Initialized successfully.");
}

// void setupImu()
// {
    // gel::ImuPins pins;
    // pins.miso = MISO;
    // pins.mosi = MOSI;
    // pins.sck = SCK;
    // pins.nss = 22;
    // pins.interrupt = 39;

    // SPI.begin();

    // imu.begin(pins);
// }

void setupMount()
{
    gel::StepperMotorPins azimuthalPins {};
    gel::StepperMotorPins elevationPins {};
    gel::StepperMotorConfig azimuthalConfig {};
    gel::StepperMotorConfig elevationConfig {};

    azimuthalPins.i01 = 14;
    azimuthalPins.i02 = 26;
    azimuthalPins.i11 = 12;
    azimuthalPins.i12 = 25;
    azimuthalPins.ph1 = 32;
    azimuthalPins.ph2 = 33;

    elevationPins.i01 = 0;
    elevationPins.i02 = 2;
    elevationPins.i11 = 3;
    elevationPins.i12 = 4;
    elevationPins.ph1 = 21;
    elevationPins.ph2 = 5;

    elevationConfig.reverseDirection = true;
    elevationConfig.stepRange = 1200;

    azMotor.begin(azimuthalPins, azimuthalConfig);
    elMotor.begin(elevationPins, elevationConfig);

    azMotor.setSpeed(0.1);
    unsigned int numSteps = 0;

    // AZ CALCULATIONS
    float ratio = 4.0/3.0;
    
    float azSteps = 90.0;
    float elSteps = azSteps * ratio; // 240

    // -1.7, 0.5
    
    azMotor.setSpeed(0.001);
    elMotor.setSpeed(0.001);
    elMotor.enableFullStepping(3.0/3.0);
    azMotor.enableFullStepping(3.0/3.0);
    delay(5000);
    
    azMotor.stepForward(azSteps);
    delay(1000);
    elMotor.stepForward(azSteps*ratio);
    
    // mount.begin(elevationPins, azimuthalPins);
}

void setup()
{
    // setupMount();
    
    Serial.println("Initializing serial...");
    Serial.begin(115200);
    delay(1000);
    Serial.println("Initialized serial.");
    setupRadio();
    // setupImu();

    // delay(1000);
}


const unsigned long MESSAGE_TIMEOUT = 5000;

void loop()
{   
    static bool timeout = true;
    static unsigned long startReceiveTime = 0;
    static size_t messageCounter = 0;

    auto radioState = radio.getState();

    switch (radioState)
    {
    case gel::Radio::Idle:
        // If we are idle, we either have finished transmitting and must start receiving,
        // or must send a new message (either due to timeout or receival of the message)
        if (timeout || (radio.getPrevState() == gel::Radio::Receiving))
        {
            timeout = false;
            delay(1000);

            if (gel::Error err = radio.startTransmit("Hello " + String(messageCounter)))
            {
                handleError(err, "Could not send message.");
                return;
            }

            Serial.println("Sending message #" + String(messageCounter));
            messageCounter++;
        }
        else
        {
            Serial.println("Awaiting response...");
            radio.startReceive();
            startReceiveTime = millis();
        }

        break;

    case gel::Radio::Receiving:
        // If we in receiving state, we need to see if the message is available, or if it timed out
        if (radio.available())
        {
            Serial.println(radio.readData().value_or("Message corrupt"));
            radio.standby();
        }
        else if ((millis() - startReceiveTime) > MESSAGE_TIMEOUT)
        {
            timeout = true;
            Serial.println("Response timed out");
            radio.standby();
        }

    default:
        break;
    }
}