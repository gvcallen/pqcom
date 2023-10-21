#pragma once

#include <gel.h>

class PqUnit
{
public:
    void begin();
    void update();

private:
    gel::Error setupLink();
    gel::Error setupGps();
    gel::Error setupRadio();

    void updateButton();

    gel::Error handleTelemetry(gel::span<uint8_t> payload);
    gel::Error handleTelecommand(gel::span<uint8_t> command, gel::span<uint8_t> response);    
    void handleError(gel::Error err, const char* msg = nullptr, bool critical = true);
    void handleButtonPress();

    static gel::Error telemetryCallback(gel::span<uint8_t> payload) { return getPqUnit()->handleTelemetry(payload); };
    static gel::Error telecommandCallback(gel::span<uint8_t> command, gel::span<uint8_t> response) { return getPqUnit()->handleTelecommand(command, response); };
    static PqUnit* getPqUnit() {return singleton; }

private:
    const unsigned long bounceDelay = 50;
    unsigned long lastBounceTime = 0;
    int prevButtonState = 1;
    
    uint64_t telemetryCounter = 0;
    static PqUnit* singleton;

    gel::Radio radio;
    gel::Link link;

    gel::Gps gps{};
};