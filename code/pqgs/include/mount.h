#include "motor.h"

namespace pqgs
{

class Mount
{
public:
    Mount() { initialized = false; }

    void begin (MotorPins elevationPins, MotorPins azimuthalPins, uint32_t speed = 1);
    void returnToZero ();
    void calibrate ();

    void stepAzForward ();
    void stepAzBackward ();

private:
    bool initialized;

    Motor elevationMotor, azimuthalMotor;
};

} // namespace pqgs