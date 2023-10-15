/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
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
    QSpacerItem *horizontalSpacer;
    QPushButton *connect;
    QGroupBox *statusGroup;
    QVBoxLayout *verticalLayout_4;
    QLabel *statusLabel;
    QWidget *groundStationTab;
    QVBoxLayout *verticalLayout;
    QGroupBox *upload;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *flightPathFileButton;
    QLabel *flightPathFileLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *groundStationUploadButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *groundStationUploadStatusLabel;
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
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        connect = new QPushButton(serialGroup);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setMaximumSize(QSize(16777215, 16777215));
        connect->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_4->addWidget(connect);


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
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        flightPathFileButton = new QPushButton(upload);
        flightPathFileButton->setObjectName(QString::fromUtf8("flightPathFileButton"));
        flightPathFileButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(flightPathFileButton);

        flightPathFileLabel = new QLabel(upload);
        flightPathFileLabel->setObjectName(QString::fromUtf8("flightPathFileLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(flightPathFileLabel->sizePolicy().hasHeightForWidth());
        flightPathFileLabel->setSizePolicy(sizePolicy);
        flightPathFileLabel->setFrameShape(QFrame::NoFrame);

        horizontalLayout_8->addWidget(flightPathFileLabel);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        groundStationUploadButton = new QPushButton(upload);
        groundStationUploadButton->setObjectName(QString::fromUtf8("groundStationUploadButton"));

        horizontalLayout_9->addWidget(groundStationUploadButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        groundStationUploadStatusLabel = new QLabel(upload);
        groundStationUploadStatusLabel->setObjectName(QString::fromUtf8("groundStationUploadStatusLabel"));

        horizontalLayout_9->addWidget(groundStationUploadStatusLabel);


        verticalLayout_5->addLayout(horizontalLayout_9);


        verticalLayout->addWidget(upload);

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
        QObject::connect(connect, SIGNAL(clicked()), MainWindow, SLOT(openSerialPort()));
        QObject::connect(upload, SIGNAL(clicked()), MainWindow, SLOT(uploadData()));
        QObject::connect(groundStationUploadButton, SIGNAL(clicked()), MainWindow, SLOT(uploadData()));

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
        connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        statusGroup->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Not Connected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(connectionTab), QCoreApplication::translate("MainWindow", "Connection", nullptr));
        upload->setTitle(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        flightPathFileButton->setText(QCoreApplication::translate("MainWindow", "Select Flight Path file...", nullptr));
        flightPathFileLabel->setText(QCoreApplication::translate("MainWindow", "<No file selected>", nullptr));
        groundStationUploadButton->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        groundStationUploadStatusLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(groundStationTab), QCoreApplication::translate("MainWindow", "Ground Station", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(satelliteTab), QCoreApplication::translate("MainWindow", "Satellite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
