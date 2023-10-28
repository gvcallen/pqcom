/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../include/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[38];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 20), // "selectFlightPathFile"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 26), // "toggleSerialPortConnection"
QT_MOC_LITERAL(60, 16), // "serialBytesReady"
QT_MOC_LITERAL(77, 17), // "autoRXOutputReady"
QT_MOC_LITERAL(95, 16), // "autoRXErrorReady"
QT_MOC_LITERAL(112, 14), // "autoRXLogCheck"
QT_MOC_LITERAL(127, 16), // "autoRXLogChanged"
QT_MOC_LITERAL(144, 13), // "setAutoRXPath"
QT_MOC_LITERAL(158, 7), // "onClose"
QT_MOC_LITERAL(166, 18), // "resetGroundStation"
QT_MOC_LITERAL(185, 9), // "calibrate"
QT_MOC_LITERAL(195, 13), // "returnToStart"
QT_MOC_LITERAL(209, 12), // "returnToStow"
QT_MOC_LITERAL(222, 10), // "uploadData"
QT_MOC_LITERAL(233, 12), // "setTrackMode"
QT_MOC_LITERAL(246, 14), // "setTrackTarget"
QT_MOC_LITERAL(261, 12) // "showModified"

    },
    "MainWindow\0selectFlightPathFile\0\0"
    "toggleSerialPortConnection\0serialBytesReady\0"
    "autoRXOutputReady\0autoRXErrorReady\0"
    "autoRXLogCheck\0autoRXLogChanged\0"
    "setAutoRXPath\0onClose\0resetGroundStation\0"
    "calibrate\0returnToStart\0returnToStow\0"
    "uploadData\0setTrackMode\0setTrackTarget\0"
    "showModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x0a,    1 /* Public */,
       3,    0,  117,    2, 0x0a,    2 /* Public */,
       4,    0,  118,    2, 0x0a,    3 /* Public */,
       5,    0,  119,    2, 0x0a,    4 /* Public */,
       6,    0,  120,    2, 0x0a,    5 /* Public */,
       7,    0,  121,    2, 0x0a,    6 /* Public */,
       8,    0,  122,    2, 0x0a,    7 /* Public */,
       9,    0,  123,    2, 0x0a,    8 /* Public */,
      10,    0,  124,    2, 0x0a,    9 /* Public */,
      11,    0,  125,    2, 0x0a,   10 /* Public */,
      12,    0,  126,    2, 0x0a,   11 /* Public */,
      13,    0,  127,    2, 0x0a,   12 /* Public */,
      14,    0,  128,    2, 0x0a,   13 /* Public */,
      15,    0,  129,    2, 0x0a,   14 /* Public */,
      16,    0,  130,    2, 0x0a,   15 /* Public */,
      17,    0,  131,    2, 0x0a,   16 /* Public */,
      18,    0,  132,    2, 0x0a,   17 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectFlightPathFile(); break;
        case 1: _t->toggleSerialPortConnection(); break;
        case 2: _t->serialBytesReady(); break;
        case 3: _t->autoRXOutputReady(); break;
        case 4: _t->autoRXErrorReady(); break;
        case 5: _t->autoRXLogCheck(); break;
        case 6: _t->autoRXLogChanged(); break;
        case 7: _t->setAutoRXPath(); break;
        case 8: _t->onClose(); break;
        case 9: _t->resetGroundStation(); break;
        case 10: _t->calibrate(); break;
        case 11: _t->returnToStart(); break;
        case 12: _t->returnToStow(); break;
        case 13: _t->uploadData(); break;
        case 14: _t->setTrackMode(); break;
        case 15: _t->setTrackTarget(); break;
        case 16: _t->showModified(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
