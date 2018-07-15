/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtcanvas.h"
#include "qtwindow.h"
#include "pelement.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <cmath>

PROCESSING_BEGIN_NAMESPACE

extern int frameCount;

extern bool isMousePressed;
extern int mouseX;
extern int mouseY;
extern int pmouseX;
extern int pmouseY;

extern bool iskeyPressed;
extern int keyCode;
extern char key;

class QtBuffer : public IQtBuffer
{
public:
    QtBuffer(int width, int height);
    virtual ~QtBuffer();
    virtual QPainter & getPainter();
    virtual QImage & getImage();
    virtual QRect rect() const;

protected:
    QPainter painter;
    QImage *image;
    bool painting;
};

QtBuffer::QtBuffer(int width, int height)
    : image(new QImage(width, height, QImage::Format_ARGB32_Premultiplied)),
      painting(false)
{
}

QtBuffer::~QtBuffer()
{
    if (painting)
        painter.end();
    delete image;
}

QPainter & QtBuffer::getPainter()
{
    if (!painting)
    {
        painter.begin(image);
        painter.setRenderHint(QPainter::Antialiasing);
        painting = true;
    }
    return painter;
}

QImage & QtBuffer::getImage()
{
    if (painting)
    {
        painter.end();
        painting = false;
    }
    return *image;
}

QRect QtBuffer::rect() const
{
    return image->rect();
}

static QRectF getRect(DrawMode mode, float a, float b, float c, float d)
{
    QRectF bbox;
    switch (mode)
    {
        case RADIUS:
        {
            float x = a - c;
            float y = b - d;
            bbox.setRect(x, y, 2 * c, 2 * d);
            break;
        }
        case CENTER:
        {
            float x = a - 0.5 * c;
            float y = b - 0.5 * d;
            bbox.setRect(x, y, c, d);
            break;
        }
        case CORNER:
        {
            bbox.setRect(a, b, c, d);
            break;
        }
        case CORNERS:
        {
            QPointF tl(a, b);
            QPointF br(c, d);
            bbox.setTopLeft(tl);
            bbox.setBottomRight(br);
            break;
        }
    }
    return bbox;
}

/**
 * QtCanvas class
 */
QtCanvas::QtCanvas(QWidget *parent)
    : Canvas(), QWidget(parent), buffer(0)
{
    style.ellipse_mode = CENTER;
    style.rect_mode = CORNER;
}

QtCanvas::~QtCanvas()
{
    if (buffer)
        delete buffer;
}

void QtCanvas::pushStyle()
{
    style_stack.push(style);
    buffer->getPainter().save();
}

void QtCanvas::popStyle()
{
    buffer->getPainter().restore();
    style = style_stack.pop();
}

void QtCanvas::arc(float a, float b, float c, float d, float start, float stop, ArcMode mode)
{
    float x = a - 0.5 * c;
    float y = b - 0.5 * d;
    start *= -2880.0 / M_PI;
    stop *= -2880.0 / M_PI - start;
    switch (mode)
    {
    case OPEN_PIE:
        buffer->getPainter().setPen(Qt::NoPen);
        buffer->getPainter().drawPie(x, y, c, d, start, stop);
        buffer->getPainter().setPen(style.pen);
        buffer->getPainter().drawArc(x, y, c, d, start, stop);
        break;

    case PIE:
        buffer->getPainter().drawPie(x, y, c, d, start, stop);
        break;

    case OPEN:
        buffer->getPainter().setPen(Qt::NoPen);
        buffer->getPainter().drawChord(x, y, c, d, start, stop);
        buffer->getPainter().setPen(style.pen);
        buffer->getPainter().drawArc(x, y, c, d, start, stop);
        break;

    case CHORD:
        buffer->getPainter().drawChord(x, y, c, d, start, stop);
        break;
    }
}

void QtCanvas::ellipse(float a, float b, float c, float d)
{
    switch (style.ellipse_mode)
    {
        case RADIUS:
        {
            QPointF center(a, b);
            buffer->getPainter().drawEllipse(center, c, d);
            break;
        }
        case CENTER:
        {
            QPointF center(a, b);
            buffer->getPainter().drawEllipse(center, 0.5 * c, 0.5 * d);
            break;
        }
        case CORNER:
        {
            buffer->getPainter().drawEllipse(a, b, c, d);
            break;
        }
        case CORNERS:
        {
            QPointF tl(a, b);
            QPointF br(c, d);
            QRectF bbox(tl, br);
            buffer->getPainter().drawEllipse(bbox);
            break;
        }
    }
}

void QtCanvas::line(float x1, float y1, float x2, float y2)
{
    buffer->getPainter().drawLine(x1, y1, x2, y2);
}

void QtCanvas::point(float x, float y)
{
    buffer->getPainter().drawPoint(x, y);
}

void QtCanvas::quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    QPolygon polygon;
    polygon << QPoint(x1, y1)
            << QPoint(x2, y2)
            << QPoint(x3, y3)
            << QPoint(x4, y4);
    buffer->getPainter().drawPolygon(polygon);
}

void QtCanvas::rect(float a, float b, float c, float d)
{
    QRectF bbox = getRect(style.rect_mode, a, b, c, d);
    buffer->getPainter().drawRect(bbox);
}

void QtCanvas::rect(float a, float b, float c, float d, float r)
{
    QRectF bbox = getRect(style.rect_mode, a, b, c, d);
    buffer->getPainter().drawRoundedRect(bbox, r, r);
}

void QtCanvas::rect(float a, float b, float c, float d, float tl, float tr, float br, float bl)
{
    QRectF bbox = getRect(style.rect_mode, a, b, c, d);
    QPainterPath path;
    float x = bbox.x();
    float y = bbox.y();
    float w = bbox.width();
    float h = bbox.height();
    float hw = 0.5 * w;
    float hh = 0.5 * h;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(x, y, hw, hh, tl, tl);
    path.addRoundedRect(x + hw, y, hw, hh, tr, tr);
    path.addRoundedRect(x + hw, y + hw, hw, hh, br, br);
    path.addRoundedRect(x, y + hw, hw, hh, bl, bl);
    path.addRect(x + hw - tl, y, tl, tl);
    path.addRect(x, y + hh - tl, tl, tl);
    path.addRect(x + hw - tl, y + hh - tl, tl, tl);
    path.addRect(x + hw, y, tr, tr);
    path.addRect(x + hw, y + hh - tr, tr, tr);
    path.addRect(x + w - tr, y + hh - tr, tr, tr);
    path.addRect(x + hw, y + hh, br, br);
    path.addRect(x + h - br, y + hh, br, br);
    path.addRect(x + hw, y + h - br, br, br);
    path.addRect(x, y + hh, bl, bl);
    path.addRect(x + hw - bl, y + hh, bl, bl);
    path.addRect(x + hw - bl, y + h - bl, bl, bl);
    buffer->getPainter().drawPath(path.simplified());
}

void QtCanvas::triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    QPolygon polygon;
    polygon << QPoint(x1, y1)
            << QPoint(x2, y2)
            << QPoint(x3, y3);
    buffer->getPainter().drawPolygon(polygon);
}

void QtCanvas::background(int rgb)
{
    background(rgb, rgb, rgb);
}

void QtCanvas::background(int v1, int v2, int v3, int alpha)
{
    QColor c = QColor::fromRgb(v1, v2, v3, alpha);
    QBrush background(c);
    buffer->getPainter().fillRect(buffer->rect(), background);
}

void QtCanvas::fill(int gray, int alpha)
{
    fill(gray, gray, gray, alpha);
}

void QtCanvas::fill(int v1, int v2, int v3, int alpha)
{
    QColor c = QColor::fromRgb(v1, v2, v3, alpha);
    style.brush = QBrush(c);
    buffer->getPainter().setBrush(style.brush);
}

void QtCanvas::noFill()
{
    buffer->getPainter().setBrush(Qt::NoBrush);
}

void QtCanvas::stroke(int gray, int alpha)
{
    stroke(gray, gray, gray, alpha);
}

void QtCanvas::stroke(int v1, int v2, int v3, int alpha)
{
    QColor c = QColor::fromRgb(v1, v2, v3, alpha);
    int width = style.pen.width();
    style.pen = QPen(c);
    style.pen.setWidth(width);
    style.pen.setCapStyle(Qt::RoundCap);
    buffer->getPainter().setPen(style.pen);
}

void QtCanvas::noStroke()
{
    buffer->getPainter().setPen(Qt::NoPen);
}

void QtCanvas::ellipseMode(DrawMode mode)
{
    style.ellipse_mode = mode;
}

void QtCanvas::rectMode(DrawMode mode)
{
    style.rect_mode = mode;
}

void QtCanvas::strokeWeight(int weight)
{
    style.pen.setWidth(weight);
    buffer->getPainter().setPen(style.pen);
}

void QtCanvas::rotate(float angle)
{
    buffer->getPainter().rotate(angle * 180.0 / M_PI);
}

void QtCanvas::translate(float x, float y)
{
    buffer->getPainter().translate(x, y);
}

void QtCanvas::animate()
{
    Canvas::animate();
    update();
}

IQtBuffer * QtCanvas::getBuffer()
{
    return buffer;
}

void QtCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    QRect dirtyRect = event->rect();
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(dirtyRect, buffer->getImage(), dirtyRect);
    painter.end();
}

void QtCanvas::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w, h);
    buffer = new QtBuffer(w, h);
}

void QtCanvas::mousePressEvent(QMouseEvent *event)
{
    mouseUpdateGlobal(event, true);
    mouseState = S_MOUSE_PRESSED;
    mouseStateNext = S_MOUSE_NONE;
}

void QtCanvas::mouseMoveEvent(QMouseEvent *event)
{
    mouseUpdateGlobal(event, true);
    mouseState = S_MOUSE_MOVED;
    mouseStateNext = S_MOUSE_MOVED;
}

void QtCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    mouseUpdateGlobal(event, false);
    mouseState = S_MOUSE_RELEASED;
    mouseStateNext = S_MOUSE_NONE;
}

void QtCanvas::mouseUpdateGlobal(QMouseEvent *event, bool pressed)
{
    isMousePressed = pressed;
    m_mouseX = event->x();
    m_mouseY = event->y();
}

void QtCanvas::keyPressEvent(QKeyEvent *event)
{
    if (callbacks["draw"])
    {
        keyUpdateGlobal(event, true);
        keyState = S_KEY_PRESSED;
        if (callbacks["keyPressed"])
            callbacks["keyPressed"]();
        // TODO: some transformation here
        if (callbacks["keyTyped"])
            callbacks["keyTyped"]();
    }
}

void QtCanvas::keyReleaseEvent(QKeyEvent *event)
{
    if (callbacks["draw"])
    {
        keyUpdateGlobal(event, false);
        keyState = S_KEY_RELEASED;
        if (callbacks["keyReleased"])
            callbacks["keyReleased"]();
    }
}

void QtCanvas::keyUpdateGlobal(QKeyEvent *event, bool pressed)
{
    iskeyPressed = pressed;
    keyCode = event->key();
    key = event->text().toStdString()[0];
}

PROCESSING_END_NAMESPACE
