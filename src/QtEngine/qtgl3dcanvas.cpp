/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtgl3dcanvas.h"
#include "qthelper.h"
#include <iostream>

/**
 * Not supported yet
 */

PROCESSING_BEGIN_NAMESPACE

/**
 * QtGL3DWidget class
 */
QtGL3DWidget::QtGL3DWidget(QWidget *parent)
    : QOPENGLWIDGET(parent)
{
}

QtGL3DWidget::~QtGL3DWidget()
{
    makeCurrent();
    doneCurrent();
}

void QtGL3DWidget::background(int rgb)
{
    background(rgb, rgb, rgb, 255);
}

void QtGL3DWidget::background(int v1, int v2, int v3, int alpha)
{
    color = QColor(v1, v2, v3, alpha);
    // if HSV mode
    // color = QColor::fromHsv(v1, v2, v3, alpha);
    update();
}

void QtGL3DWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
 
    glClearColor(0.0 ,0.0 ,0.0, 1.0);
}

void QtGL3DWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void QtGL3DWidget::paintGL()
{
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void QtGL3DWidget::animate()
{
    update();
}

/**
 * QtGL3DCanvas class
 */
QtGL3DCanvas::QtGL3DCanvas(QWidget *parent)
    : QtCanvas(parent), widget(new QtGL3DWidget(this))
{
}

QtGL3DCanvas::~QtGL3DCanvas()
{
    delete widget;
}

void QtGL3DCanvas::background(int rgb)
{
    widget->background(rgb);
}

void QtGL3DCanvas::background(int v1, int v2, int v3, int alpha)
{
    widget->background(v1, v2, v3, alpha);
}

void QtGL3DCanvas::setFixedSize(int width, int height)
{
    widget->setFixedSize(width, height);
}

void QtGL3DCanvas::animate()
{
    widget->animate();
}

PROCESSING_END_NAMESPACE
