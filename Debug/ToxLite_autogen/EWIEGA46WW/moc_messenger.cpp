/****************************************************************************
** Meta object code from reading C++ file 'messenger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../messenger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messenger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_messenger_t {
    QByteArrayData data[29];
    char stringdata0[409];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_messenger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_messenger_t qt_meta_stringdata_messenger = {
    {
QT_MOC_LITERAL(0, 0, 9), // "messenger"
QT_MOC_LITERAL(1, 10, 17), // "signalSetUserData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15), // "signalCheckUser"
QT_MOC_LITERAL(4, 45, 16), // "signalAddRegUser"
QT_MOC_LITERAL(5, 62, 10), // "signalSend"
QT_MOC_LITERAL(6, 73, 7), // "message"
QT_MOC_LITERAL(7, 81, 13), // "signalGetPort"
QT_MOC_LITERAL(8, 95, 8), // "nameUser"
QT_MOC_LITERAL(9, 104, 18), // "slotUpdateUserList"
QT_MOC_LITERAL(10, 123, 4), // "name"
QT_MOC_LITERAL(11, 128, 8), // "password"
QT_MOC_LITERAL(12, 137, 2), // "ip"
QT_MOC_LITERAL(13, 140, 4), // "port"
QT_MOC_LITERAL(14, 145, 23), // "slotOperationSuccessful"
QT_MOC_LITERAL(15, 169, 4), // "code"
QT_MOC_LITERAL(16, 174, 9), // "slotError"
QT_MOC_LITERAL(17, 184, 21), // "slotConnectSuccessful"
QT_MOC_LITERAL(18, 206, 14), // "slotNewMessage"
QT_MOC_LITERAL(19, 221, 6), // "sender"
QT_MOC_LITERAL(20, 228, 23), // "on_login_signup_clicked"
QT_MOC_LITERAL(21, 252, 24), // "on_signup_button_clicked"
QT_MOC_LITERAL(22, 277, 23), // "on_login_button_clicked"
QT_MOC_LITERAL(23, 301, 23), // "on_signup_login_clicked"
QT_MOC_LITERAL(24, 325, 19), // "on_input_textEdited"
QT_MOC_LITERAL(25, 345, 4), // "arg1"
QT_MOC_LITERAL(26, 350, 15), // "on_send_clicked"
QT_MOC_LITERAL(27, 366, 30), // "on_listUser_currentTextChanged"
QT_MOC_LITERAL(28, 397, 11) // "currentText"

    },
    "messenger\0signalSetUserData\0\0"
    "signalCheckUser\0signalAddRegUser\0"
    "signalSend\0message\0signalGetPort\0"
    "nameUser\0slotUpdateUserList\0name\0"
    "password\0ip\0port\0slotOperationSuccessful\0"
    "code\0slotError\0slotConnectSuccessful\0"
    "slotNewMessage\0sender\0on_login_signup_clicked\0"
    "on_signup_button_clicked\0"
    "on_login_button_clicked\0on_signup_login_clicked\0"
    "on_input_textEdited\0arg1\0on_send_clicked\0"
    "on_listUser_currentTextChanged\0"
    "currentText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_messenger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       3,    2,  104,    2, 0x06 /* Public */,
       4,    4,  109,    2, 0x06 /* Public */,
       5,    1,  118,    2, 0x06 /* Public */,
       7,    1,  121,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    4,  124,    2, 0x0a /* Public */,
      14,    1,  133,    2, 0x08 /* Private */,
      16,    1,  136,    2, 0x08 /* Private */,
      17,    2,  139,    2, 0x08 /* Private */,
      18,    2,  144,    2, 0x08 /* Private */,
      20,    0,  149,    2, 0x08 /* Private */,
      21,    0,  150,    2, 0x08 /* Private */,
      22,    0,  151,    2, 0x08 /* Private */,
      23,    0,  152,    2, 0x08 /* Private */,
      24,    1,  153,    2, 0x08 /* Private */,
      26,    0,  156,    2, 0x08 /* Private */,
      27,    1,  157,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

void messenger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<messenger *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalSetUserData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->signalCheckUser((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->signalAddRegUser((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 3: _t->signalSend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->signalGetPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slotUpdateUserList((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 6: _t->slotOperationSuccessful((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->slotError((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: _t->slotConnectSuccessful((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->slotNewMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->on_login_signup_clicked(); break;
        case 11: _t->on_signup_button_clicked(); break;
        case 12: _t->on_login_button_clicked(); break;
        case 13: _t->on_signup_login_clicked(); break;
        case 14: _t->on_input_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_send_clicked(); break;
        case 16: _t->on_listUser_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (messenger::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&messenger::signalSetUserData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (messenger::*)(const QString & , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&messenger::signalCheckUser)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (messenger::*)(const QString & , const QString & , const QString & , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&messenger::signalAddRegUser)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (messenger::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&messenger::signalSend)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (messenger::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&messenger::signalGetPort)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject messenger::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_messenger.data,
    qt_meta_data_messenger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *messenger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *messenger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_messenger.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int messenger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void messenger::signalSetUserData(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void messenger::signalCheckUser(const QString & _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void messenger::signalAddRegUser(const QString & _t1, const QString & _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void messenger::signalSend(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void messenger::signalGetPort(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
