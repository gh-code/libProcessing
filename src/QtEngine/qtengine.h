/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PQTENGINE_H
#define PQTENGINE_H

#include "guiengine.h"

class QApplication;

PROCESSING_BEGIN_NAMESPACE

class QtEngine : public GuiEngine
{
public:
    QtEngine(int argc, char *argv[]);
    ~QtEngine();

    int exec();
    void quit();

private:
    QApplication *app;
};

PROCESSING_END_NAMESPACE

#endif // PQTENGINE_H
