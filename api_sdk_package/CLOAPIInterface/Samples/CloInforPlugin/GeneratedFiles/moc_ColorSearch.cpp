/****************************************************************************
** Meta object code from reading C++ file 'ColorSearch.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/Colors/ColorSearch.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorSearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__ColorSearch[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      41,   23,   23,   23, 0x08,
      58,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__ColorSearch[] = {
    "CLOPlugin::ColorSearch\0\0Search_clicked()\0"
    "Cancel_clicked()\0back_clicked()\0"
};

void CLOPlugin::ColorSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColorSearch *_t = static_cast<ColorSearch *>(_o);
        switch (_id) {
        case 0: _t->Search_clicked(); break;
        case 1: _t->Cancel_clicked(); break;
        case 2: _t->back_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::ColorSearch::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::ColorSearch::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__ColorSearch,
      qt_meta_data_CLOPlugin__ColorSearch, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::ColorSearch::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::ColorSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::ColorSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__ColorSearch))
        return static_cast<void*>(const_cast< ColorSearch*>(this));
    if (!strcmp(_clname, "Ui::ColorSearchDialog"))
        return static_cast< Ui::ColorSearchDialog*>(const_cast< ColorSearch*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::ColorSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
