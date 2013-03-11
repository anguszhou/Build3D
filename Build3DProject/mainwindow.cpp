/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
**
****************************************************************************/
#include "PreDefs.h"
#include "ConvertToVRML.h"
#include "mainwindow.h"
#include "colorswatch.h"
#include "toolbar.h"
#include "AdapterWidget.h"
#include "BuildingData.h"
#include "thumbnailthread.h"
#include "textio.h"
#include "ReaderWriterVRML2.h"
#include "qsplat/qsplat_make_main.h"
#include <QtGui>
#include <QLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDockWidget>
#include <tchar.h>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <io.h>
#include <sstream>
#include <osgUtil/Optimizer>
#include <QPixmapCache>
#include <QFile>
#include <stdlib.h>
#include <sys\stat.h>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/ReaderWriter>
#include <osgDB/WriteFile>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>

#include "vertexData.h"
using namespace std;

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

int MainWindow::i=0;
int MainWindow::j=0;

MainWindow::MainWindow(const QMap<QString, QSize> &customSizeHints,
                        QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("3D Building Reconstruction");
	
	_glWidget = new ViewerQT;
    _glWidget->setMinimumSize(400, 400);
	qsplat_widget = new GLWidget;
	qsplat_widget->setMinimumSize(400, 400);
	qsplat_widget->setMouseTracking(true);

	splitterMain = new QSplitter(Qt::Horizontal,0);

	pScroll = new QScrollArea(splitterMain);

	splitterMain->addWidget(pScroll);
	splitterMain->addWidget(_glWidget);	
	splitterMain->addWidget(qsplat_widget);

	showOSGAndhideOpengl();

	splitterMain->setStretchFactor(0,0);

	previewwidget = new QWidget(pScroll);
	pScroll->setWidget(previewwidget);
	pScroll->setWidgetResizable(false);

	previewwidget->setAutoFillBackground(true);
	previewwidget->setFixedSize(400,200);
	picGird = new QGridLayout(previewwidget);
	previewwidget->setLayout(picGird);
	//picGird->columnMinimumWidth(500);

	setCentralWidget(splitterMain);
    
    setupToolBar();
    setupMenuBar();

    //setupDockWidgets(customSizeHints);
    //statusBar()->showMessage(tr("Status Bar"));

	m_pBuildingData = new CBuildingData;
}

void MainWindow::actionTriggered(QAction *action)
{
    qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}

//setup Tool Bar include open pictures , model and build model
void MainWindow::setupToolBar()
{
	setIconSize(QSize(32, 32));
	// set open model button
	QToolBar* toolBar1 = addToolBar(tr("Tool Bar 1"));
	QAction* openAction = new QAction(QIcon("./res/open_model.png"), tr("&LoadModel"), this);
	connect(openAction, SIGNAL(triggered()), SLOT(loadmodel()));
			
	//set show model button
	QAction *showModel = new QAction(tr("&Show Model"), this);
	showModel->setStatusTip(tr("Show Model..."));
	showModel->setIcon(QIcon("./res/show_model.png"));
	connect(showModel , SIGNAL(triggered()) ,  this , SLOT (showmodel()));
	
	//set open pictures button
	QAction *openPics = new QAction(tr("&Pics"), this);
	openPics->setShortcut(QKeySequence::Open);
	openPics->setStatusTip(tr("Open Pictures..."));
	openPics->setIcon(QIcon("./res/open_picture.png"));
	connect(openPics , SIGNAL(triggered()) ,  this , SLOT (openFiles()));

	//set savemodel button
	QAction *savemodel = new QAction(tr("&Save Model"), this);
	savemodel->setIcon(QIcon("./res/save_model.png"));
	connect(savemodel , SIGNAL(triggered()) ,  this , SLOT (savemodel()));

	//set build model button
	QAction *buildModel = new QAction(tr("&Build") ,this);
	buildModel->setStatusTip(tr("Build Model..."));
	buildModel->setIcon(QIcon("./res/build.png"));
	connect(buildModel , SIGNAL(triggered()) ,  this , SLOT (buildModel()));

	//set config button
	QAction *config = new QAction(tr("&Config") ,this);
	config->setStatusTip(tr("config.."));
	config->setIcon(QIcon("./res/config.png"));

	//set search button
	QAction *search = new QAction(tr("&Search") ,this);
	search->setStatusTip(tr("Search.."));
	search->setIcon(QIcon("./res/search.png"));

	//set  help button
	QAction *help = new QAction(tr("&help") ,this);
	help->setStatusTip(tr("help.."));
	help->setIcon(QIcon("./res/help.png"));

	//set clean button
	QAction *cleanDir = new QAction(tr("&Clean Dir"), this);
	cleanDir->setIcon(QIcon("./res/clean_Dir.png"));
	connect(cleanDir , SIGNAL(triggered()) ,  this , SLOT (cleanDir()));

	//set hide button
	/*QAction *hidePic = new QAction(tr("&hide") ,this);
	hidePic->setStatusTip(tr("Hide Pic..."));
	hidePic->setIcon(QIcon("./res/clear_pic.png"));
	connect(hidePic , SIGNAL(triggered()) ,  this , SLOT (hide()));*/

	toolBar1->addAction(openPics);
	toolBar1->addAction(buildModel);
	toolBar1->addAction(openAction);
	toolBar1->addAction(showModel);
	toolBar1->addAction(savemodel);
	toolBar1->addAction(cleanDir);
	
	toolBar1->addAction(config);
	toolBar1->addAction(search);
	toolBar1->addAction(help);

}

void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("&File"));

	QAction *action = menu->addAction(tr("Load model"));
	connect(action, SIGNAL(triggered()), this, SLOT(loadmodel()));

    action = menu->addAction(tr("Save model"));
    connect(action, SIGNAL(triggered()), this, SLOT(savemodel()));

	menu->addSeparator();

	action = menu->addAction(tr("Build QsFile"));
	connect(action, SIGNAL(triggered()), this, SLOT(buildQsFile()));

	action = menu->addAction(tr("Draw QsFile"));
	connect(action, SIGNAL(triggered()), this, SLOT(drawQsFile()));

	menu->addSeparator();

    action = menu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));

    menu->addSeparator();
    menu->addAction(tr("&Quit"), this, SLOT(close()));

    mainWindowMenu = menuBar()->addMenu(tr("Main window"));

    action = mainWindowMenu->addAction(tr("Animated docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AnimatedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Allow nested docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowNestedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Allow tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowTabbedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Force tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & ForceTabbedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Vertical tabs"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & VerticalTabs);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

	//set qsplat options menu
	QMenu *Options = menuBar()->addMenu(tr("Options"));
	action = Options->addAction(tr("Shiny"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setShiny()));

	action = Options->addAction(tr("Backface Cull"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setBackface_cull()));

	action = Options->addAction(tr("Show Light"));
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setShow_light()));

	action = Options->addAction(tr("Show Refinement"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setShow_refinement()));

	action = Options->addAction(tr("Auto-spin"));
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setAuto_spin()));

	//set qsplat driver menu
	QMenu *driver = menuBar()->addMenu(tr("Driver"));
	QMenu *openGL = driver->addMenu(tr("OpenGL"));
	QActionGroup *driverGroup = new QActionGroup(this); 
	action = openGL->addAction(tr("Points"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	action->setChecked(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setPoints()));

	action = openGL->addAction(tr("Round Points"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setRound_points()));

	action = openGL->addAction(tr("Quads"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setQuads()));

	action = openGL->addAction(tr("Poly Circles"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setPoly_circles()));

	action = openGL->addAction(tr("Poly Ellipses"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setPoly_Ellipses()));

	//set qsplat software menu
	QMenu *software = driver->addMenu(tr("Software"));
	action = software->addAction(tr("Z-Buffer + GL Blit"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setZBuffer_GLblit()));

	action = software->addAction(tr("Z-Buffer"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setZBuffer()));

	action = software->addAction(tr("Tiles + GL Blit"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setTiles_GLblit()));

	action = software->addAction(tr("Tiles"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setTiles()));

	action = software->addAction(tr("Optimal + GL Blit"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setOptimal_GLblit()));

	action = software->addAction(tr("Optimal"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setOptimal()));

	//set qsplat visualizations
	QMenu *visualizations = driver->addMenu(tr("Visualizations"));
	QActionGroup *visuals = new QActionGroup(this); 
	action = visualizations->addAction(tr("Small Ellipses"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setSmail_ellipses()));

	action = visualizations->addAction(tr("Spheres"));
	driverGroup->addAction(action);
	action->setCheckable(true);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(setSpheres()));

    QMenu *toolBarMenu = menuBar()->addMenu(tr("Tool bars"));
    for (int i = 0; i < toolBars.count(); ++i)
        toolBarMenu->addMenu(toolBars.at(i)->menu);

    dockWidgetMenu = menuBar()->addMenu(tr("&Dock Widgets"));
}
// set Options slot method
void MainWindow::setShiny()
{
	GUI->menu_shiny = !GUI->menu_shiny;
	GUI->set_shiny(GUI->menu_shiny);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setBackface_cull()
{
	GUI->menu_backfacecull = !GUI->menu_backfacecull;
	GUI->set_backfacecull(GUI->menu_backfacecull);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setShow_light()
{
	GUI->menu_showlight = !GUI->menu_showlight;
	GUI->set_showlight(GUI->menu_showlight);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setShow_refinement()
{
	GUI->menu_showprogress = !GUI->menu_showprogress;
	GUI->set_showprogressbar(GUI->menu_showprogress);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
	
}
void MainWindow::setAuto_spin()
{
	GUI->menu_autospin = !GUI->menu_autospin;
	GUI->set_touristmode(!GUI->menu_autospin);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
// set Driver OpenGL slot method
void MainWindow::setPoints()
{
	GUI->whichDriver = (Driver)OPENGL_POINTS;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setRound_points()
{
	GUI->whichDriver = (Driver)OPENGL_POINTS_CIRC;
	GUI->resetviewer(true);
	if(checkModel()){		
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setQuads()
{
	GUI->whichDriver = (Driver)OPENGL_QUADS;
	GUI->resetviewer(true);
	if(checkModel()){		
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setPoly_circles()
{
	GUI->whichDriver = (Driver)OPENGL_POLYS_CIRC;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setPoly_Ellipses()
{
	GUI->whichDriver = (Driver)OPENGL_POLYS_ELLIP;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
// set Driver Software method
void MainWindow::setZBuffer_GLblit()
{
	GUI->whichDriver = (Driver)SOFTWARE_GLDRAWPIXELS;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setZBuffer()
{
	GUI->whichDriver = (Driver)SOFTWARE;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setTiles_GLblit()
{
	GUI->whichDriver = (Driver)SOFTWARE_TILES_GLDRAWPIXELS;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setTiles()
{
	GUI->whichDriver = (Driver)SOFTWARE_TILES;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setOptimal_GLblit()
{
	GUI->whichDriver = (Driver)SOFTWARE_BEST_GLDRAWPIXELS;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setOptimal()
{
	GUI->whichDriver = (Driver)SOFTWARE_BEST;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
// set Driver Visualizations method
void MainWindow::setSmail_ellipses()
{
	GUI->whichDriver = (Driver)OPENGL_POLYS_ELLIP_SMALL;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
void MainWindow::setSpheres()
{
	GUI->whichDriver = (Driver)OPENGL_SPHERES;
	GUI->resetviewer(true);
	if(checkModel()){
		qsplat_widget->updateGL();
		dorefine();
	}
}
//set MainWindow Dock
void MainWindow::setDockOptions()
{
    DockOptions opts;
    QList<QAction*> actions = mainWindowMenu->actions();

    if (actions.at(0)->isChecked())
        opts |= AnimatedDocks;
    if (actions.at(1)->isChecked())
        opts |= AllowNestedDocks;
    if (actions.at(2)->isChecked())
        opts |= AllowTabbedDocks;
    if (actions.at(3)->isChecked())
        opts |= ForceTabbedDocks;
    if (actions.at(4)->isChecked())
        opts |= VerticalTabs;

    QMainWindow::setDockOptions(opts);
}

void MainWindow::savemodel()
{
	
	QString savefileName = QFileDialog::getSaveFileName(this, tr("Save model"));
	QByteArray saveba = savefileName.toLatin1();
	std::string savefn(saveba.data());
	if (savefileName.isEmpty())
		return;
	
	//qDebug() << loadmodel(); 
	//QString loadfileName = loadmodel();
	//QByteArray loadba = loadfileName.toLatin1();
	//std::string loadfn(loadba.data());
	//std::cout << loadfn ;

	const char *ptr = ".ply";
	const char *p = strstr(savefn.c_str(),ptr);

	if(p)
	{
		//if(loadfileName != "")
			//QFile::copy(loadfileName,savefileName);
		//else
			QFile::copy("./model_data/models/option-0000.ply",savefileName);
	}
	else
	{		
			osgDB::writeNodeFile(*(_glWidget->getSceneData()),savefn,NULL);
	}			
}

QAction *addAction(QMenu *menu, const QString &text, QActionGroup *group, QSignalMapper *mapper,
                    int id)
{
    bool first = group->actions().isEmpty();
    QAction *result = menu->addAction(text);
    result->setCheckable(true);
    result->setChecked(first);
    group->addAction(result);
    QObject::connect(result, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(result, id);
    return result;
}

void MainWindow::setupDockWidgets(const QMap<QString, QSize> &customSizeHints)
{
    qRegisterMetaType<QDockWidget::DockWidgetFeatures>();

    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(setCorner(int)));

    QMenu *corner_menu = dockWidgetMenu->addMenu(tr("Top left corner"));
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Top dock area"), group, mapper, 0);
    ::addAction(corner_menu, tr("Left dock area"), group, mapper, 1);

    corner_menu = dockWidgetMenu->addMenu(tr("Top right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Top dock area"), group, mapper, 2);
    ::addAction(corner_menu, tr("Right dock area"), group, mapper, 3);

    corner_menu = dockWidgetMenu->addMenu(tr("Bottom left corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Bottom dock area"), group, mapper, 4);
    ::addAction(corner_menu, tr("Left dock area"), group, mapper, 5);

    corner_menu = dockWidgetMenu->addMenu(tr("Bottom right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Bottom dock area"), group, mapper, 6);
    ::addAction(corner_menu, tr("Right dock area"), group, mapper, 7);

    dockWidgetMenu->addSeparator();

    static const struct Set {
        const char * name;
        uint flags;
        Qt::DockWidgetArea area;
    } sets [] = {
#ifndef Q_WS_MAC
        { "Black", 0, Qt::LeftDockWidgetArea },
#else
        { "Black", Qt::Drawer, Qt::LeftDockWidgetArea },
#endif
       /* { "White", 0, Qt::RightDockWidgetArea },
       { "Red", 0, Qt::TopDockWidgetArea },
		{ "Green", 0, Qt::TopDockWidgetArea },
		{ "Yellow", 0, Qt::BottomDockWidgetArea },
        { "Blue", 0, Qt::BottomDockWidgetArea }*/
    };
    const int setCount = sizeof(sets) / sizeof(Set);

    for (int i = 0; i < setCount; ++i) 
	{
        //ColorSwatch *swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WindowFlags(sets[i].flags));
		ColorSwatch* swatch;
        if (qstrcmp(sets[i].name, "Blue") == 0) 
		{
			swatch = new TextIO(tr(sets[i].name), this, Qt::WindowFlags(sets[i].flags));
            BlueTitleBar *titlebar = new BlueTitleBar(swatch);
            swatch->setTitleBarWidget(titlebar);
            connect(swatch, SIGNAL(topLevelChanged(bool)), titlebar, SLOT(updateMask()));
            connect(swatch, SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)), titlebar, SLOT(updateMask()), Qt::QueuedConnection);

#ifdef Q_WS_QWS
            QPalette pal = palette();
            pal.setBrush(backgroundRole(), QColor(0,0,0,0));
            swatch->setPalette(pal);
#endif

        }
		else
			swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WindowFlags(sets[i].flags));

        QString name ;
		
        if (customSizeHints.contains(name))
            swatch->setCustomSizeHint(customSizeHints.value(name));
		//QSize size = new QSize(centralWidget()->width(), centralWidget()->height());	
		//swatch->setCustomSizeHint(& size);
			if(qstrcmp(sets[i].name, "Black") == 0)
			{
				pScroll = new QScrollArea(swatch);	
				swatch->setWidget(pScroll);
				
				previewwidget = new QWidget(pScroll);
				pScroll->setWidget(previewwidget);
				
				previewwidget->setAutoFillBackground(true);
				previewwidget->setFixedSize(200, 200);
				picGird = new QGridLayout(previewwidget);
				previewwidget->setLayout(picGird);
			}

        addDockWidget(sets[i].area, swatch);
        dockWidgetMenu->addMenu(swatch->menu);
    }
 
	//ColorSwatch* swatch = new ColorSwatch(tr(sets[0].name), this, Qt::WindowFlags(sets[0].flags));
	//QDockWidget *blackDockWidget = new QDockWidget(tr("PicturesViewer"));
	//blackDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); 
	//blackDockWidget->setFeatures();
    /*  QString name = QString::fromLatin1(sets[0].name);
       if (customSizeHints.contains(name))
            swatch->setCustomSizeHint(customSizeHints.value(name));*/	
	//	pScroll = new QScrollArea(blackDockWidget);	
	//	blackDockWidget->setWidget(pScroll);
	//	
	//	previewwidget = new QWidget(pScroll);
	//	pScroll->setWidget(previewwidget);

	//	previewwidget->setAutoFillBackground(true);
	//	picGird = new QGridLayout(previewwidget);
	//	previewwidget->setLayout(picGird);
    //  addDockWidget(sets[0].area, blackDockWidget);	
}

void MainWindow::setCorner(int id)
{
    switch (id) {
        case 0:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
            break;
        case 1:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 2:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
            break;
        case 3:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
            break;
        case 4:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
            break;
        case 5:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 6:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
            break;
        case 7:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
            break;
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}

void MainWindow::showOSGAndhideOpengl()
{
	_glWidget->show();
	qsplat_widget->hide();
}
void MainWindow::showOpenglAndhideOSG()
{
	_glWidget->hide();
	qsplat_widget->show();
}
//Build .qs file from .ply file
void MainWindow::buildQsFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Build .qs from .ply"),".",tr("PLY Files(*.ply)"));
	if (fileName.isEmpty())
		return;
	QByteArray ba = fileName.toLatin1();
	std::string fn(ba.data());
    char* param = "point";
	int result = build_ply_to_qs(param,fn.c_str());
    if(result)
    {
		QMessageBox::warning(this, tr("Build .qs information"), tr("Build .qs file from ")+fileName+tr(" successful!"), QMessageBox::Yes);
    }
    else
    {
	    QMessageBox::warning(this, tr("Build .qs information"),tr("Build .qs file from ")+fileName+tr(" failed!") , QMessageBox::Yes);
    }	
}

//draw .qs file
void MainWindow::drawQsFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Select .qs file to draw"),".",tr("QS Files(*.qs)"));
	if (fileName.isEmpty())
		return;
	QByteArray ba = fileName.toLatin1();
	std::string fn(ba.data());

	theQSplatGUI->SetModel(NULL);
	QSplat_Model *q = QSplat_Model::Open(fn.c_str());

	if (!q)
    {
		QMessageBox::warning(this, "Draw qs file","Can't open "+fileName+" !" , QMessageBox::Yes);
    }
    else
    {
		showOpenglAndhideOSG();
		theQSplatGUI->SetModel(q);
		GUI->resetviewer();
		qsplat_widget->updateGL();	
		dorefine();
    }
}

void MainWindow::dorefine()
{
	while(true){
		if(theQSplatGUI->theQSplat_Model->can_refine()){
			qsplat_widget->updateGL();
		}
		else{
			break;
		}
		theQSplatGUI->idle();
	}
}
// Load model from files
void MainWindow::loadmodel()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load model"));
	//QString fileName = "D:\\Build3DProject\\model_data\\models\\option-0000.ply";
	if (fileName.isEmpty())
		return;
	QByteArray ba = fileName.toLatin1();
	std::string fn(ba.data());

	_glWidget->ClearModelNode();

	std::fstream _file;		
	_file.open(fn.c_str() ,std::ios::in );
	if(_file.fail())
	{
		qDebug()<<"list is not exist";	
		return;
	};	

	std::string line ;
	int flag = 0;
	for( int i=0; i<30 ;i++ )
	{
		getline(_file, line,' ');
		if(line=="float32"||line=="float"||line=="uchar")	
			flag ++;
	}
	
	showOSGAndhideOpengl();
	if(flag == 9)
	{
		m_pBuildingData->load_3d_data(fn);
		// Set draw geometry
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		geom->setVertexArray(m_pBuildingData->m_3DBuildingVrts.get());
		geom->setColorArray(m_pBuildingData->m_3DBuildingClrs.get());	
		
		geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);		
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, m_pBuildingData->m_3DBuildingVrts->size()));
	
		osg::StateSet* sset = geom->getOrCreateStateSet();
		//sset->setMode(GL_LIGHTING, osg::StateAttribute::OFF );
		osg::Point* p = new osg::Point;
		p->setSize(4.0f);
		sset->setAttribute(p);
		
		geode->addDrawable(geom);

		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		osg::Matrix m;
		m.makeRotate(osg::PI/2.0, 1.f, 0.f, 0.f);
		mt->setMatrix(m);
		mt->addChild(geode.get());

		osgUtil::Optimizer optimizer;
		optimizer.optimize(mt.get());
		_glWidget->setSceneData(mt);	
		//_glWidget->addEventHandler(new osgGA::StateSetManipulator(_glWidget->getCamera()->getOrCreateStateSet()));
		//_glWidget->addEventHandler(new osgViewer::StatsHandler);
			
	}
	else
	{
		//read vertex directly
		osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(fn.c_str());
		osg::ref_ptr<osg::Group> root = new osg::Group();
		root->addChild(loadedModel.get());
		
		//optimize model 
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());

		_glWidget->setSceneData(root.get());
	}
		
	_file.clear();	

	_glWidget->addEventHandler(new osgGA::StateSetManipulator(_glWidget->getCamera()->getOrCreateStateSet()));
	_glWidget->addEventHandler(new osgViewer::StatsHandler);
	_glWidget->ResetCameraPara();
	_glWidget->update();
	//return fileName;
}

//show model
void MainWindow::showmodel()
{
	QString fileName = "./model_data/models/option-0000.ply";
	if (fileName.isEmpty())
		return;
	QByteArray ba = fileName.toLatin1();
	std::string fn(ba.data());

	_glWidget->ClearModelNode();

	std::fstream _file;		
	_file.open(fn.c_str() ,std::ios::in );
	if(_file.fail())
	{
		qDebug()<<"list is not exist";	
		return;
	};	

	std::string line ;
	int flag = 0;
	for( int i=0; i<30 ;i++ )
	{
		getline(_file, line,' ');
		if(line=="float32"||line=="float"||line=="uchar")	
			flag ++;
	}
	
	if(flag == 9)
	{

		m_pBuildingData->load_3d_data(fn);
		
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		geom->setVertexArray(m_pBuildingData->m_3DBuildingVrts.get());
		geom->setColorArray(m_pBuildingData->m_3DBuildingClrs.get());	
		
		geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);		
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, m_pBuildingData->m_3DBuildingVrts->size()));
	
		osg::StateSet* sset = geom->getOrCreateStateSet();
		//sset->setMode(GL_LIGHTING, osg::StateAttribute::OFF );
		osg::Point* p = new osg::Point;
		p->setSize(4.0f);
		sset->setAttribute(p);
		
		geode->addDrawable(geom);

		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		osg::Matrix m;
		m.makeRotate(osg::PI/2.0, 1.f, 0.f, 0.f);
		mt->setMatrix(m);
		mt->addChild(geode.get());

		osgUtil::Optimizer optimizer;
		optimizer.optimize(mt.get());
		_glWidget->setSceneData(mt);
	
		/*osgViewer::Viewer viewer ;
		osg::Node* node = osgDB::readNodeFile("123.osg") ;
		node ->asGroup() ->getChild(0) ->setNodeMask(0) ;
		viewer.setSceneData(node) ;
		osgDB::writeNodeFile(*(viewer.getSceneData()), "free.osg", osgDB::Registry::instance() ->getOptions());*/
	}	
	else
	{	
		osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(fn.c_str());
		osg::ref_ptr<osg::Group> root = new osg::Group();
		root->addChild(loadedModel.get());

		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());

		_glWidget->setSceneData(root.get());
	}
		
	_file.clear();	

	_glWidget->ResetCameraPara();
	_glWidget->update();
}

//open pictures 
void MainWindow::openFiles()
{
	i = 0;
	j = 0;
	//picList.clear();
	QPixmapCache::clear();
	qDebug()<<picGird->count();
	for(int k=0;k<picGird->count();k++)
		picGird->removeItem(picGird->itemAt(k));

	waitseconds = 1;//reset
	QStringList list ;
	//
	picDir=QFileDialog::getExistingDirectory(this, tr("Please choose a directory of pictures!"),QDir::currentPath(), 
																									QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
	if (!picDir.isEmpty() )
	{
		QDir *dir = new QDir(picDir);
		QStringList filter ;
		filter<<"*.jpg";
		dir->setNameFilters(filter);
		list=dir->entryList(filter);
		qDebug()<<picDir;		
	}

	picList = picList+list;
	if( list.count() == 0)
	{
		return;
	}

	//open files one by one, and create thread to create thumbnail for each file
	QStringList::Iterator it = list.begin();
	while(it != list.end()) 
	{					
 		//label->clear();
		QString tt = picDir+"\\"+*it;
		QByteArray tname = tt.toLatin1();
		std::string ttname(tname.data());    
		int lentt = tt.length(); 
		
		const char *ttnamechar = ttname.c_str();
		
		//char *ptr = ".JPG";
		QString jpg = ".JPG";
		int x = tt.indexOf(jpg);
		//const char *ptr1 = ".JPG";
		/*cout << "x" << x << endl;
		cout << "len = " << lentt;*/
					
		if(x!=0)
		{	
			//string newname =  ttname + ".jpg";
			//remove_chars(p,ptr);
			QString ttre = tt.replace(lentt-4,4,".jpg");
			//QFile::rename(tt,ttre);
			QByteArray qq = ttre.toLatin1();
			std::string ttrename = (qq.data());
			const char *ttrenamechar = ttrename.c_str(); 
			rename(ttnamechar,ttrenamechar);
			qDebug()<< "rename"<<ttre<<tt;				
		}
		
		createThumbnail(tt);
		qDebug()<<tt;
		++it;   		
 	}
	/*picDir=QFileDialog::getExistingDirectory(this, tr("Please choose a directory of pictures!"),QDir::currentPath(), 
																									QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
	if (!picDir.isEmpty() )
	{
		QDir *dir = new QDir(picDir);
		QStringList filter ;
		filter<<"*.jpg,*.JPG";
		dir->setNameFilters(filter);
		list=dir->entryList(filter);
		qDebug()<<picDir;		
	}

	picList = picList+list;
	if( list.count() == 0)
	{
		return;
	}	
	QStringList::Iterator it = list.begin();
	QString xname = picDir+"\\"+*it;
	QByteArray yname = xname.toLatin1();
	std::string pname(yname.data());              //转换Qstring至const Char*
	const char *pnamechar = pname.c_str();
	
	QByteArray picDirname = picDir.toLatin1();
	std::string picDname(picDirname.data());              //转换Qstring至const Char*
	const char *picDnamechar = picDname.c_str();
	
	//判断图片大小
	struct _stat info;  
	_stat(pnamechar, &info);  
	int size = info.st_size; 
	qDebug()<<size;
	qDebug()<<"pnamechar = " <<pnamechar;

	if(size >= 2000000)
	{
			while(it != list.end()) 
		{		

		QString xname = picDir+"\\"+*it;
		QByteArray yname = xname.toLatin1();
		std::string pname(yname.data());              //转换Qstring至const Char*
		const char *pnamechar = pname.c_str();
		IplImage *image=0,*imageresize=0;
		image=cvLoadImage(pnamechar,1);
		imageresize=cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3);
		cvResize(image,imageresize,CV_INTER_LINEAR);

		cvSaveImage(pnamechar,imageresize);
		cvReleaseImage(&image);
		cvReleaseImage(&imageresize);
		createThumbnail(xname);	
     	++it;
 		}
	}
	else
		while(it != list.end()) 
		{					
	 		
			QString tt = picDir+"\\"+*it;
			createThumbnail(tt);		
			qDebug()<<tt;
			
 			++it;
		}*/	
}

void MainWindow::createThumbnail(const QString& filename)
{
	//qDebug() << filename;
	QThread* thread = new ThumbnailThread(filename, waitseconds);
	waitseconds = waitseconds + 0.3;
	connect(thread, SIGNAL(thumbnailFinished(QImage)), this, SLOT(addThumbnail(QImage)));
	connect(thread, SIGNAL(thumbnailFailed(const QString)), this, SLOT(showError(const QString)));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteThread()));
	thread->start();
}

void MainWindow::deleteThread()
{
	QObject* obj = sender();
	ThumbnailThread * th = qobject_cast<ThumbnailThread*>(obj);
	//qDebug() << "delete thread..." << th->waitseconds();
	obj->deleteLater();
}

void MainWindow::addThumbnail(QImage smallpm)
{	
	static int i = 0;
	static int j = 0;
	const int lineSize = 7;
	//qWarning() << "thumbnail create successfully..." ;
	//qWarning() << "Small PM:" << smallpm << smallpm.size();
	
	/*for(k=0;k<5;k++)
	{		
		label[k] = new QLabel;
		//label[k]->clear();
		label[k]->setPixmap(QPixmap::fromImage(smallpm));
		picGird->addWidget(label[k], j, i);		
	}*/

	label = new QLabel;
	//label->clear();
	label->setPixmap(QPixmap::fromImage(smallpm));
	picGird->addWidget(label, j, i);
	
	//label->hide();
	//qWarning() << "Label:" <<label << label->isVisible();
	j++;
	if( j > previewwidget->height()/ smallpm.height() && j < lineSize)
	{
		previewwidget->setFixedHeight(  previewwidget->height() + 20 + smallpm.height());
	}
	else if (j >=lineSize)
	{
		j=0;
		i++;
		previewwidget->setFixedWidth(previewwidget->width()+10+smallpm.width());
	}	
	qDebug()<<"i="<<i;
	qDebug()<<"j="<<j;	
}


void MainWindow::showError(const QString filename)
{
	QMessageBox::information(this, "Error!", filename+" is not a valid picture file.");
}

void MainWindow::buildModel()
{
	//warning information
	if( picList.count() == 0)
	{
		QMessageBox::warning(this, "warning", "Please open some pictrues first!", QMessageBox::Yes);
		return;
	}
	
	//get application   path
	QTextCodec *code = QTextCodec::codecForName("gb18030"); 
	char szAppPath[MAX_PATH]; 
	GetModuleFileName(NULL, szAppPath, MAX_PATH);
	(strrchr(szAppPath, '\\'))[0] = 0; 
	(strrchr(szAppPath, '\\'))[1] = 0;
	std::string appPath(szAppPath);
	QString temp = QString ::fromLocal8Bit(appPath.c_str());
	temp.replace(QString("\\") , QString("/"));
	std::string path = code->fromUnicode(temp).data();  
	qDebug()<<path.c_str();

	//delete model_data directory 
	std::string modelPath = appPath+"model_data";
	if( !CreateDirectory(modelPath.c_str(), NULL) )
	{
		deleteDir(modelPath);
	}else
		qDebug()<<"modelPath !!";
			
	//delete all txt file
	std::string deleteTxt = "cd "+appPath+"&&del/f *.txt";
	system(deleteTxt.c_str());

	//get pictures path
	std::string picPath = code->fromUnicode(picDir).data();  
	qDebug()<<"picPath"<<picPath.c_str();
	//picDir.replace(QString("\\") , QString("/"));
	QString relativePath = picDir;
	relativePath.replace(QString("\\") , QString("/"));
	relativePath.remove(0 , temp.count());
	QString  runBundlePath = "./RunBundler.sh  \"" +relativePath + " \"";	 

	// call  bundler to build first model
	std::string paraCygwin = code->fromUnicode(runBundlePath).data();  
	std::string pathCygwin="c://cygwin//bin//mintty.exe";
	qDebug()<<paraCygwin.c_str();
	callApp(pathCygwin , paraCygwin);  

	// !!clear widget when open dir
	//modify list.txt path to absolute path(\) and modify pictures' name in visualize dir drop .rd 	
	modifyListTXT( appPath, picPath , code->fromUnicode(relativePath).data());

	//call Bundle2PMVS to produce camera parameters
	std::string pathB2P=appPath+"bin\\Bundle2PMVS.exe";
	std::string paraB2P = "\""+appPath+"list.txt \"  " +"\""+appPath+"bundle\\bundle.out \"  ";
	qDebug()<<"pathb2p"<<paraB2P.c_str();
	callApp(pathB2P , paraB2P);

	//call RadialUndistort to produce camera parameters
	std::string pathRadia=appPath+"bin\\RadialUndistort.exe";
	std::string paraRadia =  "\""+appPath+"list.txt \"  " +"\""+appPath+"bundle\\bundle.out \"  ";
	callApp(pathRadia , paraRadia);

	//build directory of pmvs2
	std::string dir = "md  "+appPath+ "model_data";
	std::string model ="md  "+appPath+ "model_data\\models ";
	std::string txt = "md  "+appPath+ "model_data\\txt";
	std::string visualize = "md  "+appPath+ "model_data\\visualize ";
	system(dir.c_str());
	system(model.c_str());
	system(txt.c_str());
	system(visualize.c_str());
		
	//std::string pics  = appPath+"example\\ET\\*.jpg\0";
	//std::string to = appPath+ "model_data\\visualize\0 ";
	//cpfiles(pics , to);

	//copy  pictures to directory above and modify their name from *.rd.jpg to *.jpg
	QStringList::Iterator it =picList.begin();
	int num = 0;
	while(it != picList.end()) 
	{						
		QString tt = picDir+"\\"+*it;
		QFileInfo fi (tt);	
		
		std::string  basename =  code->fromUnicode(fi.baseName()).data();
		std::string pcopy =  "copy  "+picPath+"\\"+basename+".rd.jpg   "+appPath+ "model_data\\visualize\\"; 
		std::string isExist = picPath+"\\"+basename+".rd.jpg";
		if(isPicExsit(isExist))
		{
			system(pcopy.c_str());
			//qDebug()<<pcopy.c_str();

			std::stringstream newstr ;	
			newstr<<num;
			std::string numstr = newstr.str();
			std::string oldname = appPath+ "model_data\\visualize\\"+basename+".rd.jpg";
			std::string newname ;
			if(num<10 && num >=0)
			{								
				newname = appPath+ "model_data\\visualize\\000"+numstr+".jpg";
				qDebug()<<newname.c_str();
			}
			else if(num>=10 && num <100)
				newname = appPath+ "model_data\\visualize\\00"+numstr+".jpg";
			else if(num>=100 && num<1000)
				newname = appPath+ "model_data\\visualize\\0"+numstr+".jpg";
			std::string deletename = "del  "+appPath+ "model_data\\visualize\\"+basename+".rd.jpg";
			//modifyPicName(oldname , newname);
			rename(oldname.c_str() , newname.c_str());
			system(deletename.c_str());				
			num++;
		}
		++it;
 	}

	//camera parameters txt to directory above
	std::string cameratxt = appPath+"\\*.txt\0";
	std::string txtto = appPath+"model_data\\txt\0";
	qDebug()<<"cameratxt"<<cameratxt.c_str();
	cpfiles(cameratxt , txtto);

	//copy  bundle.rd.out  to directory above
	std::string rdout = "copy  "+appPath+"bundle.rd.out  "+appPath+ "model_data\\";
	system(rdout.c_str());

	//call cmvs
	std::string pathCmvs = appPath+"Win32-VS2010\\cmvs.exe";
	std::string paraCmvs = appPath+"model_data\\";
	qDebug()<<"paraCMVS"<<paraCmvs.c_str();
	callApp(pathCmvs , paraCmvs);

	//call genOption
	std::string pathGen = appPath+"Win32-VS2010\\genOption.exe";
	std::string paraGen =appPath+"model_data\\";
	callApp(pathGen  , paraGen);

	//call pmvs2
	std::string pathPmvs2 = appPath+"Win32-VS2010\\pmvs2.exe";
	std::string paraPmvs2 = appPath+"model_data\\ option-0000";
	callApp(pathPmvs2 , paraPmvs2);

	//load model
	showmodel();
}

void MainWindow::cleanDir()
{
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	
	std::string picPath = code->fromUnicode(picDir).data();  
	
	std::string delPathgz = "del " + picPath + "\\*.key.gz";

	std::string delPathrd = "del " + picPath + "\\*.rd.jpg";
	 
	system(delPathrd.c_str());

	system(delPathgz.c_str());

	system("del .\\bundle\\*.out");

	system("del .\\bundle\\*.ply");	
}

void MainWindow::callApp(std::string appPath , std::string paraPath)
{
	SHELLEXECUTEINFO ShExecInfo  = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO); 
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS; 
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = _T("open"); 
	ShExecInfo.lpFile = _T(appPath.c_str()); 
	ShExecInfo.lpParameters =  _T(paraPath.c_str());
	ShExecInfo.lpDirectory = NULL; 
	ShExecInfo.nShow = SW_NORMAL; // SW_HIDE
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
	CloseHandle(ShExecInfo.hProcess);   
}

bool MainWindow::checkModel()
{
	if (!theQSplatGUI->theQSplat_Model) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return false;
	}
	return true;
}

void MainWindow::cpfiles(std::string from , std::string to)
{
		SHFILEOPSTRUCT   lpfile; 
		lpfile.hwnd   =NULL; 
		lpfile.wFunc=FO_COPY; 
		lpfile.fFlags=FOF_WANTNUKEWARNING;
		lpfile.pFrom=from.c_str(); 
		lpfile.pTo= to.c_str(); 
		lpfile.fAnyOperationsAborted=true; 
		SHFileOperation(&lpfile); 
}

void MainWindow::deleteDir(std::string dir)
{
	SHFILEOPSTRUCT FileOp={0}; 
	FileOp.fFlags = FOF_ALLOWUNDO |  
     FOF_NOCONFIRMATION; 
	FileOp.pFrom = dir.c_str(); 
	 FileOp.pTo = NULL;    
	 FileOp.wFunc = FO_DELETE;  
	 SHFileOperation(&FileOp) ; 
}

bool MainWindow::isPicExsit(std::string path)
{
	std::fstream _file;
	_file.open(path.c_str() ,std::ios::in);
	if(_file.fail())
	{
		return false;	
	};
	return true;
}

void MainWindow::modifyListTXT(std::string appPath ,std::string picDirPath ,std::string relativePath)
{
	std::fstream _file;
	std::string listPath = appPath+"list.txt";
	_file.open(listPath.c_str() ,std::ios::in |std::ios::out);
	if(_file.fail())
	{
		qDebug()<<"list is not exist";	
	};
	qDebug()<<"appPath"<<appPath.c_str()<<"picDirPath"<<picDirPath.c_str()<<"relativePath"<<relativePath.c_str();	
	std::string line , text;
    int p;
	std::string strKey =relativePath+"/";
    std::string strReplace =picDirPath+ "\\";

    while(getline(_file, line))
    {    
        while((p=line.find(strKey.c_str()))!=-1)
        {
            line.replace(p, strKey.length(), strReplace.c_str());
        }
        text+=line+"\n";
    }

    _file.clear();
    _file.sync();
    _file.seekp(0);
    _file<<text;
}

/*void MainWindow::deleterdgzfile()
{
	QByteArray picba = picDir.toLatin1();
	std::string picfn(picba.data());
	if (picDir.isEmpty())
		return;
	system("del picfn/*.rd.jpg");
	system("del picfn/*.gz");
}*/

void MainWindow::modifyPicName(std::string from , std::string to)
{
	SHFILEOPSTRUCT FileOp={0}; 
	FileOp.fFlags = FOF_WANTNUKEWARNING;  
	FileOp.pFrom = from.c_str(); 
	FileOp.pTo = to.c_str(); 
	FileOp.wFunc = FO_RENAME; 
	 SHFileOperation(&FileOp) ;
}
//解决无法从const char* 转为LPCWSTR问题
//1)将工程配置属性-》General-》Character Set为多字符集
//且保证C/C++-》Preprocessor-》Preprocessor Definitions中去掉UNICODE/_UNICODE。
//2)若在Unicode字符集下，在所有const char*的变量名前加上(WCHAR *)转换。

//不出现确认对话框 FOF_NOCONFIRMATION      
	//允许放回回收站FOF_ALLOWUNDO 
//需要时直接创建一个文件夹,不需用户确定 FOF_NOCONFIRMMKDIR ; 

//another call app code way
/*
	PROCESS_INFORMATION ProcessInfo; 
	STARTUPINFO StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field
	if(CreateProcess("C://cygwin//bin//mintty.exe", NULL, 
		 NULL,NULL,FALSE,0,NULL,
		 NULL,&StartupInfo,&ProcessInfo))
	{ 
		 WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
		 CloseHandle(ProcessInfo.hThread);
		 CloseHandle(ProcessInfo.hProcess);
	} 
	else
	{
		 MessageBox(NULL, "The process could not be started", "", MB_OK);
	}
*/