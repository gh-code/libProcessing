/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTCANVAS_H
#define P_QTCANVAS_H

#include <QTimer>
#include <QWidget>
#include <QStack>
#include <QPair>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include "pglobal.h"
#include "canvas.h"

PROCESSING_BEGIN_NAMESPACE

class IQtBuffer
{
public:
    virtual ~IQtBuffer() {}
    virtual QPainter & getPainter() = 0;
    virtual QImage & getImage() = 0;
    virtual QRect rect() const = 0;
};

struct StyleData
{
    QBrush brush;
    QPen pen;
    DrawMode ellipse_mode;
    DrawMode rect_mode;
};

class QtCanvas : public Canvas, public QWidget
{
    //Q_OBJECT

public:
    explicit QtCanvas(QWidget *parent=0);
    virtual ~QtCanvas();

    virtual void pushStyle() OVERRIDE;
    virtual void popStyle() OVERRIDE;

    virtual void arc(float a, float b, float c, float d, float start, float stop, ArcMode mode = OPEN_PIE) OVERRIDE;
    virtual void ellipse(float a, float b, float c, float d) OVERRIDE;
    virtual void line(float x1, float y1, float x2, float y2) OVERRIDE;
    virtual void point(float x, float y) OVERRIDE;
    virtual void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) OVERRIDE;
    virtual void rect(float a, float b, float c, float d) OVERRIDE;
    virtual void rect(float a, float b, float c, float d, float r) OVERRIDE;
    virtual void rect(float a, float b, float c, float d, float tl, float tr, float br, float bl) OVERRIDE;
    virtual void triangle(float x1, float y1, float x2, float y2, float x3, float y3) OVERRIDE;

    virtual void background(int rgb) OVERRIDE;
    virtual void background(int v1, int v2, int v3, int alpha = 255) OVERRIDE;
    virtual void fill(int gray, int alpha = 255) OVERRIDE;
    virtual void fill(int v1, int v2, int v3, int alpha = 255) OVERRIDE;
    virtual void noFill() OVERRIDE;
    virtual void stroke(int gray, int alpha = 255) OVERRIDE;
    virtual void stroke(int v1, int v2, int v3, int alpha = 255) OVERRIDE;
    virtual void noStroke() OVERRIDE;

    virtual void ellipseMode(DrawMode mode) OVERRIDE;
    virtual void rectMode(DrawMode mode) OVERRIDE;
    virtual void strokeWeight(int weight) OVERRIDE;

    virtual void rotate(float angle) OVERRIDE;
    virtual void translate(float x, float y) OVERRIDE;

    virtual void setFixedSize(int width, int height);
    virtual bool hasParent() const OVERRIDE { return true; }
    virtual void animate();

    virtual IQtBuffer * getBuffer();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseUpdateGlobal(QMouseEvent *event, bool pressed);
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyUpdateGlobal(QKeyEvent *event, bool pressed);

protected:
    QStack<StyleData> style_stack;
    StyleData style;
    IQtBuffer *buffer;
};

PROCESSING_END_NAMESPACE

#endif // P_QTCANVAS_H
