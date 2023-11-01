#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // General slots
    void selectFlightPathFile();
    void toggleSerialPortConnection();
    void serialBytesReady();
    void autoRXOutputReady();
    void autoRXErrorReady();
    void autoRXLogCheck();
    void autoRXLogChanged();
    void setAutoRXPath();
    void onClose();
    
    // SUNCQ Slots
    void resetGroundStation();
    void calibrate();
    void returnToStart();
    void returnToStow();
    void uploadData();
    void setTrackMode();
    void setTrackTarget();

    void showModified()
    {
        
        QMessageBox::information(this,"Directory Modified", "Your Directory is modified");
    }    

private:
    void closeSerialPort();
    void openSerialPort();

    void populateWidgets();
    void loadSettings();
    void loadSerialSettings();
    void loadGroundStationSettings();
    void populateSerialDevices();
    void saveSettings();
    void saveSerialSettings();
    void saveGroundStationSettings();

    void setTrackTargetLoRa();
    void setTrackTargetRadiosonde();
    void setTrackLocation(float lat, float lng, float alt);
    void setSnr(float snr);

    QString getLogFilePath();

private:
    Ui::MainWindow *ui;
    
    QSerialPort *serial;
    QList<QSerialPortInfo> serialInfo;

    QSettings settings;

    bool flightPathLoaded = false;

    std::vector<uint8_t> serialBytes;

    QProcess* autoRXProcess;
    QTimer* autoRXTimer;
    QDateTime lastLogCheckTime;
};
#endif // MAINWINDOW_H
