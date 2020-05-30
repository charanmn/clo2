/****************************************************************************
** Meta object code from reading C++ file 'FabricsResultTable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Materials/Fabrics/FabricsResultTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FabricsResultTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__ResultTable[] = {

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
      24,   23,   23,   23, 0x08,
      42,   23,   23,   23, 0x08,
      59,   23,   23,   23, 0x08,
      75,   23,   23,   23, 0x08,
      98,   23,   23,   23, 0x08,
     117,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__ResultTable[] = {
    "CLOPlugin::ResultTable\0\0DownloadClicked()\0"
    "Cancel_clicked()\0OnBackClicked()\0"
    "callCheckBoxSelected()\0SelectAllClicked()\0"
    "DeSelectAllClicked()\0"
};

void CLOPlugin::ResultTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ResultTable *_t = static_cast<ResultTable *>(_o);
        switch (_id) {
        case 0: _t->DownloadClicked(); break;
        case 1: _t->Cancel_clicked(); break;
        case 2: _t->OnBackClicked(); break;
        case 3: _t->callCheckBoxSelected(); break;
        case 4: _t->SelectAllClicked(); break;
        case 5: _t->DeSelectAllClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::ResultTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::ResultTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__ResultTable,
      qt_meta_data_CLOPlugin__ResultTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::ResultTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::ResultTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::ResultTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__ResultTable))
        return static_cast<void*>(const_cast< ResultTable*>(this));
    if (!strcmp(_clname, "Ui::ResultTable"))
        return static_cast< Ui::ResultTable*>(const_cast< ResultTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::ResultTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
