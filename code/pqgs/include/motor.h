#include "Arduino.h"

#define L6219_MOTOR_MAX_STATES 12

namespace pqgs
{

struct MotorPins
{
    uint8_t i01;
    uint8_t i11;
    uint8_t ph1;
    uint8_t i02;
    uint8_t i12;
    uint8_t ph2;
    uint8_t zeroSensor;
};

class Motor
{
public:
    Motor () { initialized = false; };
    void begin(MotorPins pins, bool hasZeroSensor = false, uint8_t stepDivision = 1);

    void move (uint32_t position);
    uint32_t getPosition();
    void stepForward (uint32_t numSteps);
    void stepBackward (uint32_t numSteps);
    void returnToZero ();
    void setSpeed(uint32_t speed);

private:
    void outputState();

private:
    bool initialized;
    MotorPins pins;
    uint8_t stepDivision;

    uint8_t numStates;
    uint8_t currentState;
    bool directionStatesA[L6219_MOTOR_MAX_STATES];
    bool directionStatesB[L6219_MOTOR_MAX_STATES];
    bool lsbStatesA[L6219_MOTOR_MAX_STATES];
    bool lsbStatesB[L6219_MOTOR_MAX_STATES];
    bool msbStatesA[L6219_MOTOR_MAX_STATES];
    bool msbStatesB[L6219_MOTOR_MAX_STATES];
    
    uint32_t position; // in divisional steps
    uint32_t stepTimeDelay; // in microseconds
    uint32_t prevStepTime; // in microseconds
};


} // namespace pqgs