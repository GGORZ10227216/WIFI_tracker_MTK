#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <qopengl.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <math.h>
#include <QDebug>

class GLDrawer : public QOpenGLWidget
{
public:
    GLDrawer(QWidget *parent) : QOpenGLWidget(parent) { }
private:
    QOpenGLFunctions *f = NULL ;
    float r = 1.0, g = 1.0, b= 1.0 ;
protected:
    void initializeGL() ;
    void resizeGL(int w, int h) ;
    void paintGL() ;
};

#endif // GLDRAWER_H
