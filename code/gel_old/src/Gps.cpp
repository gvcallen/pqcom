#include "Core.h"
#include "Stream.h"
#include "Gps.h"
#include "MagDec.h"

namespace gel
{

int Gps::begin(Stream *gpsSerial)
{
    this->gpsSerial = gpsSerial;
}

int Gps::update()
{
    if (gpsSerial->available() > 0)
    {
        char c = gpsSerial->read();
        bool encodeResult = tinyGps.encode(c);
        if (!encodeResult)
        {
            return Error::BadCommunication;
        }
    }

    return Error::None;
}

expected<double, Error> Gps::getLatitude()
{
    if (!tinyGps.location.isValid())
        return Error::InvalidState;

    return tinyGps.location.lat();
}

expected<double, Error> Gps::getLongitude()
{
    if (!tinyGps.location.isValid())
        return Error::InvalidState;

    return tinyGps.location.lng();
}

expected<double, Error> Gps::getAltitude()
{
    if (!tinyGps.altitude.isValid())
        return Error::InvalidState;

    return tinyGps.altitude.meters();
}

expected<float, Error> Gps::getMagneticDeclination()
{
    auto lng = getLongitude();
    if (!lng)
        return lng.error();

    auto lat = getLatitude();
    if (!lat)
        return lat.error();

    auto year = getYear();
    
    auto decl = ::gel::getMagneticDeclination(lat.value(), lng.value(), year.value_or(2014));
    return decl;
}

expected<uint8_t, Error> Gps::getSecond()
{
    if (!tinyGps.time.isValid())
        return Error::InvalidState;

    return tinyGps.time.second();
}

expected<uint8_t, Error> Gps::getMinute()
{
    if (!tinyGps.time.isUpdated())
        return Error::InvalidState;

    return tinyGps.time.minute();
}

expected<uint8_t, Error> Gps::getHour()
{
    if (!tinyGps.time.isUpdated())
        return Error::InvalidState;

    return tinyGps.time.hour();
}

expected<uint8_t, Error> Gps::getDay()
{
    if (!tinyGps.date.isValid())
        return Error::InvalidState;

    return tinyGps.date.day();
}

expected<uint8_t, Error> Gps::getMonth()
{
    if (!tinyGps.date.isValid())
        return Error::InvalidState;

    return tinyGps.date.month();
}

expected<uint16_t, Error> Gps::getYear()
{
    if (!tinyGps.date.isValid())
        return Error::InvalidState;

    return tinyGps.date.year();
}

} // namespace gel
