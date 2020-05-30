/****************************************************************************
** Meta object code from reading C++ file 'ProductResultTable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Products/ProductResultTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProductResultTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__ProductResultTable[] = {

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
      31,   30,   30,   30, 0x08,
      64,   30,   30,   30, 0x08,
      99,   30,   30,   30, 0x08,
     136,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__ProductResultTable[] = {
    "CLOPlugin::ProductResultTable\0\0"
    "productResultTableBack_clicked()\0"
    "productResultTableCancel_clicked()\0"
    "productResultTableDownload_clicked()\0"
    "callRadioSelected()\0"
};

void CLOPlugin::ProductResultTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProductResultTable *_t = static_cast<ProductResultTable *>(_o);
        switch (_id) {
        case 0: _t->productResultTableBack_clicked(); break;
        case 1: _t->productResultTableCancel_clicked(); break;
        case 2: _t->productResultTableDownload_clicked(); break;
        case 3: _t->callRadioSelected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::ProductResultTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::ProductResultTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__ProductResultTable,
      qt_meta_data_CLOPlugin__ProductResultTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::ProductResultTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::ProductResultTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::ProductResultTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__ProductResultTable))
        return static_cast<void*>(const_cast< ProductResultTable*>(this));
    if (!strcmp(_clname, "Ui::ProductResultTable"))
        return static_cast< Ui::ProductResultTable*>(const_cast< ProductResultTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::ProductResultTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
