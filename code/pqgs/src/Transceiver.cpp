#include <LoRa.h>

#include "Transceiver.h"
#include "Core.h"

const uint32_t TIMEOUT_IN_MS = 2000;

namespace pqgs
{

int Transceiver::begin(TransceiverPins pins, uint32_t frequency, uint32_t syncWord)
{
    lora = &LoRa;
    
    lora->setPins(pins.nss, pins.reset, pins.dio0);
    
    // DEBUG - Todo - Add ability to use custom SPI
  
    uint32_t timeWaited = 0;
    const uint32_t delayTime = 500;
    while (!lora->begin(frequency))
    {
        delay(delayTime);
        timeWaited += delayTime;

        if (delayTime >= TIMEOUT_IN_MS)
            return ERROR_TIMEOUT;
    }

    LoRa.setSyncWord(syncWord);

    return ERROR_NONE;
}

int Transceiver::send(const Printable& printable)
{
    LoRa.beginPacket();
    LoRa.print(printable);
    LoRa.endPacket();

    return ERROR_NONE;
}

int Transceiver::receive()
{
    return ERROR_NONE;
}

} // namespace pqgs;