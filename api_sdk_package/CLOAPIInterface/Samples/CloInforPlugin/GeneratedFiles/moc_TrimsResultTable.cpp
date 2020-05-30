/****************************************************************************
** Meta object code from reading C++ file 'TrimsResultTable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Materials/Trims/TrimsResultTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrimsResultTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__TrimsResultTable[] = {

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
      47,   28,   28,   28, 0x08,
      64,   28,   28,   28, 0x08,
      80,   28,   28,   28, 0x08,
     103,   28,   28,   28, 0x08,
     122,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__TrimsResultTable[] = {
    "CLOPlugin::TrimsResultTable\0\0"
    "DownloadClicked()\0Cancel_clicked()\0"
    "OnBackClicked()\0callCheckBoxSelected()\0"
    "SelectAllClicked()\0DeSelectAllClicked()\0"
};

void CLOPlugin::TrimsResultTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TrimsResultTable *_t = static_cast<TrimsResultTable *>(_o);
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

const QMetaObjectExtraData CLOPlugin::TrimsResultTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::TrimsResultTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__TrimsResultTable,
      qt_meta_data_CLOPlugin__TrimsResultTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::TrimsResultTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::TrimsResultTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::TrimsResultTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__TrimsResultTable))
        return static_cast<void*>(const_cast< TrimsResultTable*>(this));
    if (!strcmp(_clname, "Ui::TrimsResultTable"))
        return static_cast< Ui::TrimsResultTable*>(const_cast< TrimsResultTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::TrimsResultTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
