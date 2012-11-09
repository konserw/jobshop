/****************************************************************************
** Meta object code from reading C++ file 'wykres.h'
**
** Created: Tue Oct 16 19:09:08 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "wykres.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wykres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wykres[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x0a,
      30,   28,    7,    7, 0x0a,
      53,   46,    7,    7, 0x0a,
      62,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_wykres[] = {
    "wykres\0\0s\0setText(QString&)\0x\0"
    "finished(stat*)\0maszyn\0set(int)\0up(int)\0"
};

void wykres::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        wykres *_t = static_cast<wykres *>(_o);
        switch (_id) {
        case 0: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< stat*(*)>(_a[1]))); break;
        case 2: _t->set((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->up((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData wykres::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject wykres::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_wykres,
      qt_meta_data_wykres, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wykres::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wykres::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wykres::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wykres))
        return static_cast<void*>(const_cast< wykres*>(this));
    return QDialog::qt_metacast(_clname);
}

int wykres::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
