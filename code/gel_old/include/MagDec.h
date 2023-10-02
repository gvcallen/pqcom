#include "Core.h"

namespace gel
{

struct MagneticDeclinationCorrection
{
    int year;
    int lat;
    int lon;
    float magdec;
};

// Year may be 2023 or 2024. Lat-long must be in South Africa.
expected<float, Error> getMagneticDeclination(float lat, float lon, uint16_t year);

} // namespace gel