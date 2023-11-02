#include "PqTnc.h"

#include <Arduino.h>
#include <gel.h>

PqTnc tnc;
gel::Mount mount;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Init");

    gel::MountConfig mountConfig;
    gel::MountPins mountPins;

    mountPins.azimuthalZeroSensor = PIN_AZ_ZERO_SENSOR;
    mountPins.azimuthalPins.i01 = PIN_AZ_IO1;
    mountPins.azimuthalPins.i02 = PIN_AZ_IO2;
    mountPins.azimuthalPins.i11 = PIN_AZ_I11;
    mountPins.azimuthalPins.i12 = PIN_AZ_I12;
    mountPins.azimuthalPins.ph1 = PIN_AZ_PH1;
    mountPins.azimuthalPins.ph2 = PIN_AZ_PH2;
    mountPins.elevationPins.i01 = PIN_EL_IO1;
    mountPins.elevationPins.i02 = PIN_EL_IO2;
    mountPins.elevationPins.i11 = PIN_EL_I11;
    mountPins.elevationPins.i12 = PIN_EL_I12;
    mountPins.elevationPins.ph1 = PIN_EL_PH1;
    mountPins.elevationPins.ph2 = PIN_EL_PH2;

    mountConfig.elevationAngleBounds.min = MOUNT_EL_ANGLE_MIN  * GEL_PI_OVER_180;
    mountConfig.elevationAngleBounds.max = MOUNT_EL_ANGLE_MAX * GEL_PI_OVER_180;
    mountConfig.azelRatio = MOUNT_AZEL_RATIO;
    mountConfig.azimuthalRevolutionNumSteps = MOUNT_AZ_NUM_STEPS;
    mountConfig.elevationRevolutionNumSteps = MOUNT_EL_NUM_STEPS;
    mountConfig.reverseElevationDirection = !MOUNT_EL_START_NEAR_CUTOUT;
    mountConfig.calibrateElevationNearMax = MOUNT_EL_START_NEAR_CUTOUT;

    if (gel::Error err = mount.begin(mountPins, mountConfig))
        Serial.println("Error");

    // mount.calibrate();
    auto elMotor = mount.getElevationMotor();
    auto azMotor = mount.getAzimuthalMotor();

    // elMotor.setMode(gel::StepperMotor::Mode::Holding);
    // azMotor.setMode(gel::StepperMotor::Mode::Holding);

    elMotor.setMode(gel::StepperMotor::Mode::HalfStepping, 1.0);
    azMotor.setMode(gel::StepperMotor::Mode::HalfStepping, 1.0);
    
    // elMotor.stepForward(10000.0);
    // azMotor.stepForward(10000.0);
    Serial.println("Done");
}

// void setup()
// {
    // tnc.begin();
// }

void loop()
{   
    // tnc.update();
}