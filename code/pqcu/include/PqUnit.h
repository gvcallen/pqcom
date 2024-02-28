#pragma once

#include <gel.h>

#include "Settings.h"

/**
 * @brief The PqUnit class encompasses the communication module/unit on the PocketQube.
 * It is a singleton class (only one instance) that controls the radio module, GPS communication,
 * and the Telemetry/Telecommand link. A user of this class must create the instance, call
 * begin() to initialize it, and call update() as often as possible.
 * 
 */
class PqUnit
{
public:
    void begin();
    void update();

private:
    /* Setup functions */
    gel::Error setupLink();
    gel::Error setupGps();
    gel::Error setupRadio();

    /* Update functions */
    void updateButton();

    /* "Handle" functions, to deal with a message/action/error */
    gel::Error handleTelemetry(gel::span<uint8_t> payload);
    gel::Error handleTelecommand(gel::span<uint8_t> command, gel::span<uint8_t> response);    
    void handleError(gel::Error err, const char* msg = nullptr, bool critical = true);
    void handleButtonPress();

    /* Static callback functions*/
    static gel::Error telemetryCallback(gel::span<uint8_t> payload) { return getPqUnit()->handleTelemetry(payload); };
    static gel::Error telecommandCallback(gel::span<uint8_t> command, gel::span<uint8_t> response) { return getPqUnit()->handleTelecommand(command, response); };
    static PqUnit* getPqUnit() { return singleton; }

private:
    const unsigned long bounceDelay = BUTTON_DEBOUNCE;
    unsigned long lastBounceTime = 0;
    int prevButtonState = HIGH; // active high
    
    uint64_t telemetryCounter = 0;
    static PqUnit* singleton;

    gel::Radio radio;
    gel::Link link;

    gel::Gps gps{};
};