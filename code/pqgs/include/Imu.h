#include <MPU9250_WE.h>
#include <SPI.h>

namespace pqgs
{

struct ImuPins
{
    SPIClass* spi;
    uint8_t nss;
    uint8_t interrupt;
};

class Imu
{
public:
    Imu() {};

    int begin(ImuPins pins);
    xyzFloat getAcceleration();

private:
    bool initialized = false;

    ImuPins pins;
    MPU9250_WE mpu;
};

  xyzFloat gValue = myMPU6500.getGValues();
  xyzFloat gyr = myMPU6500.getGyrValues();
  float temp = myMPU6500.getTemperature();
  float resultantG = myMPU6500.getResultantG(gValue);

} // namespace pqgs