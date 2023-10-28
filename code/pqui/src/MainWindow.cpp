#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Suncq.h"
#include "Serial.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>
#include <QFileSystemWatcher>

QTextStream out(stdout);

static const char* TEXT_TRACK_MODE_NONE = "None";
static const char* TEXT_TRACK_MODE_GPS_UPLOADED = "GPS Uploaded";
static const char* TEXT_TRACK_MODE_GPS_RECEIVED = "GPS Recieved";
static const char* TEXT_TRACK_MODE_GPS_UPLOADED_AND_RECEIVED = "GPS Uploaded & Received";

static const char* TEXT_TRACK_TARGET_LORA = "LoRa";
static const char* TEXT_TRACK_TARGET_RADIOSONDE = "Radiosonde";

static const char* KEY_AUTO_RX_PATH = "autoRxPath";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , settings(QSettings(QSettings::IniFormat, QSettings::UserScope, "Gary Allen", "PQUI"))
{
    ui->setupUi(this);
    this->connect(this, SIGNAL(aboutToQuit()), this, SLOT(onClose()));

    loadSettings();
    populateWidgets();
    openSerialPort();
}

MainWindow::~MainWindow()
{
    if (autoRXProcess)
        autoRXProcess->close();
    saveSettings();
    delete ui;
}

void MainWindow::onClose()
{
}

void MainWindow::populateWidgets()
{
    populateSerialDevices();
    ui->trackModeCombo->addItems({TEXT_TRACK_MODE_NONE,
                                  TEXT_TRACK_MODE_GPS_UPLOADED,
                                  TEXT_TRACK_MODE_GPS_RECEIVED,
                                  TEXT_TRACK_MODE_GPS_UPLOADED_AND_RECEIVED});
    ui->trackTargetCombo->addItems({TEXT_TRACK_TARGET_LORA,
                                  TEXT_TRACK_TARGET_RADIOSONDE});
}

void MainWindow::loadSettings()
{
    loadSerialSettings();
    loadGroundStationSettings();
    saveSettings();
}

void MainWindow::saveSettings()
{
    saveSerialSettings();
    saveGroundStationSettings();
    settings.sync();
}

void MainWindow::saveSerialSettings()
{
    settings.setValue("baudRate", ui->baudRateEdit->text().toInt());
    settings.setValue("dataBits", ui->dataBitsCombo->currentText().toInt());
    settings.setValue("stopBits", ui->stopBitsCombo->currentText().toInt());
}

void MainWindow::saveGroundStationSettings()
{
    auto path = ui->autoRXPathLabel->text();
    settings.setValue(KEY_AUTO_RX_PATH, path);
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
    // auto parity = QSerialPort::Parity(settings.value("parity", 0).toInt());
    auto stopBits = QSerialPort::StopBits(settings.value("stopBits", 1).toInt());

    ui->dataBitsCombo->addItems({"5", "6", "7", "8"});
    ui->dataBitsCombo->setCurrentText(QString::number(dataBits));
    ui->stopBitsCombo->addItems({"1", "2", "3"});
    ui->stopBitsCombo->setCurrentText(QString::number(stopBits));
    ui->baudRateEdit->setText(QString::number(baudRate));
}

void MainWindow::loadGroundStationSettings()
{
    ui->autoRXPathLabel->setText(settings.value(KEY_AUTO_RX_PATH, "").toString());
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

void MainWindow::autoRXOutputReady()
{
    auto outData = autoRXProcess->readAllStandardOutput();
    ui->serialMonitor->append(outData);
}

void MainWindow::autoRXErrorReady()
{
    auto outData = autoRXProcess->readAllStandardError();
    ui->serialMonitor->append(outData);
}

QString MainWindow::getLogFilePath()
{
    QString folderPath = settings.value(KEY_AUTO_RX_PATH).toString() + "/log";
    auto fileNames = QDir(folderPath).entryList(QStringList() << "*.log", QDir::Files);

    if (fileNames.empty())
    {
        QMessageBox::critical(this, "Could not find log file", "Could not open AutoRX log file. Please ensure the log file has been previously generated");
        return "";
    }
    
    auto fileName = fileNames[0];
    QString filePath = folderPath + "/" + fileName;
    return filePath;
}

void MainWindow::autoRXLogChanged()
{
    auto filePath = getLogFilePath();

    QFile logFile(filePath);
    if (logFile.open(QIODevice::ReadOnly))
    {
        auto headers = QString(logFile.readLine()).split(',');
        
        int latIdx = -1, lngIdx = -1, altIdx = -1;
        for (int i = 0; i < headers.size(); i++)
        {
            if (headers[i] == "lat")
                latIdx = i;
            else if (headers[i] == "lon")
                lngIdx = i;
            else if (headers[i] == "alt")
                altIdx = i;
        }

        if (latIdx == -1 || lngIdx == -1 || altIdx == -1)
            return;

        // Debugging code - uncomment to read file line-by-line
        // static int targetLine = 0;
        // QString latestData;
        // for (int i = 0; i <= targetLine; i++)
            // latestData = logFile.readLine();
        // qDebug() << "Line " << targetLine;
        // targetLine++;

        auto lineLength = logFile.readLine().size();
        qint64 fileSize = logFile.size();
        logFile.seek(fileSize - lineLength);
        auto latestData = QString(logFile.read(lineLength));
        logFile.close();

        auto values = latestData.split(',');

        auto largestIdx = std::max(latIdx, std::max(lngIdx, altIdx));

        if (largestIdx > values.size())
            return;

        auto latStr = values[latIdx];
        auto lngStr = values[lngIdx];
        auto altStr = values[altIdx];

        float lat = latStr.toFloat(); 
        float lng = lngStr.toFloat(); 
        float alt = altStr.toFloat(); 

        setTrackLocation(lat, lng, alt);
    }
}

void MainWindow::autoRXLogCheck()
{
    auto filePath = getLogFilePath();
    const QFileInfo info(filePath);
    const QDateTime lastModified = info.lastModified();

    if (lastModified > lastLogCheckTime)
    {
        lastLogCheckTime = lastModified;
        autoRXLogChanged();
    }
}

void MainWindow::setAutoRXPath()
{
    auto folderPath = QFileDialog::getExistingDirectory(this, tr("Select Folder 'radiosonde_auto_rx'"), QString());
    if (folderPath != "")
    {
        settings.setValue(KEY_AUTO_RX_PATH, folderPath);
        ui->autoRXPathLabel->setText(folderPath);
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
    else if (ui->trackModeCombo->currentText() == TEXT_TRACK_MODE_GPS_RECEIVED)
        ::setTrackMode(serial, suncq::TrackMode::GpsReceived);
    else if (ui->trackModeCombo->currentText() == TEXT_TRACK_MODE_GPS_UPLOADED_AND_RECEIVED)
        ::setTrackMode(serial, (suncq::TrackMode)((int)suncq::TrackMode::GpsUploaded & (int)suncq::TrackMode::GpsReceived));
}

void MainWindow::setTrackTarget()
{
    auto currentText = ui->trackTargetCombo->currentText();
    if (currentText == TEXT_TRACK_TARGET_LORA)
        setTrackTargetLoRa();
    else
        setTrackTargetRadiosonde();
}

void MainWindow::setTrackTargetLoRa()
{
    if (autoRXProcess && autoRXProcess->isOpen())
        autoRXProcess->close();
    ui->trackTargetCombo->setCurrentIndex(0);
    ::setTrackTarget(serial, suncq::TrackTarget::Internal);
}

void MainWindow::setTrackTargetRadiosonde()
{
    ui->trackTargetCombo->setCurrentIndex(1);
    QString autoRXScriptDir = settings.value(KEY_AUTO_RX_PATH).toString();
    bool error = false;

    if (!QFileInfo::exists(autoRXScriptDir + "/auto_rx.py"))
    {
        QMessageBox::critical(this, "Error enabling Radiosonde", "Please ensure the AutoRX path is set to the 'auto_rx' directory.");
        error = true;
    }

    bool ok;
    QString password = QInputDialog::getText(this, tr("Enter Sudo Password"),
                                             tr("Password:"), QLineEdit::Password,
                                             "", &ok);

    if (!ok || password.isEmpty())
        error = true;

    if (error)
        return setTrackTargetLoRa();

    if (autoRXProcess)
        delete autoRXProcess;
    autoRXProcess = new QProcess(this);

    connect(autoRXProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(autoRXOutputReady()));
    connect(autoRXProcess, SIGNAL(readyReadStandardError()), this, SLOT(autoRXErrorReady()));

    autoRXProcess->setWorkingDirectory(autoRXScriptDir);

    QString script = "echo '" + password + "' | sudo -S python3 -u auto_rx.py";
    autoRXProcess->start("bash", QStringList() << "-c" << script);
    autoRXProcess->waitForStarted();

    if (autoRXTimer)
        delete autoRXTimer;

    autoRXTimer = new QTimer(this);
    this->connect(autoRXTimer, &QTimer::timeout, this, &MainWindow::autoRXLogCheck);
    autoRXTimer->start(1000);

    ::setTrackTarget(serial, suncq::TrackTarget::External);
}

void MainWindow::setTrackLocation(float lat, float lng, float alt)
{
    suncq::GeoInstant instant;
    instant.secondsSinceEpoch = QDateTime::currentSecsSinceEpoch();
    instant.latitude = lat;
    instant.longitude = lng;
    instant.altitude = alt;
    
    qDebug() << "Setting track location";
    qDebug() << "Lat: " << lat;
    qDebug() << "Lng: " << lng;
    qDebug() << "Alt: " << alt;
    qDebug() << "Sec: " << instant.secondsSinceEpoch;
    
    ::setTrackLocation(serial, instant);
}

void MainWindow::resetGroundStation()
{
    ::reset(serial);
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