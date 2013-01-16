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
{
	GUI->windowHeight = this->height();
	GUI->windowWidth = this->width();
	theQSplatGUI->redraw();
}


void GLWidget::resizeGL(int width, int height)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{

}
void GLWidget::keyPressEvent(QKeyEvent *e)
{
	

    switch(e->key())
    {		
		case Qt::Key_Left:        
		case Qt::Key_Right: 
			{
				QPoint mousePos;
				static QSplatGUI::mousebutton this_button = QSplatGUI::NO_BUTTON;
				
				this_button = QSplatGUI::LIGHT_BUTTON;       
				updateGL();
				break;
			}

    }
}

