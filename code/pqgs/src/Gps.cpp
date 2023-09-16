#include "Gps.h"
#include "Stream.h"

namespace pqsu
{

int Gps::begin(Stream *gpsSerial)
{
    gpsSerial = gpsSerial;
}

int Gps::update()
{
    if (gpsSerial->available() > 0)
    {
        if (tinyGps.encode(gpsSerial->read()))
        {

        }
    }
}


//   if (gpsSerial.available() > 0) {
//     if (gps.encode(gpsSerial.read())) {
//       if (gps.location.isValid()) {
//         // Serial.print(F("- latitude: "));
//         Serial.println(gps.location.lat());

//         // Serial.print(F("- longitude: "));
//         Serial.println(gps.location.lng());

//         Serial.print(F("- altitude: "));
//         if (gps.altitude.isValid())
//           Serial.println(gps.altitude.meters());
//         else
//           int x = 5;
//           // Serial.println(F("INVALID"));
//       } else {
//           int x = 5;
//         // Serial.println(F("- location: INVALID"));
//       }

//       // Serial.print(F("- speed: "));
//       if (gps.speed.isValid()) {
//         Serial.print(gps.speed.kmph());
//         // Serial.println(F(" km/h"));
//       } else {
//         int x = 5;
//         // Serial.println(F("INVALID"));
//       }

//       Serial.print(F("- GPS date&time: "));
//       if (gps.date.isValid() && gps.time.isValid()) {
//         Serial.print(gps.date.year());
//         Serial.print(F("-"));
//         Serial.print(gps.date.month());
//         Serial.print(F("-"));
//         Serial.print(gps.date.day());
//         Serial.print(F(" "));
//         Serial.print(gps.time.hour());
//         Serial.print(F(":"));
//         Serial.print(gps.time.minute());
//         Serial.print(F(":"));
//         Serial.println(gps.time.second());
//       } else {
//         Serial.println(F("INVALID"));
//       }

//       Serial.println();
//     }
//   }

//   if (millis() > 5000 && gps.charsProcessed() < 10)
//     Serial.println(F("No GPS data received: check wiring"));




} // namespace pqsu
