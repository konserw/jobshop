/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Tue Nov 6 17:44:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      19,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   27,   11,   11, 0x0a,
      86,   11,   11,   11, 0x0a,
      93,   11,   11,   11, 0x0a,
     101,   11,   11,   11, 0x0a,
     113,  111,   11,   11, 0x0a,
     135,   11,   11,   11, 0x0a,
     151,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0tick()\0tick2()\0"
    "start,due,marszruty\0"
    "more(qint32,qint32,QList<marszruta*>&)\0"
    "more()\0solve()\0rout(int)\0,\0"
    "next(qint32,zadanie*)\0finished(stat*)\0"
    "imp()\0exp()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->tick(); break;
        case 1: _t->tick2(); break;
        case 2: _t->more((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< QList<marszruta*>(*)>(_a[3]))); break;
        case 3: _t->more(); break;
        case 4: _t->solve(); break;
        case 5: _t->rout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->next((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< zadanie*(*)>(_a[2]))); break;
        case 7: _t->finished((*reinterpret_cast< stat*(*)>(_a[1]))); break;
        case 8: _t->imp(); break;
        case 9: _t->exp(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::tick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::tick2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
