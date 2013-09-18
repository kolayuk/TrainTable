/****************************************************************************
** Meta object code from reading C++ file 'stationgetter.h'
**
** Created: Fri 1. Mar 15:58:24 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stationgetter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stationgetter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StationGetter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
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
     333,   14,   14,   14, 0x0a,
     365,   14,   14,   14, 0x0a,
     396,   14,   14,   14, 0x0a,

 // methods: signature, parameters, type, tag, flags
     441,  436,   14,   14, 0x02,
     463,   14,   14,   14, 0x02,
     480,   14,   14,   14, 0x02,
     502,  496,   14,   14, 0x02,
     523,   14,   14,   14, 0x02,
     543,   14,   14,   14, 0x02,
     563,   14,   14,   14, 0x02,
     576,   14,   14,   14, 0x02,
     588,   14,   14,   14, 0x02,

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
    "GeoStationFound(QNetworkReply*)\0"
    "StationIDFound(QNetworkReply*)\0"
    "GotSeveralSearshResults(QNetworkReply*)\0"
    "name\0GetStationID(QString)\0StartPosSearch()\0"
    "StopPosSearch()\0index\0listViewPressed(int)\0"
    "SendGotoTimeTable()\0GetCachedStations()\0"
    "clearCache()\0incRadius()\0requestMap()\0"
};

void StationGetter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StationGetter *_t = static_cast<StationGetter *>(_o);
        switch (_id) {
        case 0: _t->coordinatesChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->timeouted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->stationRecieved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: _t->unableToGetStation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setListType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->gotoTimeTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: _t->needToIncRadius(); break;
        case 7: _t->showMap((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 8: _t->GeoStationFound((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 9: _t->StationIDFound((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->GotSeveralSearshResults((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 11: _t->GetStationID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->StartPosSearch(); break;
        case 13: _t->StopPosSearch(); break;
        case 14: _t->listViewPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->SendGotoTimeTable(); break;
        case 16: _t->GetCachedStations(); break;
        case 17: _t->clearCache(); break;
        case 18: _t->incRadius(); break;
        case 19: _t->requestMap(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StationGetter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StationGetter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StationGetter,
      qt_meta_data_StationGetter, &staticMetaObjectExtraData }
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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
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
