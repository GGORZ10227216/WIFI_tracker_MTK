#include "gldrawer.h"

void GLDrawer::initializeGL() {
    // Set up the rendering context, load shaders and other resources, etc.:
    f = QOpenGLContext::currentContext()->functions();
    glClearColor(0, 0, 0, 1.0f);
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
    QPainter myPaint( this ) ;
    myPaint.drawImage( this->rect(), surface.rgbSwapped() );
}
