#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QtOpenGL>
#include <QtGui/QWidget>
#include "ui_glwidget.h"
#include "qsplat/qsplat_gui_win32.h"

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
    GLWidget(QGLWidget *parent = 0);
	~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	bool fullscreen;
	

private:
	Ui::GLWidgetClass ui;
};

#endif // GLWIDGET_H
