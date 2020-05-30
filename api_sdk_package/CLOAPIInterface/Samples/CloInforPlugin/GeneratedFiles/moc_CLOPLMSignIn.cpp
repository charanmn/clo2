/****************************************************************************
** Meta object code from reading C++ file 'CLOPLMSignIn.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Authentication/CLOPLMSignIn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CLOPLMSignIn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__CLOPLMSignIn[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      52,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__CLOPLMSignIn[] = {
    "CLOPlugin::CLOPLMSignIn\0\0"
    "ValidateLoginCredentials()\0cancel_Clicked()\0"
};

void CLOPlugin::CLOPLMSignIn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CLOPLMSignIn *_t = static_cast<CLOPLMSignIn *>(_o);
        switch (_id) {
        case 0: _t->ValidateLoginCredentials(); break;
        case 1: _t->cancel_Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::CLOPLMSignIn::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::CLOPLMSignIn::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__CLOPLMSignIn,
      qt_meta_data_CLOPlugin__CLOPLMSignIn, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::CLOPLMSignIn::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::CLOPLMSignIn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::CLOPLMSignIn::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__CLOPLMSignIn))
        return static_cast<void*>(const_cast< CLOPLMSignIn*>(this));
    if (!strcmp(_clname, "Ui::CLOPLMSignIn"))
        return static_cast< Ui::CLOPLMSignIn*>(const_cast< CLOPLMSignIn*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::CLOPLMSignIn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
