#include "Suncq.h"

#include <rapidcsv.h>
#include <QTextStream>
#include <QDateTime>
#include <QSerialPort>

bool sendCommand(QSerialPort* serial, suncq::Command command)
{
    uint8_t c = (uint8_t)command;
    serial->write((const char*)&c, 1);
    return serial->waitForBytesWritten();   
}

bool uploadFlightPath(QSerialPort* serial, QString filepath)
{
    if (!serial->isOpen())
        return false;
    
    // Open CSV file
    rapidcsv::Document doc(filepath.toUtf8().data());

    // Determine if number of entries is within range
    uint64_t rows = doc.GetRowCount();
    if (rows > ((1 << 16) - 1))
        return false;
    
    // Send flight path data command character and number of entries
    uint8_t c = (uint8_t)suncq::Command::SetPathData;
    uint16_t rows16 = (uint64_t)rows;
    serial->write((const char*)&c, 1);
    serial->write((const char*)&rows16, 2);
    serial->waitForBytesWritten();

    // Send each entry
    for (size_t i = 0; i < doc.GetRowCount(); i++)
    {
        suncq::GeoInstant instant;

        auto date = QDateTime::fromString(doc.GetCell<std::string>("datetime", i).c_str(), Qt::DateFormat::ISODateWithMs);
        // date.totim
        instant.secondsSinceEpoch = date.toSecsSinceEpoch();
        qDebug() << "instantsec = " << instant.secondsSinceEpoch;
        instant.latitude = doc.GetCell<float>("latitude", i);
        instant.longitude = doc.GetCell<float>("longitude", i);
        instant.altitude = doc.GetCell<float>("altitude", i);

        serial->write((const char*)&instant, sizeof (suncq::GeoInstant));
    }
    
    return serial->waitForBytesWritten();
}

bool reset(QSerialPort* serial)
{
    return sendCommand(serial, suncq::Command::Reset);
}

bool calibrate(QSerialPort* serial)
{
    return sendCommand(serial, suncq::Command::Calibrate);
}

bool returnToStart(QSerialPort* serial)
{
    return sendCommand(serial, suncq::Command::ReturnToStart);
}

bool returnToStow(QSerialPort* serial)
{
    return sendCommand(serial, suncq::Command::ReturnToStow);
}

bool setTrackTarget(QSerialPort* serial, suncq::TrackTarget trackTarget)
{
    uint8_t c = (uint8_t)suncq::Command::SetTrackTarget;
    serial->write((const char*)&c, 1);
    serial->write((const char*)&trackTarget, 1);
    return serial->waitForBytesWritten();
}

bool setTrackMode(QSerialPort* serial, suncq::TrackMode trackMode)
{
    uint8_t c = (uint8_t)suncq::Command::SetTrackMode;
    serial->write((const char*)&c, 1);
    serial->write((const char*)&trackMode, 1);
    return serial->waitForBytesWritten();
}

bool setTrackLocation(QSerialPort* serial, suncq::GeoInstant& instant)
{
    uint8_t c = (uint8_t)suncq::Command::SetTrackLocation;
    serial->write((const char*)&c, 1);
    serial->write((const char*)&instant, sizeof (suncq::GeoInstant));
    
    return serial->waitForBytesWritten();
    
}