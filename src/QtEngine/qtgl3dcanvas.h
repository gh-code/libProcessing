/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTGL3DCANVAS_H
#define P_QTGL3DCANVAS_H

#include "qtcommon.h"
#include "qtcanvas.h"
#include <QOpenGLFunctions>

PROCESSING_BEGIN_NAMESPACE

class QtGL3DWidget : public QOPENGLWIDGET, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit QtGL3DWidget(QWidget *parent=0);
    virtual ~QtGL3DWidget();

    void background(int rgb);
    void background(int v1, int v2, int v3, int alpha=255);

public slots:
    void animate();

protected:
    void initializeGL() OVERRIDE;
    void paintGL() OVERRIDE;
    void resizeGL(int width, int height) OVERRIDE;

private:
    QColor color;
};

class QtGL3DCanvas : public QtCanvas
{
public:
    explicit QtGL3DCanvas(QWidget *parent=0);
    ~QtGL3DCanvas();

    void background(int rgb) OVERRIDE;
    void background(int v1, int v2, int v3, int alpha=255) OVERRIDE;

    void setFixedSize(int width, int height) OVERRIDE;
    void animate() OVERRIDE;

//protected:
//    void paintEvent(QPaintEvent *event) OVERRIDE;

private:
    QtGL3DWidget *widget;
};

PROCESSING_END_NAMESPACE

#endif // P_QTGL3DCANVAS_H
