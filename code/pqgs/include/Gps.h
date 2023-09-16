namespace pqgs
{

#include <Arduino.h>
#include <TinyGPS++.h>

#include "Core.h"

class Gps
{
    public:
        Gps();

        expected_void begin(Stream *gpsSerial);
        int update();
        double getLatitude();
        double getLongitude();
        double getAltitude();
        double getMagneticInclination();

    private:
        TinyGPSPlus tinyGps;
        Stream *gpsSerial;
};

} // namespace pqgs