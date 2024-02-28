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

/**
 * @brief Class for a PocketQube terminal node which implements the SUNCQ protocol.
    It handles communication with a host PC via Serial, including error and status messages.
    It is a Singleton i.e. only one instance should be created.
    
    The PqTnc "stores" all state to be passed over to the ground station, such as
    flight path information. However, it does not "control" the ground station mechanics,
    i.e. the control system is part of the ground station class itself, but it rather supplies the
    ground station with the information at the right moments in time. This seperation makes thing
    a bit easier to reason about.
 * 
 */
class PqTnc
{
public:
    void begin();
    void update();

private:
    /* Setup */
    gel::Error setupEEPROM();
    gel::Error setupGroundStation();
    gel::Error setupSettings();
    gel::Error setupFlightPath();
    
    /* Update*/
    gel::Error updateSerial();
    gel::Error updateSerialNormal(uint8_t c);
    gel::Error updateSerialKISS(uint8_t c);
    gel::vector<gel::Error, 2> updateTracking();
    gel::Error updateTrackingGPSUploaded();
    gel::Error updateTrackingGPSReceived();
    
    /* Flight path */
    gel::Error saveFlightPath();
    bool addFlightPathData(uint8_t newData);
    bool addKnownLocationData(uint8_t newData);

    /* Protocol commands */
    gel::Error setTncMode(suncq::TncMode mode);
    gel::Error setTrackMode(suncq::TrackMode mode);
    void reset();

    /* Protocol responses */
    void sendAcknowledge();
    void sendSignalRSSI();
    void sendTelemetry(String msg);
    void sendMessage(String msg);
    void sendError(gel::Error& err);

    /* Handles e.g. for messages/errors */
    gel::Error handleTelemetry(gel::span<uint8_t> payload);
    void handleError(gel::Error err, const char* msg = nullptr);

    /* Static functions */
    static gel::Error telemetryCallback(gel::span<uint8_t> payload) {return PqTnc::getTnc()->handleTelemetry(payload); };
    static PqTnc* getTnc() { return singletonTnc; };

private:
    static PqTnc* singletonTnc;
    
    /* Flight path */
    gel::GeoInstant path[FLIGHT_PATH_MAX_SIZE / sizeof (gel::GeoInstant)];
    size_t nextPathInstantIdx = 0; // the path instant the payload is next heading towards
    size_t numPathInstants = 0;

    /* Closed-loop GPS */
    gel::GeoInstant latestReceivedInstant;
    bool gpsRecieved = false;
    
    /* SUNCQ Command State */
    size_t byteStreamIdx = 0;
    bool receivingByteStream = false;
    suncq::Command currentCommand = suncq::Command::Invalid;

    /* Settings and objects */    
    gel::GroundStation groundStation;
    TncSettings settings;
};