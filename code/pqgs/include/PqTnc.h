#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <gel.h>

#include "Settings.h"
#include "Protocol.h"

// Class for a PocketQube terminal node, which contains a ground station and implements the PQGS protocol
class PqTnc
{
public:
    void setup();
    void update();

private:
    // Setup and update - main
    void setupSerial();
    void setupEEPROM();
    void setupFlightPath();
    void setupGroundStation();
    void updateSerial();
    
    // Setup and update - sub
    void updateSerialNormal(uint8_t c);
    void updateSerialKISS(uint8_t c);

    // Error handling
    void handleError(gel::Error err, const char* msg = nullptr);

    // Protocol commands
    void setTncMode(TncMode mode);
    void setTrackingMode(TrackMode mode);
    void updatePathData(uint8_t newData);
    void reset();

    // Protocol responses
    void sendAcknowledge();
    void sendSignalRSSI();


private:
    uint8_t flightPathCsv[FLIGHT_PATH_CSV_MAX_SIZE];

    TncMode tncMode = TncMode::Normal;
    gel::GroundStation groundStation;
};