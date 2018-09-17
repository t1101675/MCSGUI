/****************************************************************************
** Meta object code from reading C++ file 'mcsgraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mcsgui/mcsgraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcsgraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MCSGraph_t {
    QByteArrayData data[20];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MCSGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MCSGraph_t qt_meta_stringdata_MCSGraph = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MCSGraph"
QT_MOC_LITERAL(1, 9, 18), // "pipeClickedInGraph"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "Pipe::PipeInfo"
QT_MOC_LITERAL(4, 44, 4), // "info"
QT_MOC_LITERAL(5, 49, 14), // "outSideClicked"
QT_MOC_LITERAL(6, 64, 13), // "calulateBegin"
QT_MOC_LITERAL(7, 78, 11), // "calulateEnd"
QT_MOC_LITERAL(8, 90, 12), // "notConnected"
QT_MOC_LITERAL(9, 103, 11), // "pipeClicked"
QT_MOC_LITERAL(10, 115, 1), // "i"
QT_MOC_LITERAL(11, 117, 17), // "pipeDoubleClicked"
QT_MOC_LITERAL(12, 135, 13), // "graphModified"
QT_MOC_LITERAL(13, 149, 13), // "setAutoRecalc"
QT_MOC_LITERAL(14, 163, 12), // "setDrawSpeed"
QT_MOC_LITERAL(15, 176, 14), // "showSpeedColor"
QT_MOC_LITERAL(16, 191, 15), // "showConcenColor"
QT_MOC_LITERAL(17, 207, 13), // "generateGraph"
QT_MOC_LITERAL(18, 221, 8), // "double[]"
QT_MOC_LITERAL(19, 230, 3) // "out"

    },
    "MCSGraph\0pipeClickedInGraph\0\0"
    "Pipe::PipeInfo\0info\0outSideClicked\0"
    "calulateBegin\0calulateEnd\0notConnected\0"
    "pipeClicked\0i\0pipeDoubleClicked\0"
    "graphModified\0setAutoRecalc\0setDrawSpeed\0"
    "showSpeedColor\0showConcenColor\0"
    "generateGraph\0double[]\0out"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MCSGraph[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    0,   84,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      12,    0,   92,    2, 0x0a /* Public */,
      13,    1,   93,    2, 0x0a /* Public */,
      14,    1,   96,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x0a /* Public */,
      17,    1,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void MCSGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MCSGraph *_t = static_cast<MCSGraph *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pipeClickedInGraph((*reinterpret_cast< Pipe::PipeInfo(*)>(_a[1]))); break;
        case 1: _t->outSideClicked(); break;
        case 2: _t->calulateBegin(); break;
        case 3: _t->calulateEnd(); break;
        case 4: _t->notConnected(); break;
        case 5: _t->pipeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->pipeDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->graphModified(); break;
        case 8: _t->setAutoRecalc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setDrawSpeed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->showSpeedColor(); break;
        case 11: _t->showConcenColor(); break;
        case 12: _t->generateGraph((*reinterpret_cast< double(*)[]>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MCSGraph::*)(Pipe::PipeInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCSGraph::pipeClickedInGraph)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MCSGraph::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCSGraph::outSideClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MCSGraph::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCSGraph::calulateBegin)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MCSGraph::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCSGraph::calulateEnd)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MCSGraph::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCSGraph::notConnected)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MCSGraph::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MCSGraph.data,
      qt_meta_data_MCSGraph,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MCSGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MCSGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MCSGraph.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MCSGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MCSGraph::pipeClickedInGraph(Pipe::PipeInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MCSGraph::outSideClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MCSGraph::calulateBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MCSGraph::calulateEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MCSGraph::notConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
