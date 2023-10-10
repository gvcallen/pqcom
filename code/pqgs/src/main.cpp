#include <Arduino.h>
#include "PqTnc.h"

PqTnc tnc;

void setup()
{
    tnc.setup();
}

void loop()
{   
    tnc.update();
}