#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Suncq.h"
#include "Serial.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>

QTextStream out(stdout);

static const char* TEXT_TRACK_MODE_NONE = "None";
static const char* TEXT_TRACK_MODE_GPS_UPLOADED = "GPS Uploaded";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);
    loadSettings();
    populateWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateWidgets()
{
    populateSerialDevices();
    ui->trackModeCombo->addItems({TEXT_TRACK_MODE_NONE,
                                  TEXT_TRACK_MODE_GPS_UPLOADED});
}

void MainWindow::loadSettings()
{
    loadSerialSettings();
    saveSettings();
}

void MainWindow::saveSettings()
{
    saveSerialSettings();
}

void MainWindow::saveSerialSettings()
{
    settings.setValue("baudRate", ui->baudRateEdit->text().toInt());
    settings.setValue("dataBits", ui->dataBitsCombo->currentText().toInt());
    settings.setValue("stopBits", ui->stopBitsCombo->currentText().toInt());
}

void MainWindow::populateSerialDevices()
{
    this->serialInfo = QSerialPortInfo::availablePorts();

    // Set ui options and values
    if (this->serialInfo.size() == 0)
    {
        ui->portNameCombo->addItem("<No devices found>");
    }
    else
    {
        for (auto& info : serialInfo)
            ui->portNameCombo->addItem(info.portName());
    }
}

void MainWindow::loadSerialSettings()
{    
    // Load previous values from settings
    auto baudRate = settings.value("baudRate", 115200).toInt();
    auto dataBits = QSerialPort::DataBits(settings.value("dataBits", 8).toInt());
    auto parity = QSerialPort::Parity(settings.value("parity", 0).toInt());
    auto stopBits = QSerialPort::StopBits(settings.value("stopBits", 1).toInt());

    ui->dataBitsCombo->addItems({"5", "6", "7", "8"});
    ui->dataBitsCombo->setCurrentText(QString::number(dataBits));
    ui->stopBitsCombo->addItems({"1", "2", "3"});
    ui->stopBitsCombo->setCurrentText(QString::number(stopBits));
    ui->baudRateEdit->setText(QString::number(baudRate));
}

void MainWindow::selectFlightPathFile()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Select Flight Path File"), QString(), tr("CSV Files (*.csv)"));
    if (fileName != "")
    {
        ui->flightPathFileLabel->setText(fileName);
        flightPathLoaded = true;
    }
}

void MainWindow::openSerialPort()
{    
    auto name = ui->portNameCombo->itemText(0);
    auto baudRate = settings.value("baudRate").toInt();
    auto dataBits = QSerialPort::DataBits(settings.value("dataBits").toInt());
    auto parity = QSerialPort::Parity(settings.value("parity").toInt());
    auto stopBits = QSerialPort::StopBits(settings.value("stopBits").toInt());

    out << name;    
    
    serial->setPortName(name);
    serial->setBaudRate(baudRate);
    serial->setDataBits(dataBits);
    serial->setParity(parity);
    serial->setStopBits(stopBits);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    
    if (this->serialInfo.empty())
    {
        ui->statusLabel->setText(QString("Could not open device: No devices found"));
    }
    else
    {
        if (serial->open(QIODevice::ReadWrite))
        {
            ui->statusLabel->setText("Connected");
            ui->serialConnectionButton->setText("Disconnect");
            this->connect(serial, &QSerialPort::readyRead, this, &MainWindow::serialBytesReady);
        }
        else
        {
            ui->statusLabel->setText(QString("Could not open device: ") + serial->errorString());
        }
    }
}

void MainWindow::toggleSerialPortConnection()
{
    if (serial->isOpen())
        closeSerialPort();
    else
        openSerialPort();
}

void MainWindow::serialBytesReady()
{
    auto bytes = serial->readAll();
    serialBytes.insert(serialBytes.end(), bytes.begin(), bytes.end());

    auto location = std::find(serialBytes.begin(), serialBytes.end(), '\n');
    while (location != serialBytes.end())
    {
        QString message;
        for (auto it = serialBytes.begin(); it != location - 1; it++)
        {
            char c = (char)*it;
            message.append(c);
        }
        serialBytes.erase(serialBytes.begin(), location + 1);
        ui->serialMonitor->append(message);

        location = std::find(serialBytes.begin(), serialBytes.end(), '\n');
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    
    ui->statusLabel->setText("Not Connected");
    ui->serialConnectionButton->setText("Connect");
}

void MainWindow::uploadData()
{    
    if (flightPathLoaded)
    {
        if (!uploadFlightPath(serial, ui->flightPathFileLabel->text()))
            QMessageBox::critical(this, "Error uploading path", "Failed to upload flight path. Please ensure that the TNC is connected and that the file is valid.");
    }
}

void MainWindow::setTrackMode()
{
    if (ui->trackModeCombo->currentText() == TEXT_TRACK_MODE_NONE)
        ::setTrackMode(serial, suncq::TrackMode::None);
    else if (ui->trackModeCombo->currentText() == TEXT_TRACK_MODE_GPS_UPLOADED)
        ::setTrackMode(serial, suncq::TrackMode::GpsUploaded);
}

void MainWindow::calibrate()
{
    ::calibrate(serial);
}

void MainWindow::returnToStart()
{
    ::returnToStart(serial);
}

void MainWindow::returnToStow()
{
    ::returnToStow(serial);
}