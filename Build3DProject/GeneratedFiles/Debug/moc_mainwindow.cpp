/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Mar 12 14:51:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x0a,
      45,   11,   11,   11, 0x0a,
      57,   11,   11,   11, 0x0a,
      69,   11,   11,   11, 0x0a,
      84,   81,   11,   11, 0x0a,
      99,   11,   11,   11, 0x0a,
     123,   11,   11,   11, 0x0a,
     140,   11,   11,   11, 0x0a,
     151,   11,   11,   11, 0x0a,
     165,   11,   11,   11, 0x0a,
     178,   11,   11,   11, 0x0a,
     189,   11,   11,   11, 0x0a,
     208,   11,   11,   11, 0x0a,
     224,   11,   11,   11, 0x0a,
     245,   11,   11,   11, 0x0a,
     260,   11,   11,   11, 0x0a,
     272,   11,   11,   11, 0x0a,
     290,   11,   11,   11, 0x0a,
     301,   11,   11,   11, 0x0a,
     319,   11,   11,   11, 0x0a,
     338,   11,   11,   11, 0x0a,
     358,   11,   11,   11, 0x0a,
     371,   11,   11,   11, 0x0a,
     389,   11,   11,   11, 0x0a,
     400,   11,   11,   11, 0x0a,
     420,   11,   11,   11, 0x0a,
     433,   11,   11,   11, 0x0a,
     453,   11,   11,   11, 0x0a,
     466,   11,   11,   11, 0x0a,
     479,   11,   11,   11, 0x0a,
     491,   11,   11,   11, 0x0a,
     503,   11,   11,   11, 0x0a,
     527,  518,   11,   11, 0x0a,
     546,   11,   11,   11, 0x0a,
     567,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0action\0actionTriggered(QAction*)\0"
    "savemodel()\0loadmodel()\0showmodel()\0"
    "id\0setCorner(int)\0switchLayoutDirection()\0"
    "setDockOptions()\0cleanDir()\0buildQsFile()\0"
    "drawQsFile()\0setShiny()\0setBackface_cull()\0"
    "setShow_light()\0setShow_refinement()\0"
    "setAuto_spin()\0setPoints()\0setRound_points()\0"
    "setQuads()\0setPoly_circles()\0"
    "setPoly_Ellipses()\0setZBuffer_GLblit()\0"
    "setZBuffer()\0setTiles_GLblit()\0"
    "setTiles()\0setOptimal_GLblit()\0"
    "setOptimal()\0setSmail_ellipses()\0"
    "setSpheres()\0setPLYMode()\0setQSMode()\0"
    "openFiles()\0deleteThread()\0filename\0"
    "showError(QString)\0addThumbnail(QImage)\0"
    "buildModel()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->actionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->savemodel(); break;
        case 2: _t->loadmodel(); break;
        case 3: _t->showmodel(); break;
        case 4: _t->setCorner((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->switchLayoutDirection(); break;
        case 6: _t->setDockOptions(); break;
        case 7: _t->cleanDir(); break;
        case 8: _t->buildQsFile(); break;
        case 9: _t->drawQsFile(); break;
        case 10: _t->setShiny(); break;
        case 11: _t->setBackface_cull(); break;
        case 12: _t->setShow_light(); break;
        case 13: _t->setShow_refinement(); break;
        case 14: _t->setAuto_spin(); break;
        case 15: _t->setPoints(); break;
        case 16: _t->setRound_points(); break;
        case 17: _t->setQuads(); break;
        case 18: _t->setPoly_circles(); break;
        case 19: _t->setPoly_Ellipses(); break;
        case 20: _t->setZBuffer_GLblit(); break;
        case 21: _t->setZBuffer(); break;
        case 22: _t->setTiles_GLblit(); break;
        case 23: _t->setTiles(); break;
        case 24: _t->setOptimal_GLblit(); break;
        case 25: _t->setOptimal(); break;
        case 26: _t->setSmail_ellipses(); break;
        case 27: _t->setSpheres(); break;
        case 28: _t->setPLYMode(); break;
        case 29: _t->setQSMode(); break;
        case 30: _t->openFiles(); break;
        case 31: _t->deleteThread(); break;
        case 32: _t->showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->addThumbnail((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 34: _t->buildModel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
