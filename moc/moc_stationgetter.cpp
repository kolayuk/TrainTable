/****************************************************************************
** Meta object code from reading C++ file 'stationgetter.h'
**
** Created: Sat 5. Nov 21:04:47 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stationgetter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stationgetter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StationGetter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   15,   14,   14, 0x05,
      76,   70,   14,   14, 0x05,
     119,   95,   14,   14, 0x05,
     165,  158,   14,   14, 0x05,
     198,  193,   14,   14, 0x05,
     228,  215,   14,   14, 0x05,
     264,   14,   14,   14, 0x05,
     296,  282,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     338,  333,   14,   14, 0x0a,
     367,   14,   14,   14, 0x0a,
     380,   14,   14,   14, 0x0a,
     412,   14,   14,   14, 0x0a,
     443,   14,   14,   14, 0x0a,

 // methods: signature, parameters, type, tag, flags
     488,  483,   14,   14, 0x02,
     510,   14,   14,   14, 0x02,
     527,   14,   14,   14, 0x02,
     549,  543,   14,   14, 0x02,
     570,   14,   14,   14, 0x02,
     590,   14,   14,   14, 0x02,
     610,   14,   14,   14, 0x02,
     623,   14,   14,   14, 0x02,
     635,   14,   14,   14, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_StationGetter[] = {
    "StationGetter\0\0longitude,latitude\0"
    "coordinatesChanged(QString,QString)\0"
    "aType\0timeouted(QString)\0"
    "name,longitude,latitude\0"
    "stationRecieved(QString,double,double)\0"
    "reason\0unableToGetStation(QString)\0"
    "type\0setListType(int)\0url,name,gps\0"
    "gotoTimeTable(QString,QString,bool)\0"
    "needToIncRadius()\0l1,lo1,l2,lo2\0"
    "showMap(double,double,double,double)\0"
    "info\0PosUpdated(QGeoPositionInfo)\0"
    "TimeoutGPS()\0GeoStationFound(QNetworkReply*)\0"
    "StationIDFound(QNetworkReply*)\0"
    "GotSeveralSearshResults(QNetworkReply*)\0"
    "name\0GetStationID(QString)\0StartPosSearch()\0"
    "StopPosSearch()\0index\0listViewPressed(int)\0"
    "SendGotoTimeTable()\0GetCachedStations()\0"
    "clearCache()\0incRadius()\0requestMap()\0"
};

const QMetaObject StationGetter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StationGetter,
      qt_meta_data_StationGetter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StationGetter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StationGetter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StationGetter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StationGetter))
        return static_cast<void*>(const_cast< StationGetter*>(this));
    return QObject::qt_metacast(_clname);
}

int StationGetter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: coordinatesChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: timeouted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: stationRecieved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: unableToGetStation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: setListType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: gotoTimeTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: needToIncRadius(); break;
        case 7: showMap((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 8: PosUpdated((*reinterpret_cast< QGeoPositionInfo(*)>(_a[1]))); break;
        case 9: TimeoutGPS(); break;
        case 10: GeoStationFound((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 11: StationIDFound((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: GotSeveralSearshResults((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: GetStationID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: StartPosSearch(); break;
        case 15: StopPosSearch(); break;
        case 16: listViewPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: SendGotoTimeTable(); break;
        case 18: GetCachedStations(); break;
        case 19: clearCache(); break;
        case 20: incRadius(); break;
        case 21: requestMap(); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void StationGetter::coordinatesChanged(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StationGetter::timeouted(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StationGetter::stationRecieved(QString _t1, double _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void StationGetter::unableToGetStation(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StationGetter::setListType(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StationGetter::gotoTimeTable(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void StationGetter::needToIncRadius()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void StationGetter::showMap(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
