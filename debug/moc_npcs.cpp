/****************************************************************************
** Meta object code from reading C++ file 'npcs.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../OneDrive - Universidad Tecnologica Centroamericana/Documents/QT Proyects/Proyecto1_Estru2/npcs.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'npcs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN4NpcsE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN4NpcsE = QtMocHelpers::stringData(
    "Npcs",
    "Animacion",
    "",
    "moverIzquierda",
    "moverDerecha",
    "Detener",
    "Caminar",
    "attack",
    "death",
    "addLifes",
    "takeLifes",
    "getLifes"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN4NpcsE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    0,   78,    2, 0x0a,    5 /* Public */,
       7,    0,   79,    2, 0x0a,    6 /* Public */,
       8,    0,   80,    2, 0x0a,    7 /* Public */,
       9,    0,   81,    2, 0x0a,    8 /* Public */,
      10,    0,   82,    2, 0x0a,    9 /* Public */,
      11,    0,   83,    2, 0x0a,   10 /* Public */,

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
    QMetaType::Int,

       0        // eod
};

Q_CONSTINIT const QMetaObject Npcs::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN4NpcsE.offsetsAndSizes,
    qt_meta_data_ZN4NpcsE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN4NpcsE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Npcs, std::true_type>,
        // method 'Animacion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverIzquierda'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverDerecha'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Detener'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Caminar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'death'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addLifes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'takeLifes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getLifes'
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void Npcs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Npcs *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->Animacion(); break;
        case 1: _t->moverIzquierda(); break;
        case 2: _t->moverDerecha(); break;
        case 3: _t->Detener(); break;
        case 4: _t->Caminar(); break;
        case 5: _t->attack(); break;
        case 6: _t->death(); break;
        case 7: _t->addLifes(); break;
        case 8: _t->takeLifes(); break;
        case 9: { int _r = _t->getLifes();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *Npcs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Npcs::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN4NpcsE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int Npcs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
