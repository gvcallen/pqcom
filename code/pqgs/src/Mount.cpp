#include "Mount.h"

namespace pqgs
{

void Mount::begin(StepperMotorPins elevationPins, StepperMotorPins azimuthalPins, uint32_t speed)
{
    this->azimuthalMotor.begin (azimuthalPins);
    this->elevationMotor.begin (elevationPins);
}

void Mount::returnToZero()
{

}

void Mount::calibrate()
{
    
}

void Mount::stepAzForward()
{
    azimuthalMotor.stepForward (1);
}

void Mount::stepAzBackward()
{
    azimuthalMotor.stepBackward (1);
}

} // namespace pqgs'