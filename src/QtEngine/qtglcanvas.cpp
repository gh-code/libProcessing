/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtglcanvas.h"
#include "qthelper.h"
#include <QPainter>

PROCESSING_BEGIN_NAMESPACE

/**
 * QtGLWidget class
 */
QtGLWidget::QtGLWidget(QtCanvas *helper, QWidget *parent)
    : QOPENGLWIDGET(parent), helper(helper)
{
    setAutoFillBackground(false);
}

QtGLWidget::~QtGLWidget()
{
}

void QtGLWidget::animate()
{
    update();
}

void QtGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event);
    painter.end();
}

/**
 * QtGLCanvas class
 */
QtGLCanvas::QtGLCanvas(QWidget *parent)
    : QtCanvas(parent), widget(new QtGLWidget(this, this))
{
}

QtGLCanvas::~QtGLCanvas()
{
    delete widget;
}

void QtGLCanvas::setFixedSize(int width, int height)
{
    widget->setFixedSize(width, height);
}

void QtGLCanvas::paintEvent(QPaintEvent *event)
{
    widget->paintEvent(event);
}

void QtGLCanvas::animate()
{
    Canvas::animate();
    widget->animate();
}

PROCESSING_END_NAMESPACE
