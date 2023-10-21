#include "Settings.h"
#include "PqUnit.h"

#include <Arduino.h>
#include <gel.h>

PqUnit pq;
void setup()
{
    // Calibrate for Atmega328 on PQ unit for 8 MHz clock
    OSCCAL = 101;

    pq.begin();
}

void loop()
{
    pq.update(); 
}