#include "PqTnc.h"

#include <Arduino.h>
#include <gel.h>

PqTnc tnc;
gel::GroundStation groundStation;

gel::Error setupGroundStation()
{
    gel::GroundStationConfig config;
    gel::GroundStationPins pins;

    // MOUNT PINS
    pins.mount.azimuthalZeroSensor = PIN_AZ_ZERO_SENSOR;
    pins.mount.azimuthalPins.i01 = PIN_AZ_IO1;
    pins.mount.azimuthalPins.i02 = PIN_AZ_IO2;
    pins.mount.azimuthalPins.i11 = PIN_AZ_I11;
    pins.mount.azimuthalPins.i12 = PIN_AZ_I12;
    pins.mount.azimuthalPins.ph1 = PIN_AZ_PH1;
    pins.mount.azimuthalPins.ph2 = PIN_AZ_PH2;
    pins.mount.elevationPins.i01 = PIN_EL_IO1;
    pins.mount.elevationPins.i02 = PIN_EL_IO2;
    pins.mount.elevationPins.i11 = PIN_EL_I11;
    pins.mount.elevationPins.i12 = PIN_EL_I12;
    pins.mount.elevationPins.ph1 = PIN_EL_PH1;
    pins.mount.elevationPins.ph2 = PIN_EL_PH2;

    // MOUNT CONFIG
    config.mount.elevationAngleBounds.min = MOUNT_EL_ANGLE_MIN  * GEL_PI_OVER_180;
    config.mount.elevationAngleBounds.max = MOUNT_EL_ANGLE_MAX * GEL_PI_OVER_180;
    config.mount.azelRatio = MOUNT_AZEL_RATIO;
    config.mount.azimuthalRevolutionNumSteps = MOUNT_AZ_NUM_STEPS;
    config.mount.elevationRevolutionNumSteps = MOUNT_EL_NUM_STEPS;
    config.mount.reverseElevationDirection = !MOUNT_EL_START_NEAR_CUTOUT;
    config.mount.calibrateElevationNearMax = MOUNT_EL_START_NEAR_CUTOUT;

    // LINK CONFIG
    config.link.controller = true;
    
    // RADIO PINS
    pins.radio.nss = PIN_RADIO_NSS;
    pins.radio.dio0 = PIN_RADIO_DIO0;
    pins.radio.reset = PIN_RADIO_RESET;

    // IMU PINS
    pins.imu.nss = PIN_IMU_NSS;
    pins.imu.interrupt = PIN_IMU_INT;
    
    // BEGIN GROUND STATION
    if (gel::Error err = groundStation.begin(config, pins))
        return err;

    delay(1000);
    return gel::Error::None;
}

void setup()
{
    tnc.begin();
    if (gel::Error err = setupGroundStation())
        tnc.handleError(err, "Could not initialize ground station");
    else
        tnc.setGroundStation(groundStation);
}

void loop()
{   
    tnc.update();
    groundStation.update();
}