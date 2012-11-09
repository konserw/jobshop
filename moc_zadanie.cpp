/****************************************************************************
** Meta object code from reading C++ file 'zadanie.h'
**
** Created: Tue Nov 6 17:44:07 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "zadanie.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zadanie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_zadanie[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,    9,    8,    8, 0x05,
      33,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,    8,    8,    8, 0x0a,
      58,    8,    8,    8, 0x0a,
      80,    8,   65,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_zadanie[] = {
    "zadanie\0\0,\0next(qint32,zadanie*)\0"
    "finished(stat*)\0update()\0done()\0"
    "QGraphicsItem*\0gItem()\0"
};

void zadanie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        zadanie *_t = static_cast<zadanie *>(_o);
        switch (_id) {
        case 0: _t->next((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< zadanie*(*)>(_a[2]))); break;
        case 1: _t->finished((*reinterpret_cast< stat*(*)>(_a[1]))); break;
        case 2: _t->update(); break;
        case 3: _t->done(); break;
        case 4: { QGraphicsItem* _r = _t->gItem();
            if (_a[0]) *reinterpret_cast< QGraphicsItem**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData zadanie::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject zadanie::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_zadanie,
      qt_meta_data_zadanie, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &zadanie::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *zadanie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *zadanie::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_zadanie))
        return static_cast<void*>(const_cast< zadanie*>(this));
    return QObject::qt_metacast(_clname);
}

int zadanie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void zadanie::next(qint32 _t1, zadanie * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void zadanie::finished(stat * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
