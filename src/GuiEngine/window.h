/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PWINDOW_H
#define PWINDOW_H

#include "global.h"

PROCESSING_BEGIN_NAMESPACE

class Canvas;

class Window
{
public:
    virtual ~Window();

    virtual void setWindowTitle(const char *title) = 0;
    virtual void setFixedSize(int width, int height) = 0;
    virtual bool hasParent() const { return false; }
    virtual bool hasOtherParent() const { return false; }
    virtual void show() = 0;
    virtual void start(int fps) = 0;
    virtual Canvas * createCanvas(enum Renderer) = 0;
    virtual Canvas * replaceCanvas(enum Renderer) = 0;

    virtual void loop() = 0;
    virtual void noLoop() = 0;

protected:
    Window();
    Window & operator=(const Window &);

    Canvas *canvas;
};

PROCESSING_END_NAMESPACE

#endif // PWINDOW_H
