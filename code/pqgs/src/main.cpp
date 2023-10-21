#include "PqTnc.h"

#include <Arduino.h>
#include <gel.h>

PqTnc tnc;

void setup()
{
    tnc.begin();
}

void loop()
{   
    tnc.update();
}