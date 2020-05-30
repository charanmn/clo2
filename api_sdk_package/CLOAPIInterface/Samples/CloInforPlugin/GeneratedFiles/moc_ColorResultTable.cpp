/****************************************************************************
** Meta object code from reading C++ file 'ColorResultTable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Colors/ColorResultTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorResultTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__ColorResultTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x08,
      60,   28,   28,   28, 0x08,
      93,   28,   28,   28, 0x08,
     128,   28,   28,   28, 0x08,
     151,   28,   28,   28, 0x08,
     170,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__ColorResultTable[] = {
    "CLOPlugin::ColorResultTable\0\0"
    "colorResultTableBack_clicked()\0"
    "colorResultTableCancel_clicked()\0"
    "colorResultTableDownload_clicked()\0"
    "callCheckBoxSelected()\0SelectAllClicked()\0"
    "DeSelectAllClicked()\0"
};

void CLOPlugin::ColorResultTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColorResultTable *_t = static_cast<ColorResultTable *>(_o);
        switch (_id) {
        case 0: _t->colorResultTableBack_clicked(); break;
        case 1: _t->colorResultTableCancel_clicked(); break;
        case 2: _t->colorResultTableDownload_clicked(); break;
        case 3: _t->callCheckBoxSelected(); break;
        case 4: _t->SelectAllClicked(); break;
        case 5: _t->DeSelectAllClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::ColorResultTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::ColorResultTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__ColorResultTable,
      qt_meta_data_CLOPlugin__ColorResultTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::ColorResultTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::ColorResultTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::ColorResultTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__ColorResultTable))
        return static_cast<void*>(const_cast< ColorResultTable*>(this));
    if (!strcmp(_clname, "Ui::ColorResultTable"))
        return static_cast< Ui::ColorResultTable*>(const_cast< ColorResultTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::ColorResultTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
