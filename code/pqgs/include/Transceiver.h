#include <Arduino.h>

#include "Core.h"

class LoRaClass;

namespace pqgs
{

struct TransceiverPins
{
    uint8_t miso;
    uint8_t mosi;
    uint8_t sck;
    uint8_t nss;
    uint8_t reset;
    etl::optional<uint8_t> dio0;
    etl::optional<uint8_t> dio1;
    etl::optional<uint8_t> dio2;
    etl::optional<uint8_t> dio3;
    etl::optional<uint8_t> dio4;
};

class Transceiver
{
public:
    Transceiver() {};
    int begin(TransceiverPins pins, uint32_t frequency, uint32_t syncWord = 0xF3);
    
    int send(const Printable& printable);
    int receive();

private:
    bool initialized = false;

    TransceiverPins pins;
    uint32_t frequency;
    
    LoRaClass* lora;
};

} // namespace pqgs