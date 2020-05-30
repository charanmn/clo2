/****************************************************************************
** Meta object code from reading C++ file 'TrimsSearch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Materials/Trims/TrimsSearch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrimsSearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__TrimsSearch[] = {

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
      24,   23,   23,   23, 0x08,
      41,   23,   23,   23, 0x08,
      58,   23,   23,   23, 0x08,
      78,   73,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__TrimsSearch[] = {
    "CLOPlugin::TrimsSearch\0\0Search_clicked()\0"
    "Cancel_clicked()\0back_clicked()\0item\0"
    "BrandValueChanged(QString)\0"
};

void CLOPlugin::TrimsSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TrimsSearch *_t = static_cast<TrimsSearch *>(_o);
        switch (_id) {
        case 0: _t->Search_clicked(); break;
        case 1: _t->Cancel_clicked(); break;
        case 2: _t->back_clicked(); break;
        case 3: _t->BrandValueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CLOPlugin::TrimsSearch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::TrimsSearch::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__TrimsSearch,
      qt_meta_data_CLOPlugin__TrimsSearch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::TrimsSearch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::TrimsSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::TrimsSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__TrimsSearch))
        return static_cast<void*>(const_cast< TrimsSearch*>(this));
    if (!strcmp(_clname, "Ui::TrimsSearch"))
        return static_cast< Ui::TrimsSearch*>(const_cast< TrimsSearch*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::TrimsSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
