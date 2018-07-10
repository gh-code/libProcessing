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

/**
 * QtCanvas class
 */
QtCanvas::QtCanvas(QWidget *parent)
    : Canvas(), QWidget(parent)
{
}

QtCanvas::~QtCanvas()
{
}

void QtCanvas::animate()
{
    Canvas::animate();
    update();
}

void QtCanvas::paint(QPainter *painter, QPaintEvent *event)
{
    for (std::list<PElement *>::const_iterator it = draw_queue.cbegin();
            it != draw_queue.cend(); ++it)
    {
        PElement *e = (*it);
        switch (e->type())
        {
            case PElement::None:
                break;

            case PElement::PushStyle:
            {
                painter->save();
                break;
            }
            case PElement::PopStyle:
            {
                painter->restore();
                break;
            }
            case PElement::Ellipse:
            {
                PEllipse *el = (PEllipse *) e;
                QPointF center(el->a(), el->b());
                painter->drawEllipse(center, el->c(), el->d());
                break;
            }
            case PElement::Line:
            {
                PLine *l = (PLine *) e;
                painter->drawLine(l->x1(), l->y1(), l->x2(), l->y2());
                break;
            }
            case PElement::Point:
            {
                PPoint *p = (PPoint *) e;
                painter->drawPoint(p->x(), p->y());
                break;
            }
            case PElement::Quad:
            {
                PQuad *q = (PQuad *) e;
                QPolygon polygon;
                polygon << QPoint(q->x1(), q->y1())
                        << QPoint(q->x2(), q->y2())
                        << QPoint(q->x3(), q->y3())
                        << QPoint(q->x4(), q->y4());
                painter->drawPolygon(polygon);
                break;
            }
            case PElement::Rect:
            {
                PRect *r = (PRect *) e;
                painter->drawRect(r->a(), r->b(), r->c(), r->d());
                break;
            }
            case PElement::Triangle:
            {
                PTriangle *t = (PTriangle *) e;
                QPolygon polygon;
                polygon << QPoint(t->x1(), t->y1())
                        << QPoint(t->x2(), t->y2())
                        << QPoint(t->x3(), t->y3());
                painter->drawPolygon(polygon);
                break;
            }
            case PElement::Background:
            {
                PBackground *b = (PBackground *) e;
                QColor c = QColor::fromRgb(b->v1(), b->v2(), b->v3(), b->alpha());
                QBrush background(c);
                painter->fillRect(event->rect(), background);
                break;
            }
            case PElement::Fill:
            {
                PFill *f = (PFill *) e;
                QColor c = QColor::fromRgb(f->v1(), f->v2(), f->v3(), f->alpha());
                brush = QBrush(c);
                painter->setBrush(brush);
                break;
            }
            case PElement::NoFill:
            {
                painter->setBrush(Qt::NoBrush);
                break;
            }
            case PElement::Stroke:
            {
                PStroke *s = (PStroke *) e;
                QColor c = QColor::fromRgb(s->v1(), s->v2(), s->v3(), s->alpha());
                pen = QPen(c);
                painter->setPen(pen);
                break;
            }
            case PElement::NoStroke:
            {
                painter->setPen(Qt::NoPen);
                break;
            }
            case PElement::StrokeWeight:
            {
                PStrokeWeight *sw = (PStrokeWeight *) e;
                pen.setWidth(sw->weight());
                painter->setPen(pen);
                break;
            }
            case PElement::Rotate:
            {
                PRotate *r = (PRotate *) e;
                painter->rotate(r->angle() * 180.0 / M_PI);
                break;
            }
            case PElement::Translate:
            {
                PTranslate *t = (PTranslate *) e;
                painter->translate(t->x(), t->y());
                break;
            }
        }
    }
}

void QtCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}

void QtCanvas::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w, h);
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
