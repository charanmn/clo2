/****************************************************************************
** Meta object code from reading C++ file 'APISignInDialogSample.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../classes/APISignInDialogSample.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'APISignInDialogSample.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOAPISample__APISigninDialogSample[] = {

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
      37,   36,   36,   36, 0x09,
      48,   36,   36,   36, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CLOAPISample__APISigninDialogSample[] = {
    "CLOAPISample::APISigninDialogSample\0"
    "\0OnAccept()\0OnReject()\0"
};

void CLOAPISample::APISigninDialogSample::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        APISigninDialogSample *_t = static_cast<APISigninDialogSample *>(_o);
        switch (_id) {
        case 0: _t->OnAccept(); break;
        case 1: _t->OnReject(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOAPISample::APISigninDialogSample::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOAPISample::APISigninDialogSample::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOAPISample__APISigninDialogSample,
      qt_meta_data_CLOAPISample__APISigninDialogSample, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOAPISample::APISigninDialogSample::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOAPISample::APISigninDialogSample::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOAPISample::APISigninDialogSample::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOAPISample__APISigninDialogSample))
        return static_cast<void*>(const_cast< APISigninDialogSample*>(this));
    if (!strcmp(_clname, "Ui::DialogSignIn"))
        return static_cast< Ui::DialogSignIn*>(const_cast< APISigninDialogSample*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOAPISample::APISigninDialogSample::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
