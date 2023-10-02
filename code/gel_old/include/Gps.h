namespace gel
{

#include <Arduino.h>
#include <TinyGPS++.h>

#include "Core.h"

class Gps
{
    public:
        Gps();

        int begin(Stream *gpsSerial);
        int update();
        expected<double, Error> getLatitude();
        expected<double, Error> getLongitude();
        expected<double, Error> getAltitude();
        expected<float, Error> getMagneticDeclination();
        expected<uint8_t, Error> getSecond();
        expected<uint8_t, Error> getMinute();
        expected<uint8_t, Error> getHour();
        expected<uint8_t, Error> getDay();
        expected<uint8_t, Error> getMonth();
        expected<uint16_t, Error> getYear();

    private:
        TinyGPSPlus tinyGps;
        Stream *gpsSerial;
};

} // namespace gel