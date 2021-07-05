/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_core_t {
    QByteArrayData data[13];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_core_t qt_meta_stringdata_core = {
    {
QT_MOC_LITERAL(0, 0, 4), // "core"
QT_MOC_LITERAL(1, 5, 13), // "signalToxData"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "signalSetId"
QT_MOC_LITERAL(4, 32, 16), // "signalClientInfo"
QT_MOC_LITERAL(5, 49, 8), // "uint32_t"
QT_MOC_LITERAL(6, 58, 16), // "TOX_MESSAGE_TYPE"
QT_MOC_LITERAL(7, 75, 14), // "const uint8_t*"
QT_MOC_LITERAL(8, 90, 6), // "size_t"
QT_MOC_LITERAL(9, 97, 14), // "signalSaveData"
QT_MOC_LITERAL(10, 112, 11), // "QByteArray&"
QT_MOC_LITERAL(11, 124, 15), // "signalSetStatus"
QT_MOC_LITERAL(12, 140, 17) // "signalSendMessage"

    },
    "core\0signalToxData\0\0signalSetId\0"
    "signalClientInfo\0uint32_t\0TOX_MESSAGE_TYPE\0"
    "const uint8_t*\0size_t\0signalSaveData\0"
    "QByteArray&\0signalSetStatus\0"
    "signalSendMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_core[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       3,    1,   51,    2, 0x06 /* Public */,
       4,    4,   54,    2, 0x06 /* Public */,
       9,    1,   63,    2, 0x06 /* Public */,
      11,    1,   66,    2, 0x06 /* Public */,
      12,    2,   69,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    2,    2,

       0        // eod
};

void core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<core *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalToxData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->signalSetId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->signalClientInfo((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< TOX_MESSAGE_TYPE(*)>(_a[2])),(*reinterpret_cast< const uint8_t*(*)>(_a[3])),(*reinterpret_cast< size_t(*)>(_a[4]))); break;
        case 3: _t->signalSaveData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->signalSetStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signalSendMessage((*reinterpret_cast< const uint32_t(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (core::*)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalToxData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (core::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalSetId)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (core::*)(uint32_t , TOX_MESSAGE_TYPE , const uint8_t * , size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalClientInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (core::*)(QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalSaveData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (core::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalSetStatus)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (core::*)(const uint32_t , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&core::signalSendMessage)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject core::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_core.data,
    qt_meta_data_core,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *core::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_core.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void core::signalToxData(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void core::signalSetId(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void core::signalClientInfo(uint32_t _t1, TOX_MESSAGE_TYPE _t2, const uint8_t * _t3, size_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void core::signalSaveData(QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void core::signalSetStatus(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void core::signalSendMessage(const uint32_t _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
