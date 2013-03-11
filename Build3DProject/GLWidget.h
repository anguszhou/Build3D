#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QWidget>
#include "qsplat/qsplat_gui_win32.h"


class GLWidget : public QGLWidget
{

public:
    GLWidget(QGLWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent * e);
	bool fullscreen;
	double CalFrameRate();
	
};

#endif // GLWIDGET_H
