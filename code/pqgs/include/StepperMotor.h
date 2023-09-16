#include <Arduino.h>

#include "Core.h"

#define MOTOR_MAX_STATES 12

namespace pqgs
{

struct StepperMotorPins
{
    uint8_t i01;
    uint8_t i11;
    uint8_t ph1;
    uint8_t i02;
    uint8_t i12;
    uint8_t ph2;
    etl::optional<uint8_t> zeroSensor;
    etl::optional<uint8_t> currentSensorA;
    etl::optional<uint8_t> currentSensorB;
};

class StepperMotor
{
public:
    StepperMotor() { initialized = false; };
    int begin(StepperMotorPins pins, uint8_t stepDivision = 1, uint8_t numCurrentLevels = 4, bool mechanicalStop = false);

    void move(uint32_t position);
    uint32_t getPosition();
    void stepForward(uint32_t numSteps);
    void stepBackward(uint32_t numSteps);
    void returnToZero();
    void setSpeed(uint32_t pps);
    void enableHolding();
    void enableHalfStepping();
    void enableFullStepping();
    void setHoldingCurrentBinary(uint8_t holdingCurrentBinary) { this->holdingCurrentBinary = holdingCurrentBinary; };

private:

    void updateIO();

private:
    bool initialized;
    StepperMotorPins pins;
    bool mechanicalStop;
    uint8_t stepDivision;
    uint8_t numCurrentLevels;
    float holdingCurrentBinary;

    uint8_t numStates;
    uint8_t stateIdx;
    
    bool directionStatesA[MOTOR_MAX_STATES];
    bool directionStatesB[MOTOR_MAX_STATES];
    uint8_t currentStatesA[MOTOR_MAX_STATES];
    uint8_t currentStatesB[MOTOR_MAX_STATES];
    
    uint32_t position; // in divisional steps
    uint32_t stepTimeDelay; // in microseconds
    uint32_t prevStepTime; // in microseconds
};


} // namespace pqgs