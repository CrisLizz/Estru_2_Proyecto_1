/****************************************************************************
** Meta object code from reading C++ file 'protagonista.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../OneDrive - Universidad Tecnologica Centroamericana/Documents/QT Proyects/Proyecto1_Estru2/protagonista.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protagonista.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12ProtagonistaE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12ProtagonistaE = QtMocHelpers::stringData(
    "Protagonista",
    "Animacion",
    "",
    "moverDerecha",
    "moverIzquierda",
    "moverArriba",
    "moverAbajo",
    "Detener",
    "Caminar",
    "attack",
    "addLifes",
    "death",
    "takeLifes",
    "getLifes"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12ProtagonistaE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x0a,    1 /* Public */,
       3,    0,   87,    2, 0x0a,    2 /* Public */,
       4,    0,   88,    2, 0x0a,    3 /* Public */,
       5,    0,   89,    2, 0x0a,    4 /* Public */,
       6,    0,   90,    2, 0x0a,    5 /* Public */,
       7,    0,   91,    2, 0x0a,    6 /* Public */,
       8,    0,   92,    2, 0x0a,    7 /* Public */,
       9,    0,   93,    2, 0x0a,    8 /* Public */,
      10,    0,   94,    2, 0x0a,    9 /* Public */,
      11,    0,   95,    2, 0x0a,   10 /* Public */,
      12,    0,   96,    2, 0x0a,   11 /* Public */,
      13,    0,   97,    2, 0x0a,   12 /* Public */,

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
    QMetaType::Int,

       0        // eod
};

Q_CONSTINIT const QMetaObject Protagonista::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN12ProtagonistaE.offsetsAndSizes,
    qt_meta_data_ZN12ProtagonistaE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12ProtagonistaE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Protagonista, std::true_type>,
        // method 'Animacion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverDerecha'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverIzquierda'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverArriba'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moverAbajo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Detener'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Caminar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addLifes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'death'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'takeLifes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getLifes'
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void Protagonista::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Protagonista *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->Animacion(); break;
        case 1: _t->moverDerecha(); break;
        case 2: _t->moverIzquierda(); break;
        case 3: _t->moverArriba(); break;
        case 4: _t->moverAbajo(); break;
        case 5: _t->Detener(); break;
        case 6: _t->Caminar(); break;
        case 7: _t->attack(); break;
        case 8: _t->addLifes(); break;
        case 9: _t->death(); break;
        case 10: _t->takeLifes(); break;
        case 11: { int _r = _t->getLifes();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *Protagonista::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Protagonista::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12ProtagonistaE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int Protagonista::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
