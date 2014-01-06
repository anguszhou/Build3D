#include "glwidget.h"

GLWidget::GLWidget(QGLWidget *parent) :
    QGLWidget(parent)
{
	ui.setupUi(this);

	fullscreen = false;
	int whichDriver;
	theQSplatGUI = new QSplatWin32GUI();
	theQSplatGUI->whichDriver =  OPENGL_POINTS ;
	makeCurrent();
	QMessageBox::warning(this, "Draw qs file",(char *)glGetString(GL_VENDOR) , QMessageBox::Yes);
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
	makeCurrent();
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

GLWidget::~GLWidget()
{

}
