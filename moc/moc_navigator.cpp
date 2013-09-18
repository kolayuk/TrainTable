/****************************************************************************
** Meta object code from reading C++ file 'navigator.h'
**
** Created: Sat 5. Nov 15:34:14 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../navigator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Navigator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      40,   22,   10,   10, 0x05,
      84,   22,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   10,   10,   10, 0x08,
     155,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Navigator[] = {
    "Navigator\0\0finished()\0error,errorString\0"
    "searchError(QGeoSearchReply::Error,QString)\0"
    "routingError(QGeoRouteReply::Error,QString)\0"
    "on_addressSearchFinished()\0"
    "on_routingFinished()\0"
};

const QMetaObject Navigator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Navigator,
      qt_meta_data_Navigator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Navigator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Navigator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Navigator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Navigator))
        return static_cast<void*>(const_cast< Navigator*>(this));
    return QObject::qt_metacast(_clname);
}

int Navigator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished(); break;
        case 1: searchError((*reinterpret_cast< QGeoSearchReply::Error(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: routingError((*reinterpret_cast< QGeoRouteReply::Error(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: on_addressSearchFinished(); break;
        case 4: on_routingFinished(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Navigator::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Navigator::searchError(QGeoSearchReply::Error _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Navigator::routingError(QGeoRouteReply::Error _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
