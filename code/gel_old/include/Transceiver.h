#include <Arduino.h>

#include "Core.h"
#include "RadioLib.h"

namespace gel
{

struct TransceiverPins
{
    uint8_t nss;
    uint8_t reset;
    uint8_t dio0;
    optional<uint8_t> dio1;
    optional<uint8_t> dio2;
    optional<uint8_t> dio3;
    optional<uint8_t> dio4;
    optional<SPIClass*> SPI;
};

class Transceiver
{
public:
    Transceiver() {};
    Error begin(TransceiverPins pins, uint32_t frequency, uint32_t syncWord = 0xF3);
    
    Error send(span<uint8_t> msg);
    int receive();

private:
    bool initialized = false;

    TransceiverPins pins;
    uint32_t frequency;
    
    SX1278 radio{nullptr};
};

} // namespace gel