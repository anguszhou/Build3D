/****************************************************************************
**
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QScrollArea>
#include <QSplitter>
#include <QGridLayout>
#include <QLabel>
#include <CString>
#include "GLWidget.h"
#include <QWidget>
#include "AdapterWidget.h"
#include "qsplat/qsplat_gui_win32.h"

#define GUI ((QSplatWin32GUI *) theQSplatGUI)

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSignalMapper)

class CBuildingData;
struct POINT4 
{
	float x;
	float y;
	float z;
	int  i;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *center;
    QList<ToolBar*> toolBars;
    QMenu *dockWidgetMenu;
    QMenu *mainWindowMenu;
    QSignalMapper *mapper;
    QList<QDockWidget*> extraDockWidgets;
	QStringList picList;
	QSplitter *splitterMain;
	GLWidget *qsplat_widget;
	

public:
    MainWindow(const QMap<QString, QSize> &customSizeHints,
                QWidget *parent = 0, Qt::WindowFlags flags = 0);
	QString fileName;
	

protected:
    void showEvent(QShowEvent *event);

public slots:
    void actionTriggered(QAction *action);
    void savemodel();
	void loadmodel();
	void showmodel();
    void setCorner(int id);
    void switchLayoutDirection();
    void setDockOptions();
	void cleanDir();

	//Qsplat part
	void buildQsFile();
	void drawQsFile();
	void setShiny();
	void setBackface_cull();
	void setShow_light();
	void setShow_refinement();
	void setAuto_spin();

	void setPoints();
	void setRound_points();
	void setQuads();
	void setPoly_circles();
	void setPoly_Ellipses();

	void setZBuffer_GLblit();
	void setZBuffer();
	void setTiles_GLblit();
	void setTiles();
	void setOptimal_GLblit();
	void setOptimal();

	void setSmail_ellipses();
	void setSpheres();

	//void hidePic();

	//open pictures
	void openFiles();
	void deleteThread();
	void showError(const QString filename);
	void addThumbnail(QImage);
	
	//build model
	void buildModel();
public:

public:
	ViewerQT*	_glWidget;
	CBuildingData *		m_pBuildingData;
	
private:
    //void cleanDir();

	void setupToolBar();
    void setupMenuBar();
    void setupDockWidgets(const QMap<QString, QSize> &customSizeHints);
	void callApp(std::string appPath , std::string paraPath);
	void cpfiles(std::string from , std::string to);
	void deleteDir(std::string dir);
	void modifyListTXT(std::string appPath ,std::string picDirPath ,std::string relativePath);
	void modifyPicName(std::string from , std::string to);
	bool isPicExsit(std::string path);
	void createThumbnail(const QString& filename);
	void showOSGAndhideOpengl();
	void showOpenglAndhideOSG();
	void dorefine();
	bool checkModel();

	QWidget* previewwidget;
	QWidget * main;
	QScrollArea * pScroll;
	QGridLayout* picGird;
	QLabel *label;
	//QLabel *label[5];
	int waitseconds;
	QString picDir;
	
	static int i ;
	static int j ;
	int k;	
};
#endif
