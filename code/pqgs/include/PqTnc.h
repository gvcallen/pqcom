#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <gel.h>

#include "Settings.h"
#include "Suncq.h"

struct FlightPathHeader
{
    uint16_t numInstances;
};

struct TncSettings
{
    suncq::TncMode tncMode = suncq::TncMode::Normal;
    suncq::TrackMode trackMode = suncq::TrackMode::None;
};

/*  Class for a PocketQube terminal node which implements the SUNCQ protocol.
    It handles communication with a host PC via Serial, including error and status messages.
    
    It also "stores" all state to be passed over to the ground station, such as
    flight path information. However, it does not "control" the ground station per-say,
    i.e. the control system is part of the ground station class itself.
    
    It is therefore not responsible for calling update on the ground station, but does require
    a refernece to it during construction to provide it with new information, when necessary.
*/
class PqTnc
{
public:
    void begin();
    void update();
    void setGroundStation(gel::GroundStation& groundStation) {this->groundStation = &groundStation; }
    void handleError(gel::Error err, const char* msg = nullptr);

private:
    // Setup
    void beginEEPROM();
    gel::Error loadSettings();
    gel::Error loadFlightPath();
    
    // Update
    void updateSerial();
    void updateSerialNormal(uint8_t c);
    void updateSerialKISS(uint8_t c);
    void updateTracking();
    void updateTrackingGPSUploaded();
    
    // Flight path commands
    gel::Error saveFlightPath();
    bool addFlightPathData(uint8_t newData);

    // Protocol commands
    void setTncMode(suncq::TncMode mode);
    gel::Error setTrackMode(suncq::TrackMode mode);
    void reset();

    // Protocol responses
    void sendAcknowledge();
    void sendSignalRSSI();
    void sendMessage(String msg);

private:
    gel::GeoInstant path[FLIGHT_PATH_MAX_SIZE / sizeof (gel::GeoInstant)];
    size_t nextPathInstantIdx = 0; // the path instant the payload is next heading towards
    size_t numPathInstants = 0;
    
    size_t pathByteIdx = 0;
    bool receivingByteStream = false;
    
    suncq::Command currentCommand = suncq::Command::Invalid;
    TncSettings settings;
    
    gel::GroundStation* groundStation = nullptr;
};