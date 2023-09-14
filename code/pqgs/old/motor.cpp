#include "motor.h"

namespace pqgs
{

// Single stepping states
const bool singleStepDirectionStateA[] = {0,1,1,0}; // output to direction 1
const bool singleStepDirectionStateB[] = {0,0,1,1}; // output to direction 2
const bool singleStepLsbStateA[] = {0,0,0,0}; // output to LSB current limiting 1
const bool singleStepMsbStateA[] = {0,0,0,0}; // output to MSB current limiting 1
const bool singleStepLsbStateB[] = {0,0,0,0}; // output to LSB current limiting 2
const bool singleStepMsbStateB[] = {0,0,0,0}; // output to MSB current limiting 2

void Motor::begin (MotorPins config, bool hasZeroSensor, uint8_t stepDivision)
{
    // Setup config and pins
    this->initialized = true;
    this->pins = config;
    this->stepDivision = stepDivision;

    // Setup state arrays. These arrays allow us to simply increment a state counter
    // that changes the excited windings and current amounts to step (or micro-step)
    // the motor
    uint8_t numStates;
    const bool *directionStatesA, *directionStatesB, *lsbStatesA,
               *msbStatesA, *lsbStatesB, *msbStatesB;
    
    // DEBUG - Hardcoded for now to only allow single-stepping
    stepDivision = 1;

    // We populated the array points and number of states depending on
    // whether micro-stepping is required
    if (stepDivision == 4)
    {

    }
    else if (stepDivision == 2)
    {

    }
    else // stepDivision == 1
    {
        numStates = 4;
        directionStatesA = singleStepDirectionStateA;
        directionStatesB = singleStepDirectionStateB;
        lsbStatesA = singleStepLsbStateA;
        msbStatesB = singleStepMsbStateB;
        lsbStatesA = singleStepLsbStateA;
        msbStatesB = singleStepMsbStateB;
    }

    // Populate the number of states and state arrays
    this->numStates = numStates;
    memcpy (this->directionStatesA, directionStatesA, sizeof (bool) * numStates);
    memcpy (this->directionStatesB, directionStatesB, sizeof (bool) * numStates);
    memcpy (this->lsbStatesA, lsbStatesA, sizeof (bool) * numStates);
    memcpy (this->msbStatesB, msbStatesB, sizeof (bool) * numStates);
    memcpy (this->lsbStatesA, lsbStatesA, sizeof (bool) * numStates);
    memcpy (this->msbStatesB, msbStatesB, sizeof (bool) * numStates);

    // Set the various pins to output
    pinMode (this->pins.i01, OUTPUT);
    pinMode (this->pins.i11, OUTPUT);
    pinMode (this->pins.ph1, OUTPUT);
    pinMode (this->pins.i02, OUTPUT);
    pinMode (this->pins.i12, OUTPUT);
    pinMode (this->pins.ph2, OUTPUT);

    // Set all pins to high (no current)
    pinMode (this->pins.i01, HIGH);
    pinMode (this->pins.i11, HIGH);
    pinMode (this->pins.ph1, HIGH);
    pinMode (this->pins.i02, HIGH);
    pinMode (this->pins.i12, HIGH);
    pinMode (this->pins.ph2, HIGH);
}

void Motor::move (uint32_t position)
{

}

uint32_t Motor::getPosition()
{

}

void Motor::setSpeed(uint32_t speed)
{

}

void Motor::stepForward (uint32_t numSteps)
{
    currentState++;
    if (currentState == numStates)
        currentState = 0;
        
    outputState();
}

void Motor::stepBackward (uint32_t numSteps)
{
    if (currentState == 0)
        currentState = numStates - 1;
    else
        currentState--;
    
    outputState();
}

void Motor::returnToZero ()
{

}

void Motor::outputState()
{
    digitalWrite(pins.i01, lsbStatesA[currentState]);
    digitalWrite(pins.i11, msbStatesA[currentState]);
    digitalWrite(pins.ph1, directionStatesA[currentState]);
    digitalWrite(pins.i02, lsbStatesB[currentState]);
    digitalWrite(pins.i12, msbStatesB[currentState]);
    digitalWrite(pins.ph2, directionStatesB[currentState]);
}

} // namespace pqgs