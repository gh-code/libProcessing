/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtengine.h"
#include "qtwindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>

PROCESSING_BEGIN_NAMESPACE

QtEngine::QtEngine(int argc, char *argv[])
    : GuiEngine()
{
    app = new QApplication(argc, argv);
    window = new QtWindow;
}

QtEngine::~QtEngine()
{
    //delete window;
    delete app;
}

int QtEngine::exec()
{
    return app->exec();
}

void QtEngine::quit()
{
    QApplication::quit();
}

PROCESSING_END_NAMESPACE
