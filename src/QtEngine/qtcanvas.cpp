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
    style.ellipse_mode = CENTER;
    style.rect_mode = CORNER;
}

QtCanvas::~QtCanvas()
{
}

void QtCanvas::animate()
{
    Canvas::animate();
    update();
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
                style_stack.push(style);
                painter->save();
                break;
            }
            case PElement::PopStyle:
            {
                painter->restore();
                style = style_stack.pop();
                break;
            }
            case PElement::Arc:
            {
                PArc *a = (PArc *) e;
                float x = a->a() - 0.5 * a->c();
                float y = a->b() - 0.5 * a->d();
                float start = a->start() * -2880.0 / M_PI;
                float stop = a->stop() * -2880.0 / M_PI - start;
                switch (a->mode())
                {
                    case OPEN_PIE:
                        painter->setPen(Qt::NoPen);
                        painter->drawPie(x, y, a->c(), a->d(), start, stop);
                        painter->setPen(style.pen);
                        painter->drawArc(x, y, a->c(), a->d(), start, stop);
                        break;

                    case PIE:
                        painter->drawPie(x, y, a->c(), a->d(), start, stop);
                        break;

                    case OPEN:
                        painter->setPen(Qt::NoPen);
                        painter->drawChord(x, y, a->c(), a->d(), start, stop);
                        painter->setPen(style.pen);
                        painter->drawArc(x, y, a->c(), a->d(), start, stop);
                        break;

                    case CHORD:
                        painter->drawChord(x, y, a->c(), a->d(), start, stop);
                        break;
                }
                break;
            }
            case PElement::Ellipse:
            {
                PEllipse *el = (PEllipse *) e;
                switch (style.ellipse_mode)
                {
                    case RADIUS:
                    {
                        QPointF center(el->a(), el->b());
                        painter->drawEllipse(center, el->c(), el->d());
                        break;
                    }
                    case CENTER:
                    {
                        QPointF center(el->a(), el->b());
                        painter->drawEllipse(center, 0.5 * el->c(), 0.5 * el->d());
                        break;
                    }
                    case CORNER:
                    {
                        painter->drawEllipse(el->a(), el->b(), el->c(), el->d());
                        break;
                    }
                    case CORNERS:
                    {
                        QPointF tl(el->a(), el->b());
                        QPointF br(el->c(), el->d());
                        QRectF bbox(tl, br);
                        painter->drawEllipse(bbox);
                        break;
                    }
                }
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
                QRectF bbox = getRect(style.rect_mode, r->a(), r->b(), r->c(), r->d());
                painter->drawRect(bbox);
                break;
            }
            case PElement::RoundedRect:
            {
                PRoundedRect *r = (PRoundedRect *)e;
                QRectF bbox = getRect(style.rect_mode, r->a(), r->b(), r->c(), r->d());
                painter->drawRoundedRect(bbox, r->r(), r->r());
                break;
            }
            case PElement::RoundedRectC4:
            {
                PRoundedRectC4 *r = (PRoundedRectC4 *)e;
                QRectF bbox = getRect(style.rect_mode, r->a(), r->b(), r->c(), r->d());
                QPainterPath path;
                float x = bbox.x();
                float y = bbox.y();
                float w = bbox.width();
                float h = bbox.height();
                float hw = 0.5 * w;
                float hh = 0.5 * h;
                path.setFillRule(Qt::WindingFill);
                path.addRoundedRect(x,      y     , hw, hh, r->tl(), r->tl());
                path.addRoundedRect(x + hw, y     , hw, hh, r->tr(), r->tr());
                path.addRoundedRect(x + hw, y + hw, hw, hh, r->br(), r->br());
                path.addRoundedRect(x,      y + hw, hw, hh, r->bl(), r->bl());
                path.addRect(x + hw - r->tl(), y, r->tl(), r->tl());
                path.addRect(x, y + hh - r->tl(), r->tl(), r->tl());
                path.addRect(x + hw - r->tl(), y + hh - r->tl(), r->tl(), r->tl());
                path.addRect(x + hw, y, r->tr(), r->tr());
                path.addRect(x + hw, y + hh - r->tr(), r->tr(), r->tr());
                path.addRect(x + w - r->tr(), y + hh - r->tr(), r->tr(), r->tr());
                path.addRect(x + hw, y + hh, r->br(), r->br());
                path.addRect(x + h - r->br(), y + hh, r->br(), r->br());
                path.addRect(x + hw, y + h - r->br(), r->br(), r->br());
                path.addRect(x, y + hh, r->bl(), r->bl());
                path.addRect(x + hw - r->bl(), y + hh, r->bl(), r->bl());
                path.addRect(x + hw - r->bl(), y + h - r->bl(), r->bl(), r->bl());
                painter->drawPath(path.simplified());
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
                style.brush = QBrush(c);
                painter->setBrush(style.brush);
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
                int width = style.pen.width();
                style.pen = QPen(c);
                style.pen.setWidth(width);
                style.pen.setCapStyle(Qt::RoundCap);
                painter->setPen(style.pen);
                break;
            }
            case PElement::NoStroke:
            {
                painter->setPen(Qt::NoPen);
                break;
            }
            case PElement::EllipseMode:
            {
                PEllipseMode *em = (PEllipseMode *) e;
                style.ellipse_mode = em->mode();
                break;
            }
            case PElement::RectMode:
            {
                PRectMode *rm = (PRectMode *) e;
                style.rect_mode = rm->mode();
                break;
            }
            case PElement::StrokeWeight:
            {
                PStrokeWeight *sw = (PStrokeWeight *) e;
                style.pen.setWidth(sw->weight());
                painter->setPen(style.pen);
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
