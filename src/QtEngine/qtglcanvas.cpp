/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtglcanvas.h"
#include "qthelper.h"
#include <QOpenGLPaintDevice>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFramebufferObject>
#include <QPaintEvent>
#include <QWindow>
#include <iostream>

PROCESSING_BEGIN_NAMESPACE

class QtGLBuffer : public IQtBuffer
{
public:
    QtGLBuffer(int width, int height);
    ~QtGLBuffer();

    QPainter & getPainter() OVERRIDE;
    QImage & getImage() OVERRIDE;
    QRect rect() const OVERRIDE;

private:
    QRect drawRect;
    QWindow window;
    QOpenGLContext context;
    QOpenGLFramebufferObjectFormat fbo_format;
    QOpenGLFramebufferObject *fbo;
    QOpenGLPaintDevice *device;
    QPainter painter;
    QImage image;
    bool painting;
};

QtGLBuffer::QtGLBuffer(int width, int height)
    : painting(false)
{
    window.setSurfaceType(QWindow::OpenGLSurface);
    window.create();

    if (!context.create())
        qFatal("Cannot create the requested OpenGL context!");
    context.makeCurrent(&window);

    drawRect = QRect(0, 0, width, height);
    const QSize drawRectSize = drawRect.size();

    fbo_format.setSamples(16);
    fbo_format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

    fbo = new QOpenGLFramebufferObject(drawRectSize, fbo_format);

    device = new QOpenGLPaintDevice(drawRectSize);
}

QtGLBuffer::~QtGLBuffer()
{
    if (painting)
    {
        painter.end();
        fbo->release();
    }
    delete device;
    delete fbo;
}

QPainter & QtGLBuffer::getPainter()
{
    if (!painting)
    {
        fbo->bind();
        painter.begin(device);
        painting = true;
    }
    return painter;
}

QImage & QtGLBuffer::getImage()
{
    if (fbo->isBound())
    {
        painter.end();
        fbo->release();
        image = fbo->toImage();
        painting = false;
    }
    return image;
}

QRect QtGLBuffer::rect() const
{
    return drawRect;
}

/**
 * QtGLWidget class
 */
QtGLWidget::QtGLWidget(QtCanvas *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    // setAutoFillBackground(false);
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
    QRect dirtyRect = event->rect();
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QImage & image = helper->getBuffer()->getImage();
    painter.drawImage(dirtyRect, image, dirtyRect);
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
    delete buffer;
    buffer = 0;
    delete widget;
}

void QtGLCanvas::setFixedSize(int width, int height)
{
    widget->setFixedSize(width, height);
    buffer = new QtGLBuffer(width, height);
}

void QtGLCanvas::animate()
{
    Canvas::animate();
    widget->animate();
}

PROCESSING_END_NAMESPACE
