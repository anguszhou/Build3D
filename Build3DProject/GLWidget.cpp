#include "glwidget.h"

#include <QtCore>
#include <QtOpenGL>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define GL_PI 3.1415926
#define GL_RADIUX  0.2f
#define glGUI ((QSplatWin32GUI *) theQSplatGUI)

GLWidget::GLWidget(QGLWidget *parent) :
    QGLWidget(parent)
{
	
	fullscreen = false;
	int whichDriver;
	theQSplatGUI = new QSplatWin32GUI();
	theQSplatGUI->whichDriver =  OPENGL_POINTS ;
	float framerate = ((int)whichDriver >= (int)SOFTWARE_GLDRAWPIXELS) ? 4.0f : 8.0f;
	theQSplatGUI->set_desiredrate(framerate);
	std::string fn = "C:\\ply\\toy.qs";
	QSplat_Model *q = QSplat_Model::Open(fn.c_str());
	theQSplatGUI->SetModel(q);
}


void GLWidget::initializeGL()
{
	makeCurrent();
}

void GLWidget::paintGL()
{	/*
	qDebug()<<"options:";	
	qDebug()<<GUI->menu_shiny;	
	qDebug()<<GUI->menu_backfacecull;
	qDebug()<<GUI->menu_showlight;
	qDebug()<<GUI->menu_showprogress;
	qDebug()<<GUI->menu_autospin;

	qDebug()<<"Driver:";
	qDebug()<<GUI->whichDriver;
	*/
	GUI->windowHeight = this->height();
	GUI->windowWidth = this->width();
	theQSplatGUI->redraw();
}


void GLWidget::resizeGL(int width, int height)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
	static QSplatGUI::mousebutton this_button = QSplatGUI::NO_BUTTON;     
	
	//L/M/R button + Ctrl/Shift
	if(((e->buttons() & Qt::LeftButton)||(e->buttons() & Qt::MidButton)||(e->buttons() & Qt::RightButton)) && ((e->modifiers()==Qt::Key_Control) || (e->modifiers()==Qt::Key_Shift)))
	{	
		qDebug()<<"L/M/R button + Ctrl/Shift";
		this_button = QSplatGUI::LIGHT_BUTTON;
	}// L + R button
	else if((e->buttons() & Qt::LeftButton) && (e->buttons() & Qt::RightButton))
	{	
		this_button = QSplatGUI::TRANSZ_BUTTON;
	}//M + R button
	else if((e->buttons() & Qt::MidButton) && (e->buttons() & Qt::RightButton))
	{
		this_button = QSplatGUI::LIGHT_BUTTON;
	}//L button
	else if((e->buttons() & Qt::LeftButton))
	{	
		this_button = QSplatGUI::ROT_BUTTON;
	}//M button
	else if((e->buttons() & Qt::MidButton))
	{	
		this_button = QSplatGUI::TRANSZ_BUTTON;
	}//R button
	else if((e->buttons() & Qt::RightButton))
	{	
		this_button = QSplatGUI::TRANSXY_BUTTON;
	}//no button
	else
	{
		this_button = QSplatGUI::NO_BUTTON;
	}
	GUI->mouse(e->globalX() - GUI->windowPosX,
		(GUI->windowHeight - GUI->windowBorderY) - 
		(e->globalY() - GUI->windowPosY ),
		 this_button);
}
void GLWidget::wheelEvent(QWheelEvent * e)
{
	static QSplatGUI::mousebutton this_button = QSplatGUI::NO_BUTTON;
	this_button = e->delta() > 0 ? QSplatGUI::UP_WHEEL : QSplatGUI::DOWN_WHEEL;
	GUI->mouse(e->globalX() - GUI->windowPosX,
		(GUI->windowHeight - GUI->windowBorderY) - 
		(e->globalY() - GUI->windowPosY ),
		this_button);
}
void GLWidget::keyPressEvent(QKeyEvent *e)
{
}

