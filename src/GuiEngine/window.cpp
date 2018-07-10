/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "window.h"
#include "canvas.h"

PROCESSING_BEGIN_NAMESPACE

Window::Window()
    : canvas(0)
{
}

Window::~Window()
{
    if (canvas && !canvas->hasOtherParent())
        delete canvas;
}

PROCESSING_END_NAMESPACE
