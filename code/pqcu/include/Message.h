#pragma once

#include <gel/Core.h>

class Message
{
public:
    enum Type
    {
        SET_MODE_STREAMING,
        SET_MODE_INTERACTIVE,
    };

public:
    Message(gel::span<uint8_t> data);

private:
    Type type;
};