#pragma once

#include "Suncq.h"

#include <QSerialPort>

bool uploadFlightPath(QSerialPort* serial, QString filepath);
bool calibrate(QSerialPort* serial);
bool returnToStart(QSerialPort* serial);
bool returnToStow(QSerialPort* serial);
bool setTrackMode(QSerialPort* serial, suncq::TrackMode trackMode);