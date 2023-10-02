#include "StepperMotor.h"

namespace gel
{

class Mount
{
public:
    Mount() { initialized = false; }

    void begin(StepperMotorPins elevationPins, StepperMotorPins azimuthalPins, uint32_t speed = 1);
    void returnToZero();
    void calibrate();

    void stepAzForward();
    void stepAzBackward();

private:
    bool initialized;

    StepperMotor elevationMotor, azimuthalMotor;
};

} // namespace gel