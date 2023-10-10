#pragma once

enum class ProtocolCommand
{
    SetTncMode = 0x00,
    SetTrackMode = 0x01,
    SetPathData = 0x02,
    GetSignalRSSI = 0x40,
    Reset = 0x7F,
    TncStatus = 0x80,
    TncMessage = 0x81,
    SignalRSSI = 0xA0,
    Reserved = 0xFF,
};

enum class TncMode
{
    Normal = 0x00,
    Kiss = 0x01,
};

enum class TrackMode
{
    None = 0x00,
    GpsUploaded = 0x01,
    GpsReceived = 0x02,
    SignalStrength = 0x04,
};

enum class StatusCode
{
    Acknowledge = 0x00,
    TrackingUnsuccessful = 0x01,
};