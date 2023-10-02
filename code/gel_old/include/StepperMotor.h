#pragma once

#include <Arduino.h>
#include "Core.h"

#define MOTOR_MAX_STATES 12

namespace gel
{

struct StepperMotorPins
{
    uint8_t i01;
    uint8_t i11;
    uint8_t ph1;
    uint8_t i02;
    uint8_t i12;
    uint8_t ph2;
    optional<uint8_t> zeroSensor;
    optional<uint8_t> currentSensorA;
    optional<uint8_t> currentSensorB;
};

struct StepperMotorConfig
{
    uint8_t stepDivision = 1;
    uint8_t numCurrentLevels = 4;
    bool reverseDirection = true;
    bool activeLow = true;
    double stepRange = 0.0; // number of full steps in range, if mechanically stopped. Leave as 0 for no mechanical stop (360 degrees)
    uint32_t stepDelay = 1000; // in microseconds
};

class StepperMotor
{
public:
    StepperMotor() { initialized = false; };
    
    int begin(StepperMotorPins pins, StepperMotorConfig config);
    void calibrate();

    void move(double position);
    double getPosition();
    void stepForward(double numSteps);
    void stepBackward(double numSteps);
    void returnToZero();
    
    void setSpeed(float speedMultiplier);
    Error setCurrentMultiplier(float currentLimit);
    void enableHolding(float currentMultiplier = 1.0);
    void enableHalfStepping(float currentMultiplier = 1.0);
    void enableFullStepping(float currentMultiplier = 1.0);

private:
    void stepDivisional(bool backwards = false);
    void stepN(double numSteps, bool backwards = false);
    void updateIO();
    void enableState(const bool directionStatesA[], const bool directionStatesB[], const float currentStatesA[], const float currentStatesB[], uint8_t numStates);

private:
    bool initialized;
    StepperMotorPins pins;
    StepperMotorConfig config;
    
    float currentMultiplier = 0.0;
    bool currentMultiplierSet = false;

    uint8_t numStates;
    uint8_t stateIdx;
    
    bool directionStatesA[MOTOR_MAX_STATES];
    bool directionStatesB[MOTOR_MAX_STATES];
    float currentStatesA[MOTOR_MAX_STATES];
    float currentStatesB[MOTOR_MAX_STATES];
    
    float speedMultiplier = 1.0;
    double position = 0.0; // in (fractional) full steps
    uint32_t prevStepTime; // in microseconds
};


} // namespace gel