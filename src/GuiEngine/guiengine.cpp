/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "qtengine.h"
#include "guiengine.h"
#include <iostream>

PROCESSING_BEGIN_NAMESPACE

GuiEngine::GuiEngine()
    : window(0)
{
}

GuiEngine::~GuiEngine()
{
    // Qt window seems to be handled by QApplication.
    // If I delete it, the program will crash.
    if (window && !window->hasOtherParent())
        delete window;
}

Window * GuiEngine::createWindow()
{
    return window;
}

GuiEngine * GuiEngine::create(GuiEngineType type, int argc, char *argv[])
{
    // This is a dynamic factory for isolating the actual implementation.
    switch (type)
    {
        case GuiEngine::Qt:
            return new QtEngine(argc, argv);

        // Other GUI engine should be supported but I leave them to other people
        //case GuiEngine::GTK:
        //    return new GTKEngine(argc, argv);
    }
    return ((GuiEngine *) 0);
}

PROCESSING_END_NAMESPACE
