#include <MPU9250_WE.h>
#include <SPI.h>

#include "Core.h"

namespace gel
{

struct ImuPins
{
    SPIClass* spi;
    uint8_t nss;
    optional<uint8_t> interrupt;
};

class Imu
{
public:
    Imu() {};

    expected<void, Error> begin(ImuPins pins);
    Vec3f getLinearAcceleration();
    Vec3f getRotationAcceleration();

private:
    bool initialized = false;

    ImuPins pins;
    MPU9250_WE mpu;
};

} // namespace gel