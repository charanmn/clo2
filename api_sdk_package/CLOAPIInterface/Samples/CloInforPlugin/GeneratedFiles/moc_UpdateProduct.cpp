/****************************************************************************
** Meta object code from reading C++ file 'UpdateProduct.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Products/UpdateProduct.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateProduct.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__UpdateProduct[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x08,
      48,   25,   25,   25, 0x08,
      71,   25,   25,   25, 0x08,
      86,   25,   25,   25, 0x08,
     113,  108,   25,   25, 0x08,
     140,  108,   25,   25, 0x08,
     170,  108,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__UpdateProduct[] = {
    "CLOPlugin::UpdateProduct\0\0"
    "updateInPlm_clicked()\0saveAndClose_clicked()\0"
    "back_clicked()\0closeWindow_clicked()\0"
    "item\0brandValueChanged(QString)\0"
    "divisionValueChanged(QString)\0"
    "categoryValueChanged(QString)\0"
};

void CLOPlugin::UpdateProduct::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpdateProduct *_t = static_cast<UpdateProduct *>(_o);
        switch (_id) {
        case 0: _t->updateInPlm_clicked(); break;
        case 1: _t->saveAndClose_clicked(); break;
        case 2: _t->back_clicked(); break;
        case 3: _t->closeWindow_clicked(); break;
        case 4: _t->brandValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->divisionValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->categoryValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CLOPlugin::UpdateProduct::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::UpdateProduct::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__UpdateProduct,
      qt_meta_data_CLOPlugin__UpdateProduct, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::UpdateProduct::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::UpdateProduct::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::UpdateProduct::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__UpdateProduct))
        return static_cast<void*>(const_cast< UpdateProduct*>(this));
    if (!strcmp(_clname, "Ui::UpdateProduct"))
        return static_cast< Ui::UpdateProduct*>(const_cast< UpdateProduct*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::UpdateProduct::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
