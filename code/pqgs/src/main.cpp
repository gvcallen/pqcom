#include <Arduino.h>

#include <gel.h>

// Objects
gel::Radio radio{};
gel::Link mylink{};
gel::Imu imu;
gel::Mount mount;
gel::StepperMotor azMotor;
gel::StepperMotor elMotor;

void handleError(gel::Error err, const char* msg = nullptr)
{
    if (msg)
        Serial.print(msg);
    Serial.println(err);

    delay(1000);
    while (1);
}

gel::Error setupRadio()
{
    gel::RadioPins pins;
    gel::RadioConfig config;

    pins.nss = 27;
    pins.dio0 = 15;
    pins.reset = 13;

    config.modConfig.lora = gel::LoRaConfig{};
    config.modType = gel::ModulationType::LoRa;

    return radio.begin(pins, config);
}

gel::Error setupLink()
{
    gel::LinkConfig config{};

    config.controller = true;
    if (gel::Error err = mylink.begin(radio, config))
        return err;

    return gel::Error::None;
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

gel::Error setupMount()
{
    gel::StepperMotorPins azimuthalPins {};
    gel::StepperMotorPins elevationPins {};
    gel::MountConfig mountConfig {};

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

    mountConfig.elevationAngleBounds.min = 40.0  * PI_OVER_180;
    mountConfig.elevationAngleBounds.max = 152.6 * PI_OVER_180;
    mountConfig.gearCorrectionRatio = 1.15;
    mountConfig.azimuthalRevolutionNumSteps = 800.0; // 200 * 60/15
    mountConfig.elevationRevolutionNumSteps = 1610.0; // 200 * 92/20 * 140/80

    if (gel::Error err = mount.begin(elevationPins, azimuthalPins, mountConfig))
        return err;

    if (gel::Error err = mount.calibrate())
        return err;

    while(1)
    {
        delay(2000);
        mount.setElevationAngleDegrees(90.0);
        delay(2000);
        mount.setElevationAngleDegrees(45.0);
    }

    return gel::Error::None;
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Initializing system");

    // Initialize moount
    if (gel::Error err = setupMount())
        handleError(err, "Could not initialize mount.");
    else
        Serial.println("Mount initialized.");

    // // Initialize radio
    // if (gel::Error err = setupRadio())
    //     handleError(err, "Could not initialize radio.");
    // else
    //     Serial.println("Radio initialized.");
    
    // // Initialize link
    // if (gel::Error err = setupLink())
    //     handleError(err, "Could not setup communication link.");
    // else
    //     Serial.println("Link initialized.");
}

void loop()
{   
    // if (radio.available() > 0)
    // {
        // String message = radio.readData().value();
        // Serial.println("Received: " + message);
    // }
}