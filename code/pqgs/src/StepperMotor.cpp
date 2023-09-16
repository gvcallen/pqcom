#include "Core.h"
#include "StepperMotor.h"

namespace pqgs
{

// NB: The maximum number of states must be reflected in MOTOR_MAX_STATES.

// Single stepping states
const uint8_t singleStepCurrentStatesA[] =  {3,3,3,3}; // output to I0 and I1 current (phase A)
const uint8_t singleStepCurrentStatesB[] =  {3,3,3,3}; // output to I0 and I1 current (phase B)
const bool singleStepDirectionStatesA[] =   {0,1,1,0}; // output to direction (phase A)
const bool singleStepDirectionStatesB[] =   {0,0,1,1}; // output to direction (phase B)

// Half-stepping states
const uint8_t halfStepCurrentStatesA[] =    {1,3,3,3,1,3,3,3}; // output to I0 and I1 current (phase A)
const uint8_t halfStepCurrentStatesB[] =    {3,3,1,3,3,3,1,3}; // output to I0 and I1 current (phase B)
const bool halfStepDirectionStatesA[] =     {1,1,1,1,0,0,0,0}; // output to direction (phase A)
const bool halfStepDirectionStatesB[] =     {1,1,0,0,0,0,1,1}; // output to direction (phase B)

// Holding states. Holding current is set based on a member variable
const bool holdingDirectionStatesA[] =      {0}; // output to direction (phase A)
const bool holdingDirectionStatesB[] =      {1}; // output to direction (phase B)

int StepperMotor::begin(StepperMotorPins pins, uint8_t stepDivision, uint8_t numCurrentLevels, bool mechanicalStop)
{
    // Setup config and pins
    this->initialized = true;
    this->pins = pins;
    this->mechanicalStop = mechanicalStop;
    this->stepDivision = stepDivision;
    this->numCurrentLevels = numCurrentLevels;
    this->holdingCurrentBinary = 0;

    // Enable holding, which initially is actually no holding (no current)
    enableHolding();

    // Set the various pins to output
    pinMode (this->pins.i01, OUTPUT);
    pinMode (this->pins.i11, OUTPUT);
    pinMode (this->pins.ph1, OUTPUT);
    pinMode (this->pins.i02, OUTPUT);
    pinMode (this->pins.i12, OUTPUT);
    pinMode (this->pins.ph2, OUTPUT);

    // Output the IO
    updateIO();
}

void StepperMotor::move(uint32_t position)
{

}

uint32_t StepperMotor::getPosition()
{

}

void StepperMotor::setSpeed(uint32_t pps)
{

}

void StepperMotor::stepForward(uint32_t numSteps)
{
    stateIdx++;
    if (stateIdx == numStates)
        stateIdx = 0;
        
    updateIO();
}

void StepperMotor::stepBackward(uint32_t numSteps)
{
    if (stateIdx == 0)
        stateIdx = numStates - 1;
    else
        stateIdx--;
    
    updateIO();
}

void StepperMotor::returnToZero ()
{

}

void StepperMotor::updateIO()
{
    uint8_t i01 = ((numCurrentLevels - 1) - currentStatesA[stateIdx]) & 0b01;
    uint8_t i11 = ((numCurrentLevels - 1) - currentStatesA[stateIdx]) & 0b10;
    uint8_t i02 = ((numCurrentLevels - 1) - currentStatesB[stateIdx]) & 0b01;
    uint8_t i12 = ((numCurrentLevels - 1) - currentStatesB[stateIdx]) & 0b10;
    uint8_t ph1 = directionStatesA[stateIdx];
    uint8_t ph2 = directionStatesB[stateIdx];

    digitalWrite(pins.i01, i01);
    digitalWrite(pins.i11, i11);
    digitalWrite(pins.i02, i02);
    digitalWrite(pins.i12, i12);
    digitalWrite(pins.ph1, ph1);
    digitalWrite(pins.ph2, ph2);
}

void StepperMotor::enableHolding()
{
    this->numStates = 1;
    directionStatesA[0] = holdingDirectionStatesA[0];
    directionStatesB[0] = holdingDirectionStatesB[0];
    currentStatesA[0] = holdingCurrentBinary;
    currentStatesB[0] = holdingCurrentBinary;
}

void StepperMotor::enableHalfStepping()
{
    this->numStates = NUM_ELEMS(halfStepDirectionStatesA);
    memcpy (this->directionStatesA, halfStepDirectionStatesA, sizeof (halfStepDirectionStatesA));
    memcpy (this->directionStatesB, halfStepDirectionStatesB, sizeof (halfStepDirectionStatesB));
    memcpy (this->currentStatesA, halfStepCurrentStatesA, sizeof (halfStepCurrentStatesA));
    memcpy (this->currentStatesB, halfStepCurrentStatesB, sizeof (halfStepCurrentStatesB));
}

void StepperMotor::enableFullStepping()
{
    this->numStates = NUM_ELEMS(singleStepDirectionStatesA);
    memcpy (this->directionStatesA, singleStepDirectionStatesA, sizeof (singleStepDirectionStatesA));
    memcpy (this->directionStatesB, singleStepDirectionStatesB, sizeof (singleStepDirectionStatesB));
    memcpy (this->currentStatesA, singleStepCurrentStatesA, sizeof (singleStepCurrentStatesA));
    memcpy (this->currentStatesB, singleStepCurrentStatesB, sizeof (singleStepCurrentStatesB));
}

} // namespace pqgs