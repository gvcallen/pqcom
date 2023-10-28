/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *connectionTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *serialGroup;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *portNameCombo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *baudRateLabel;
    QLineEdit *baudRateEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_2;
    QComboBox *dataBitsCombo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *stopBitsLabel;
    QComboBox *stopBitsCombo;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *serialConnectionButton;
    QSpacerItem *horizontalSpacer;
    QGroupBox *statusGroup;
    QVBoxLayout *verticalLayout_4;
    QLabel *statusLabel;
    QWidget *groundStationTab;
    QVBoxLayout *verticalLayout;
    QGroupBox *upload;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout;
    QComboBox *trackModeCombo;
    QLabel *label_5;
    QComboBox *trackTargetCombo;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_4;
    QLabel *autoRXPathLabel;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *flightPathFileButton;
    QPushButton *groundStationUploadButton;
    QLabel *flightPathFileLabel;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *label_8;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_2;
    QLabel *groundStationUploadStatusLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QTextBrowser *serialMonitor;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *Clear;
    QSpacerItem *horizontalSpacer_4;
    QWidget *satelliteTab;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        connectionTab = new QWidget();
        connectionTab->setObjectName(QString::fromUtf8("connectionTab"));
        verticalLayout_2 = new QVBoxLayout(connectionTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        serialGroup = new QGroupBox(connectionTab);
        serialGroup->setObjectName(QString::fromUtf8("serialGroup"));
        verticalLayout_3 = new QVBoxLayout(serialGroup);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(serialGroup);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        portNameCombo = new QComboBox(serialGroup);
        portNameCombo->setObjectName(QString::fromUtf8("portNameCombo"));
        portNameCombo->setMinimumSize(QSize(0, 0));
        portNameCombo->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_5->addWidget(portNameCombo);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        baudRateLabel = new QLabel(serialGroup);
        baudRateLabel->setObjectName(QString::fromUtf8("baudRateLabel"));
        baudRateLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(baudRateLabel);

        baudRateEdit = new QLineEdit(serialGroup);
        baudRateEdit->setObjectName(QString::fromUtf8("baudRateEdit"));
        baudRateEdit->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_2->addWidget(baudRateEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_2 = new QLabel(serialGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_7->addWidget(label_2);

        dataBitsCombo = new QComboBox(serialGroup);
        dataBitsCombo->setObjectName(QString::fromUtf8("dataBitsCombo"));
        dataBitsCombo->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_7->addWidget(dataBitsCombo);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        stopBitsLabel = new QLabel(serialGroup);
        stopBitsLabel->setObjectName(QString::fromUtf8("stopBitsLabel"));

        horizontalLayout_3->addWidget(stopBitsLabel);

        stopBitsCombo = new QComboBox(serialGroup);
        stopBitsCombo->setObjectName(QString::fromUtf8("stopBitsCombo"));
        stopBitsCombo->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_3->addWidget(stopBitsCombo);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        serialConnectionButton = new QPushButton(serialGroup);
        serialConnectionButton->setObjectName(QString::fromUtf8("serialConnectionButton"));
        serialConnectionButton->setMinimumSize(QSize(100, 0));
        serialConnectionButton->setMaximumSize(QSize(16777215, 16777215));
        serialConnectionButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_4->addWidget(serialConnectionButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(serialGroup);

        statusGroup = new QGroupBox(connectionTab);
        statusGroup->setObjectName(QString::fromUtf8("statusGroup"));
        statusGroup->setMinimumSize(QSize(0, 100));
        statusGroup->setMaximumSize(QSize(16777215, 100));
        verticalLayout_4 = new QVBoxLayout(statusGroup);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        statusLabel = new QLabel(statusGroup);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        verticalLayout_4->addWidget(statusLabel);


        verticalLayout_2->addWidget(statusGroup);

        tabWidget->addTab(connectionTab, QString());
        groundStationTab = new QWidget();
        groundStationTab->setObjectName(QString::fromUtf8("groundStationTab"));
        verticalLayout = new QVBoxLayout(groundStationTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        upload = new QGroupBox(groundStationTab);
        upload->setObjectName(QString::fromUtf8("upload"));
        verticalLayout_5 = new QVBoxLayout(upload);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        trackModeCombo = new QComboBox(upload);
        trackModeCombo->setObjectName(QString::fromUtf8("trackModeCombo"));
        trackModeCombo->setMinimumSize(QSize(100, 0));
        trackModeCombo->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(trackModeCombo, 4, 2, 1, 1);

        label_5 = new QLabel(upload);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        trackTargetCombo = new QComboBox(upload);
        trackTargetCombo->setObjectName(QString::fromUtf8("trackTargetCombo"));
        trackTargetCombo->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(trackTargetCombo, 6, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_4 = new QPushButton(upload);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(pushButton_4);

        autoRXPathLabel = new QLabel(upload);
        autoRXPathLabel->setObjectName(QString::fromUtf8("autoRXPathLabel"));

        horizontalLayout_8->addWidget(autoRXPathLabel);


        gridLayout->addLayout(horizontalLayout_8, 7, 2, 1, 1);

        label_6 = new QLabel(upload);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label_7 = new QLabel(upload);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        pushButton = new QPushButton(upload);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_14->addWidget(pushButton);

        pushButton_2 = new QPushButton(upload);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 0));
        pushButton_2->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_14->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(upload);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 0));
        pushButton_3->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_14->addWidget(pushButton_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_14, 1, 2, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        flightPathFileButton = new QPushButton(upload);
        flightPathFileButton->setObjectName(QString::fromUtf8("flightPathFileButton"));
        flightPathFileButton->setMinimumSize(QSize(100, 1));
        flightPathFileButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_13->addWidget(flightPathFileButton);

        groundStationUploadButton = new QPushButton(upload);
        groundStationUploadButton->setObjectName(QString::fromUtf8("groundStationUploadButton"));
        groundStationUploadButton->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(groundStationUploadButton);

        flightPathFileLabel = new QLabel(upload);
        flightPathFileLabel->setObjectName(QString::fromUtf8("flightPathFileLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(flightPathFileLabel->sizePolicy().hasHeightForWidth());
        flightPathFileLabel->setSizePolicy(sizePolicy);
        flightPathFileLabel->setMinimumSize(QSize(350, 0));
        flightPathFileLabel->setMaximumSize(QSize(500, 16777215));
        flightPathFileLabel->setFrameShape(QFrame::NoFrame);

        horizontalLayout_13->addWidget(flightPathFileLabel);


        gridLayout->addLayout(horizontalLayout_13, 2, 2, 1, 1);

        label_4 = new QLabel(upload);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 1, 1, 1);

        label_3 = new QLabel(upload);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_8 = new QLabel(upload);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        pushButton_5 = new QPushButton(upload);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButton_5, 0, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        groundStationUploadStatusLabel = new QLabel(upload);
        groundStationUploadStatusLabel->setObjectName(QString::fromUtf8("groundStationUploadStatusLabel"));

        horizontalLayout_9->addWidget(groundStationUploadStatusLabel);


        verticalLayout_5->addLayout(horizontalLayout_9);


        verticalLayout->addWidget(upload);

        groupBox = new QGroupBox(groundStationTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        serialMonitor = new QTextBrowser(groupBox);
        serialMonitor->setObjectName(QString::fromUtf8("serialMonitor"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serialMonitor->sizePolicy().hasHeightForWidth());
        serialMonitor->setSizePolicy(sizePolicy1);
        serialMonitor->setMaximumSize(QSize(16777215, 150));

        verticalLayout_6->addWidget(serialMonitor);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Clear = new QPushButton(groupBox);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        Clear->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(Clear);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(groupBox);

        tabWidget->addTab(groundStationTab, QString());
        satelliteTab = new QWidget();
        satelliteTab->setObjectName(QString::fromUtf8("satelliteTab"));
        tabWidget->addTab(satelliteTab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(flightPathFileButton, SIGNAL(clicked()), MainWindow, SLOT(selectFlightPathFile()));
        QObject::connect(upload, SIGNAL(clicked()), MainWindow, SLOT(uploadData()));
        QObject::connect(trackModeCombo, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(setTrackMode()));
        QObject::connect(serialConnectionButton, SIGNAL(clicked()), MainWindow, SLOT(toggleSerialPortConnection()));
        QObject::connect(Clear, &QPushButton::clicked, serialMonitor, qOverload<>(&QTextBrowser::clear));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(calibrate()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(returnToStart()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), MainWindow, SLOT(returnToStow()));
        QObject::connect(groundStationUploadButton, SIGNAL(clicked()), MainWindow, SLOT(uploadData()));
        QObject::connect(trackTargetCombo, SIGNAL(currentIndexChanged(QString)), MainWindow, SLOT(setTrackTarget()));
        QObject::connect(trackTargetCombo, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(setTrackTarget()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), MainWindow, SLOT(setAutoRXPath()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), MainWindow, SLOT(resetGroundStation()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        serialGroup->setTitle(QCoreApplication::translate("MainWindow", "Serial", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port Name:", nullptr));
        baudRateLabel->setText(QCoreApplication::translate("MainWindow", "Baud Rate:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Data Bits:", nullptr));
        stopBitsLabel->setText(QCoreApplication::translate("MainWindow", "Stop Bits:", nullptr));
        serialConnectionButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        statusGroup->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Not Connected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(connectionTab), QCoreApplication::translate("MainWindow", "Connection", nullptr));
        upload->setTitle(QCoreApplication::translate("MainWindow", "Configure", nullptr));
        trackModeCombo->setCurrentText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Mount:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Select..", nullptr));
        autoRXPathLabel->setText(QCoreApplication::translate("MainWindow", "<No folder selected>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Tracking Target:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "AutoRX Path:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Calibrate", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Return to Start", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Stow", nullptr));
        flightPathFileButton->setText(QCoreApplication::translate("MainWindow", "Open...", nullptr));
        groundStationUploadButton->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        flightPathFileLabel->setText(QCoreApplication::translate("MainWindow", "<No file selected>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Flight Path:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Tracking Mode:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "System:", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        groundStationUploadStatusLabel->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Monitor", nullptr));
        Clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(groundStationTab), QCoreApplication::translate("MainWindow", "Ground Station", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(satelliteTab), QCoreApplication::translate("MainWindow", "Satellite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
