#include "Settings.h"
#include "PqUnit.h"

#include <Arduino.h>
#include <gel.h>

PqUnit pq;

void setup()
{
    // Calibrated for Atmega328 on PQ unit developed in 2023 for 8 MHz internal clock.
    // If this line is not included, clock timing is not calibrated and software serial
    // with the GPS does not work.
    OSCCAL = 101;

    pq.begin();
}

void loop()
{
    pq.update(); 
}