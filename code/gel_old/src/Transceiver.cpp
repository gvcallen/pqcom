#include <RadioLib.h>

#include "Transceiver.h"
#include "Core.h"

const uint32_t TIMEOUT_IN_MS = 2000;

namespace gel
{

Error Transceiver::begin(TransceiverPins pins, uint32_t frequency, uint32_t syncWord)
{
    if (pins.dio1.has_value())
        radio = new Module(pins.nss, pins.dio0, pins.reset, pins.dio1.value());
    else
        radio = new Module(pins.nss, pins.dio0, pins.reset);

    int state = radio.begin();
    if (state != RADIOLIB_ERR_NONE)
        return Error::Uninitialized;

    return Error::None;
}

Error Transceiver::send(span<uint8_t> msg)
{
    int state = radio.transmit(msg.data(), msg.size());
  
    if (state != RADIOLIB_ERR_NONE)
    {
        if (state == RADIOLIB_ERR_PACKET_TOO_LONG)
        {
            return Error::OutOfRange;
        }
        else if (state == RADIOLIB_ERR_TX_TIMEOUT)
        {
           return Error::Timeout;
        }
        
        return Error::Internal;
    }
  
    return Error::None;
}

int Transceiver::receive()
{
    return Error::None;
}

} // namespace gel;