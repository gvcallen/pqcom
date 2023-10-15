#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>

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
    
    // SUNCQ Slots
    void calibrate();
    void returnToStart();
    void returnToStow();
    void uploadData();
    void setTrackMode();

private:
    void closeSerialPort();
    void openSerialPort();

    void populateWidgets();
    void loadSettings();
    void loadSerialSettings();
    void populateSerialDevices();
    void saveSettings();
    void saveSerialSettings();

private:
    Ui::MainWindow *ui;
    
    QSerialPort *serial;
    QList<QSerialPortInfo> serialInfo;

    bool flightPathLoaded = false;
    QSettings settings;

    std::vector<uint8_t> serialBytes;
};
#endif // MAINWINDOW_H
