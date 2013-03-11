#include "glwidget.h"

#include <QtCore>
#include <QtOpenGL>
#include <time.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define GL_PI 3.1415926
#define GL_RADIUX  0.2f
#define glGUI ((QSplatWin32GUI *) theQSplatGUI)

GLWidget::GLWidget(QGLWidget *parent) :
    QGLWidget(parent)
{
	makeCurrent();
	fullscreen = false;
	int whichDriver;
	theQSplatGUI = new QSplatWin32GUI();
	bool a = strncmp((char *)glGetString(GL_VENDOR), "Microsoft", 9);
	theQSplatGUI->whichDriver  = strncmp((char *)glGetString(GL_VENDOR), "Microsoft", 9) ? OPENGL_POINTS : SOFTWARE_BEST ;
	float framerate = ((int)whichDriver >= (int)SOFTWARE_GLDRAWPIXELS) ? 4.0f : 8.0f;
	theQSplatGUI->set_desiredrate(framerate);
}


void GLWidget::initializeGL()
{
	makeCurrent();	
}
/*
double GLWidget::CalFrameRate(){
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if(count <= 50){
		return save;
	}
	count = 0 ;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	qDebug()<<"current - last : "<<current - last<<" , CLK_TCK"<<CLK_TCK;	
	save = 50.0 / timegap;
	return save;
}
*/
double GLWidget::CalFrameRate(){
	static float framePerSecond = 0.0f;
	static float lastTime = 0.0f;

	float currentTime = GetTickCount()* 0.001f;
	++framePerSecond;

	if(currentTime - lastTime > 1.0f){
		lastTime = currentTime;
		qDebug()<<"frame rate is : "<<framePerSecond;	
		framePerSecond = 0 ;
	}
	
	return 0.0;
}
void GLWidget::paintGL()
{
	GUI->windowPosX=this->geometry().x();
	GUI->windowPosY=this->geometry().y();
	GUI->windowHeight = this->height();
	GUI->windowWidth = this->width();
	GUI->windowBorderY = 0;
	
	glReadBuffer(GL_BACK);
	theQSplatGUI->redraw();
	CalFrameRate();
	/*
	double frameRate = CalFrameRate();
	qDebug()<<"frame rate is : "<<frameRate;
	*/
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
	updateGL();
}
void GLWidget::wheelEvent(QWheelEvent * e)
{
	static QSplatGUI::mousebutton this_button = QSplatGUI::NO_BUTTON;
	this_button = e->delta() > 0 ? QSplatGUI::UP_WHEEL : QSplatGUI::DOWN_WHEEL;
	GUI->mouse(e->globalX() - GUI->windowPosX,
		(GUI->windowHeight - GUI->windowBorderY) - 
		(e->globalY() - GUI->windowPosY ),
		this_button);
	updateGL();
}
void GLWidget::keyPressEvent(QKeyEvent *e)
{
}

