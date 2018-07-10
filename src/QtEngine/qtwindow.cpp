/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include <QHBoxLayout>

#include "qtwindow.h"
#include "qtcanvas.h"
#include "qtglcanvas.h"
#include "qtgl3dcanvas.h"
#include <iostream>

PROCESSING_BEGIN_NAMESPACE

extern int frameRate;

QtWindow::QtWindow()
    : Window(), QWidget(0), timer(0)
{
}

QtWindow::~QtWindow()
{
    if (timer)
        delete timer;
}

static QtCanvas *createQtCanvas(enum Renderer renderer, QWidget *parent=0)
{
    switch (renderer)
    {
        case P2D:
            return new QtGLCanvas(parent);

        case P3D:
            return new QtGL3DCanvas(parent);

        case PDF:
            throw "PDF is not support yet";
            break;

        case PDEFAULT:
        default:
            return new QtCanvas(parent);
    }
    return 0;
}

Canvas * QtWindow::replaceCanvas(enum Renderer renderer)
{
    QtCanvas *qtcanvas = createQtCanvas(renderer, this);
    QtCanvas *qtcanvas_last = (QtCanvas *) canvas;

    qtcanvas->setMouseTracking(true);
    qtcanvas->copyAllElementsFrom(*qtcanvas_last);

    layout->removeWidget(qtcanvas_last);
    layout->addWidget(qtcanvas);

    qtcanvas_last->setParent(0);
    delete qtcanvas_last;

    canvas = qtcanvas;
    return canvas;
}

Canvas * QtWindow::createCanvas(enum Renderer renderer)
{
    QtCanvas *qtcanvas = createQtCanvas(renderer, this);
    qtcanvas->setMouseTracking(true);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(qtcanvas);
    setLayout(layout);

    canvas = qtcanvas;
    return canvas;
}

void QtWindow::start(int fps)
{
    QtCanvas *qtcanvas = (QtCanvas *) canvas;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, qtcanvas, &QtCanvas::animate);
    timer->start(1000.0 / fps);
}

PROCESSING_END_NAMESPACE
