#pragma once

namespace suncq
{

enum Command
{
    Reset = 0x00,
    Calibrate = 0x01,
    ReturnToStart = 0x02,
    ReturnToStow = 0x03,
    SetTncMode = 0x30,
    SetTrackMode = 0x31,
    SetPathData = 0x32,
    SetTrackLocation = 0x33,
    SetTrackTarget = 0x34,
    GetSignalRSSI = 0x60,
    TncTelemetry = 0x80,
    TncMessage = 0x81,
    SignalRSSI = 0xA0,
    Invalid = 0xFF,
};

enum TncMode
{
    Normal = 0x00,
    Kiss = 0x01,
};

enum TrackMode
{
    None = 0x00,
    GpsUploaded = 0x01,
    GpsReceived = 0x02,
    SignalStrengthInitial = 0x04,
};

enum StatusCode
{
    Acknowledge = 0x00,
    TrackingUnsuccessful = 0x01,
};

} // namespace suncq