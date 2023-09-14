/* namespace pqsu
{

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class Gps
{
    public:
        Gps(int gpsRxPin, int gpsTxPin, uint32_t gpsBaud = 9600);

    private:
        TinyGPSPlus tinyGps;
        SoftwareSerial gpsSerial;
};

} // namespace pqsu */