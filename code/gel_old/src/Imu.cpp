#include <MPU9250_WE.h>

#include "Core.h"
#include "Imu.h"

namespace gel
{

expected<void, Error> Imu::begin(ImuPins pins)
{
    // if (!mpu.init())
    // {
        // return Error::Uninitialized;
        // return;
    // }

    /* Choose the SPI clock speed, default is 8 MHz 
       This function must be used only after init(), not before */
    //myMPU9250.setSPIClockSpeed(4000000);

    // Serial.println("Position you MPU9050 flat and don't move it - calibrating...");
    // delay(1000);
    // myMPU9050.autoOffsets();
    // Serial.println("Done!");

    //myMPU9050.setAccOffsets(-14240.0, 18220.0, -17280.0, 15590.0, -20930.0, 12080.0);
    //myMPU9050.setGyrOffsets(45.0, 145.0, -105.0);
    // myMPU9050.enableGyrDLPF();
    //myMPU9050.disableGyrDLPF(MPU9050_BW_WO_DLPF_8800); // bandwdith without DLPF
    // myMPU9050.setGyrDLPF(MPU9050_DLPF_6);
    // myMPU9050.setSampleRateDivider(5);
    // myMPU9050.setGyrRange(MPU9050_GYRO_RANGE_250);
    // myMPU9050.setAccRange(MPU9050_ACC_RANGE_2G);
    // myMPU9050.enableAccDLPF(true);
    // myMPU9050.setAccDLPF(MPU9050_DLPF_6);
    //myMPU9050.enableAccAxes(MPU9050_ENABLE_XYZ);
    //myMPU9050.enableGyrAxes(MPU9050_ENABLE_XYZ);

      // if (!this-> .init())
    // else{
      // Serial.println("MPU9050 is connected");
    // }
}   

Vec3f getLinearAcceleration()
{

}

Vec3f getRotationAcceleration()
{

}


} // namespace gel