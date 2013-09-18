/****************************************************************************
** Meta object code from reading C++ file 'timetable.h'
**
** Created: Fri 1. Mar 16:29:50 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../timetable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timetable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Timetable[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,
      44,   40,   10,   10, 0x05,
      67,   63,   10,   10, 0x05,
      92,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     125,  116,   10,   10, 0x0a,
     153,   10,   10,   10, 0x0a,
     182,   10,   10,   10, 0x0a,
     217,   10,   10,   10, 0x0a,
     246,   11,   10,   10, 0x0a,

 // methods: signature, parameters, type, tag, flags
     266,   63,   10,   10, 0x02,
     288,  285,   10,   10, 0x02,
     316,   10,   10,   10, 0x02,
     338,  332,   10,   10, 0x02,
     367,  355,   10,   10, 0x02,
     385,  332,   10,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Timetable[] = {
    "Timetable\0\0state\0setTrainListState(int)\0"
    "txt\0setUIText(QString)\0dir\0"
    "setCurrentDirection(int)\0"
    "showDestinationDialog()\0url,name\0"
    "setStation(QString,QString)\0"
    "GotTrainList(QNetworkReply*)\0"
    "GotTrainsToStation(QNetworkReply*)\0"
    "GotTrainInfo(QNetworkReply*)\0"
    "storeListState(int)\0GoToDirection(int)\0"
    "to\0getTrainsToStation(QString)\0"
    "backToStation()\0index\0itemClicked(int)\0"
    "aShowOrHide\0ShowLongList(int)\0"
    "destinationSelected(int)\0"
};

const QMetaObject Timetable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Timetable,
      qt_meta_data_Timetable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Timetable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Timetable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Timetable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Timetable))
        return static_cast<void*>(const_cast< Timetable*>(this));
    return QObject::qt_metacast(_clname);
}

int Timetable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setTrainListState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setUIText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setCurrentDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: showDestinationDialog(); break;
        case 4: setStation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: GotTrainList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: GotTrainsToStation((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: GotTrainInfo((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: storeListState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: GoToDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: getTrainsToStation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: backToStation(); break;
        case 12: itemClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: ShowLongList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: destinationSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Timetable::setTrainListState(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Timetable::setUIText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Timetable::setCurrentDirection(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Timetable::showDestinationDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
