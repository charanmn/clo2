/****************************************************************************
** Meta object code from reading C++ file 'DesignSuite.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CLO_PLUGIN/INFOR/DesignSuite/DesignSuite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DesignSuite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLOPlugin__DesignSuite[] = {

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
      24,   23,   23,   23, 0x08,
      41,   23,   23,   23, 0x08,
      55,   23,   23,   23, 0x08,
      74,   23,   23,   23, 0x08,
      94,   23,   23,   23, 0x08,
     114,   23,   23,   23, 0x08,
     136,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CLOPlugin__DesignSuite[] = {
    "CLOPlugin::DesignSuite\0\0materialSearch()\0"
    "closeWindow()\0clickedCreatProd()\0"
    "clickedUpdateProd()\0clickedSearchProd()\0"
    "clickedSearchColors()\0clickedSearchTrims()\0"
};

void CLOPlugin::DesignSuite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DesignSuite *_t = static_cast<DesignSuite *>(_o);
        switch (_id) {
        case 0: _t->materialSearch(); break;
        case 1: _t->closeWindow(); break;
        case 2: _t->clickedCreatProd(); break;
        case 3: _t->clickedUpdateProd(); break;
        case 4: _t->clickedSearchProd(); break;
        case 5: _t->clickedSearchColors(); break;
        case 6: _t->clickedSearchTrims(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLOPlugin::DesignSuite::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLOPlugin::DesignSuite::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLOPlugin__DesignSuite,
      qt_meta_data_CLOPlugin__DesignSuite, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLOPlugin::DesignSuite::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLOPlugin::DesignSuite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLOPlugin::DesignSuite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLOPlugin__DesignSuite))
        return static_cast<void*>(const_cast< DesignSuite*>(this));
    if (!strcmp(_clname, "Ui::DesignSuite"))
        return static_cast< Ui::DesignSuite*>(const_cast< DesignSuite*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLOPlugin::DesignSuite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
