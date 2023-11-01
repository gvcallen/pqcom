#include "Settings.h"
#include "PqUnit.h"

#include <Arduino.h>
#include <gel.h>

PqUnit pq;
void setup()
{
    // Calibrated for Atmega328 on PQ unit for 8 MHz internal clock
    OSCCAL = 101;

    pq.begin();
}

void loop()
{
    pq.update(); 
}