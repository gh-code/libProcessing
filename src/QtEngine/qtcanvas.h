/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTCANVAS_H
#define P_QTCANVAS_H

#include <QTimer>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include "macro.h"
#include "canvas.h"

PROCESSING_BEGIN_NAMESPACE

class QtCanvas : public Canvas, public QWidget
{
    //Q_OBJECT

public:
    explicit QtCanvas(QWidget *parent=0);
    virtual ~QtCanvas();

    virtual void setFixedSize(int width, int height);
    virtual bool hasParent() const OVERRIDE { return true; }
    virtual bool hasOtherParent() const OVERRIDE { return true; }
    virtual void animate();
    void paint(QPainter *painter, QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event) OVERRIDE;
    void mousePressEvent(QMouseEvent *event) OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) OVERRIDE;
    void mouseUpdateGlobal(QMouseEvent *event, bool pressed);
    void keyPressEvent(QKeyEvent *event) OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) OVERRIDE;
    void keyUpdateGlobal(QKeyEvent *event, bool pressed);

protected:
    QBrush brush;
    QPen pen;
    DrawMode ellipse_mode;
    DrawMode rect_mode;
};

PROCESSING_END_NAMESPACE

#endif // P_QTCANVAS_H
