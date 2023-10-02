#include <Arduino.h>

// #include "Mount.h"
#include "StepperMotor.h"
#include "Radio.h"
// #include "Imu.h"

// Objects
// gel::Mount mount;
gel::StepperMotor azMotor;
gel::StepperMotor elMotor;
gel::Radio radio;
// gel::Imu imu;

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

    pins.nss = 27;
    pins.dio0 = 15;
    pins.reset = 13;

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
    Serial.begin(9600);
    delay(1000);
    Serial.println("Initialized serial.");
    setupRadio();
    // setupImu();

    // delay(1000);
}


size_t counter = 0;
void loop()
{   
    if (gel::Error err = radio.send("Hello " + counter))
    {
        handleError(err, "Could not send message.");
    }
    delay(1000);
}