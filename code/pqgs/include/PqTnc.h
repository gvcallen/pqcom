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
*/
class PqTnc
{
public:
    void begin();
    void update();
    void handleError(gel::Error err, const char* msg = nullptr);

private:
    // Setup
    gel::Error setupEEPROM();
    gel::Error setupGroundStation();
    gel::Error loadSettings();
    gel::Error loadFlightPath();
    
    // Update
    gel::Error updateSerial();
    gel::Error updateSerialNormal(uint8_t c);
    gel::Error updateSerialKISS(uint8_t c);
    gel::Error updateTracking();
    gel::Error updateTrackingGPSUploaded();
    gel::Error updateTrackingGPSReceived();
    
    // Flight path commands
    gel::Error saveFlightPath();
    bool addFlightPathData(uint8_t newData);
    bool addKnownLocationData(uint8_t newData);

    // Protocol commands
    gel::Error setTncMode(suncq::TncMode mode);
    gel::Error setTrackMode(suncq::TrackMode mode);
    void reset();

    // Protocol responses
    void sendAcknowledge();
    void sendSignalRSSI();
    void sendMessage(String msg);
    void sendError(gel::Error& err);

    // Interfacing
    gel::Error handleTelemetry(gel::span<uint8_t> payload);

    // Static
    static gel::Error telemetryCallback(gel::span<uint8_t> payload) {return PqTnc::getTnc()->handleTelemetry(payload); };
    static PqTnc* getTnc() { return singletonTnc; };

private:
    static PqTnc* singletonTnc;
    
    gel::GeoInstant path[FLIGHT_PATH_MAX_SIZE / sizeof (gel::GeoInstant)];
    size_t nextPathInstantIdx = 0; // the path instant the payload is next heading towards
    size_t numPathInstants = 0;

    gel::GeoInstant latestReceivedInstant;
    bool gpsRecieved = false;
    
    size_t byteStreamIdx = 0;
    bool receivingByteStream = false;
    
    suncq::Command currentCommand = suncq::Command::Invalid;
    TncSettings settings;
    
    gel::GroundStation groundStation;
};