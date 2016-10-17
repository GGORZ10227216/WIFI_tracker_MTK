#include "gldrawer.h"

void GLDrawer::initializeGL() {
    // Set up the rendering context, load shaders and other resources, etc.:
    f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(r, g, b, 1.0f);

}

void GLDrawer::resizeGL(int w, int h) {
    // Update projection matrix and other size related settings:
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLDrawer::paintGL() {
    // Draw the scene:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // glDrawPixels( this->width(), this->height(), GL_RGBA, GL_UNSIGNED_BYTE, );
    f->glClear(GL_COLOR_BUFFER_BIT);
    if ( b > 0 )
        b = b - 0.1 ;
    else if ( r > 0 )
        r = r - 0.1 ;
    else if ( g > 0 )
        g = g - 0.1 ;
    else
        r = g = b = 1 ;
    f->glClearColor(r, g, b, 1.0f);
    qDebug() << "clear!" ;
}
