/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef GUIENGINE_H
#define GUIENGINE_H

#include "global.h"
#include "window.h"
#include "canvas.h"

PROCESSING_BEGIN_NAMESPACE

class GuiEngine
{
public:
    enum GuiEngineType
    {
        Qt
    };

public:
    virtual ~GuiEngine();
    virtual Window *createWindow();
    virtual int exec() = 0;
    virtual void quit() = 0;

    static GuiEngine *create(GuiEngineType type, int argc, char *argv[]);

protected:
    GuiEngine();

    Window *window;
};

PROCESSING_END_NAMESPACE

#endif // GUIENGINE_H
