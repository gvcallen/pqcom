#include "mount.h"

namespace pqgs
{

void Mount::begin (MotorPins elevationPins, MotorPins azimuthalPins, uint32_t speed)
{
    this->azimuthalMotor.begin (azimuthalPins, true, 1);
    this->elevationMotor.begin (elevationPins, false, 1);
}

void Mount::returnToZero()
{

}

void Mount::calibrate ()
{
    
}

void Mount::stepAzForward ()
{
    azimuthalMotor.stepForward (1);
}

void Mount::stepAzBackward ()
{
    azimuthalMotor.stepBackward (1);
}

} // namespace pqgs'