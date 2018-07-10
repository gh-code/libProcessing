/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTGLCANVAS_H
#define P_QTGLCANVAS_H

#include "qtcommon.h"
#include "qtcanvas.h"

PROCESSING_BEGIN_NAMESPACE

class QtGLWidget : public QOPENGLWIDGET
{
    Q_OBJECT

public:
    explicit QtGLWidget(QtCanvas *helper, QWidget *parent=0);
    ~QtGLWidget();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) OVERRIDE;

private:
    friend class QtGLCanvas;

    QtCanvas *helper;
};

class QtGLCanvas : public QtCanvas
{
public:
    explicit QtGLCanvas(QWidget *parent=0);
    ~QtGLCanvas();

    void setFixedSize(int width, int height) OVERRIDE;
    void animate() OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) OVERRIDE;

private:
    QtGLWidget *widget;
};

PROCESSING_END_NAMESPACE

#endif // P_QTGLCANVAS_H
