/****************************************************************************
** Meta object code from reading C++ file 'ProductSearch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Products/ProductSearch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProductSearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__ProductSearch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   25,   25,   25, 0x08,
      69,   25,   25,   25, 0x08,
      86,   25,   25,   25, 0x08,
     105,  100,   25,   25, 0x08,
     132,  100,   25,   25, 0x08,
     162,  100,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__ProductSearch[] = {
    "CLOPlugin::ProductSearch\0\0"
    "CreateProductBackClicked()\0SearchClicked()\0"
    "Cancel_clicked()\0backclicked()\0item\0"
    "brandValueChanged(QString)\0"
    "divisionValueChanged(QString)\0"
    "categoryValueChanged(QString)\0"
};

void CLOPlugin::ProductSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProductSearch *_t = static_cast<ProductSearch *>(_o);
        switch (_id) {
        case 0: _t->CreateProductBackClicked(); break;
        case 1: _t->SearchClicked(); break;
        case 2: _t->Cancel_clicked(); break;
        case 3: _t->backclicked(); break;
        case 4: _t->brandValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->divisionValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->categoryValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CLOPlugin::ProductSearch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::ProductSearch::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__ProductSearch,
      qt_meta_data_CLOPlugin__ProductSearch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::ProductSearch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::ProductSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::ProductSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__ProductSearch))
        return static_cast<void*>(const_cast< ProductSearch*>(this));
    if (!strcmp(_clname, "Ui::ProductSearch"))
        return static_cast< Ui::ProductSearch*>(const_cast< ProductSearch*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::ProductSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void CLOPlugin::ProductSearch::CreateProductBackClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
