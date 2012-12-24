/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Dec 4 14:59:51 2012
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
      13,   14, // methods
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
     163,   11,   11,   11, 0x0a,
     187,  178,   11,   11, 0x0a,
     206,   11,   11,   11, 0x0a,
     227,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0action\0actionTriggered(QAction*)\0"
    "savemodel()\0loadmodel()\0showmodel()\0"
    "id\0setCorner(int)\0switchLayoutDirection()\0"
    "setDockOptions()\0cleanDir()\0openFiles()\0"
    "deleteThread()\0filename\0showError(QString)\0"
    "addThumbnail(QImage)\0buildModel()\0"
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
        case 8: _t->openFiles(); break;
        case 9: _t->deleteThread(); break;
        case 10: _t->showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->addThumbnail((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 12: _t->buildModel(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
