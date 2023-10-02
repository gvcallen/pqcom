#include "Core.h"
#include "StepperMotor.h"

namespace gel
{

// NB: The maximum number of states must be reflected in MOTOR_MAX_STATES.

// Full step sequence
const float fullStepCurrentStatesA[] =    {1.0, 1.0, 1.0, 1.0}; // output to I0 and I1 current (phase A)
const float fullStepCurrentStatesB[] =    {1.0, 1.0, 1.0, 1.0}; // output to I0 and I1 current (phase B)
const bool fullStepDirectionStatesA[] =   {0,1,1,0}; // output to direction (phase A)
const bool fullStepDirectionStatesB[] =   {0,0,1,1}; // output to direction (phase B)

// Half-stepping states
const float halfStepCurrentStatesA[] =     {3.0/3.0, 3.0/3.0, 1.0/3.0, 3.0/3.0, 3.0/3.0, 3.0/3.0, 1.0/3.0, 3.0/3.0}; // output to I0 and I1 current (phase A)
const float halfStepCurrentStatesB[] =     {1.0/3.0, 3.0/3.0, 3.0/3.0, 3.0/3.0, 1.0/3.0, 3.0/3.0, 3.0/3.0, 3.0/3.0}; // output to I0 and I1 current (phase B)
const bool halfStepDirectionStatesA[] =    {1, 1, 0, 0, 0, 0, 1, 1}; // output to direction (phase A)
const bool halfStepDirectionStatesB[] =    {1, 1, 1, 1, 0, 0, 0, 0}; // output to direction (phase B)

// Holding states
const float holdingCurrentStatesA[] =      {1.0};
const float holdingCurrentStatesB[] =      {1.0};
const bool holdingDirectionStatesA[] =     {0}; // output to direction (phase A)
const bool holdingDirectionStatesB[] =     {1}; // output to direction (phase B)

int StepperMotor::begin(StepperMotorPins pins, StepperMotorConfig config)
{
    // Setup config and pins
    this->initialized = true;
    this->pins = pins;
    this->config = config;
    this->stateIdx = 0;

    // Enable a pseudo-holding state (at 0.0 current)
    this->currentMultiplierSet = true;
    this->currentMultiplier = 0.0;
    enableHolding();
    this->currentMultiplierSet = false;

    // Set the various pins to output
    pinMode (this->pins.i01, OUTPUT);
    pinMode (this->pins.i11, OUTPUT);
    pinMode (this->pins.ph1, OUTPUT);
    pinMode (this->pins.i02, OUTPUT);
    pinMode (this->pins.i12, OUTPUT);
    pinMode (this->pins.ph2, OUTPUT);

    return Error::None;
}

void StepperMotor::move(double position)
{
    // if (this->config.stepRange)
    // {
        // 
    // }
// 
    // stepN(this->position - position)
    
}

double StepperMotor::getPosition()
{
    return this->position;
}

void StepperMotor::setSpeed(float speedMultiplier)
{
    this->speedMultiplier = speedMultiplier;
}

void StepperMotor::stepDivisional(bool backwards)
{
    this->prevStepTime = micros();

    bool downwards = backwards != config.reverseDirection;

    if (!downwards)
    {
        stateIdx++;
        if (stateIdx == numStates)
            stateIdx = 0;
    }
    else
    {
        if (stateIdx == 0)
            stateIdx = numStates - 1;
        else
            stateIdx--;

    }
    
    updateIO();
}

void StepperMotor::stepN(double numSteps, bool backwards)
{
    double integral;
    double fractional = modf(numSteps, &integral);

    uint32_t numFullSteps = (uint32_t)integral;
    
    for (uint32_t i = 0; i < numFullSteps; i++)
    {
        stepDivisional(backwards);
        delayMicroseconds(this->config.stepDelay / speedMultiplier);
    }

    // TODO: Deal with fractional steps
}

void StepperMotor::stepForward(double numSteps)
{
    stepN(numSteps, false);
}

void StepperMotor::stepBackward(double numSteps)
{
    stepN(numSteps, true);
}

void StepperMotor::returnToZero()
{
    move(0.0);
}

void StepperMotor::calibrate()
{
    //uint32_t savedStepDelay = this->config.stepDelay;
    //this->config.stepDelay =  this->config.stepDelay * (1.0 / speedMultiplier);
    
    if (config.stepRange) // mechanical stop. calibrate by rotating by 10% more than the step range
    {
        stepBackward(config.stepRange * 1.1);
        this->position = 0.0;
    }
    else // zero sensor calibration
    {
        // TODO
    }

    // this->config.stepDelay = savedStepDelay;
}

void StepperMotor::updateIO()
{
    uint8_t maxCurrentLevel = config.numCurrentLevels - 1;
    
    uint8_t currentA = currentStatesA[stateIdx] * currentMultiplier * maxCurrentLevel;
    uint8_t currentB = currentStatesB[stateIdx] * currentMultiplier * maxCurrentLevel;
    uint8_t directionA = directionStatesA[stateIdx];
    uint8_t directionB = directionStatesB[stateIdx];


    if (config.activeLow)
    {
        currentA = maxCurrentLevel - currentA;
        currentB = maxCurrentLevel - currentB;
    }

    
    digitalWrite(pins.i01, currentA & 0b01);
    digitalWrite(pins.i11, currentA & 0b10);
    digitalWrite(pins.i02, currentB & 0b01);
    digitalWrite(pins.i12, currentB & 0b10);
    digitalWrite(pins.ph1, directionA);
    digitalWrite(pins.ph2, directionB);
}

void StepperMotor::enableHolding(float currentMultiplier)
{
    setCurrentMultiplier(currentMultiplier);

    enableState(holdingDirectionStatesA,
                holdingDirectionStatesB,
                holdingCurrentStatesA,
                holdingCurrentStatesB,
                NUM_ELEMS(holdingDirectionStatesA)
               );
}

void StepperMotor::enableHalfStepping(float currentMultiplier)
{
    setCurrentMultiplier(currentMultiplier);

    enableState(halfStepDirectionStatesA,
                halfStepDirectionStatesB,
                halfStepCurrentStatesA,
                halfStepCurrentStatesB,
                NUM_ELEMS(halfStepDirectionStatesA)
               );
}

void StepperMotor::enableFullStepping(float currentMultiplier)
{
    setCurrentMultiplier(currentMultiplier);

    enableState(fullStepDirectionStatesA,
                fullStepDirectionStatesB,
                fullStepCurrentStatesA,
                fullStepCurrentStatesB,
                NUM_ELEMS(fullStepDirectionStatesA)
               );
}

void StepperMotor::enableState(const bool directionStatesA[], const bool directionStatesB[], const float currentStatesA[], const float currentStatesB[], uint8_t numStates)
{
    if (!currentMultiplierSet)
        currentMultiplier = 1.0;

    this->numStates = numStates;
    memcpy (this->directionStatesA, directionStatesA, sizeof (directionStatesA[0]) * numStates);
    memcpy (this->directionStatesB, directionStatesB, sizeof (directionStatesB[0]) * numStates);
    memcpy (this->currentStatesA, currentStatesA, sizeof (currentStatesA[0]) * numStates);
    memcpy (this->currentStatesB, currentStatesB, sizeof (currentStatesB[0]) * numStates);

    updateIO();
}

Error StepperMotor::setCurrentMultiplier(float currentMultiplier)
{
    if (currentMultiplier < 0.0 || currentMultiplier > 1.0)
        return Error::BadParameter;
    
    this->currentMultiplier = currentMultiplier;
    this->currentMultiplierSet = true;

    updateIO();
    
    return Error::None;
}

} // namespace gel