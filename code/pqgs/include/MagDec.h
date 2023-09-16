#include "Core.h"

struct MagneticDeclinationCorrection
{
    int year;
    int lat;
    int lon;
    float magdec;
};

extern const MagneticDeclinationCorrection magDecCorrections[];
extern size_t numMagDecCorrections;

// Year may be 2023 or 2024. Lat-long must be in South Africa.
float getMagDev(float lat, float lon, int year);