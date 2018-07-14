/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PCANVAS_H
#define PCANVAS_H

#include "pglobal.h"
#include <list>

PROCESSING_BEGIN_NAMESPACE

// Forward declaration
class PElement;

class Canvas
{
public:
    enum MouseState
    {
        S_MOUSE_NONE,
        S_MOUSE_PRESSED,
        S_MOUSE_MOVED,
        S_MOUSE_RELEASED
    };

    enum KeyState
    {
        S_KEY_NONE,
        S_KEY_PRESSED,
        S_KEY_RELEASED
    };

public:
    virtual ~Canvas();

    virtual void pushStyle();
    virtual void popStyle();
 
    virtual void arc(float a, float b, float c, float d, float start, float stop, ArcMode mode=OPEN_PIE);
    virtual void ellipse(float a, float b, float c, float d);
    virtual void line(float x1, float y1, float x2, float y2);
    virtual void point(float x, float y);
    virtual void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    virtual void rect(float a, float b, float c, float d);
    virtual void rect(float a, float b, float c, float d, float r);
    virtual void rect(float a, float b, float c, float d, float tl, float tr, float br, float bl);
    virtual void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
 
    virtual void background(int rgb);
    virtual void background(int v1, int v2, int v3, int alpha=255);
    virtual void fill(int gray, int alpha=255);
    virtual void fill(int v1, int v2, int v3, int alpha=255);
    virtual void noFill();
    virtual void stroke(int gray, int alpha=255);
    virtual void stroke(int v1, int v2, int v3, int alpha=255);
    virtual void noStroke();
 
    virtual void ellipseMode(DrawMode mode);
    virtual void rectMode(DrawMode mode);
    virtual void strokeWeight(int weight);
 
    virtual void rotate(float angle);
    virtual void translate(float x, float y);

    virtual void setFixedSize(int width, int height) = 0;
    virtual bool hasParent() const { return true; } // default is Window
    virtual void animate();
    void registerCallbacks(PFunctions &cbs) { callbacks = cbs; }

    const std::list<PElement *> & getDrawQueue() const { return draw_queue; }
    void setAllElementsPersistent();
    void copyAllElementsFrom(const Canvas &);
    void clearAllElements(bool force=false);

protected:
    Canvas();
    Canvas & operator=(const Canvas &);

    int m_mouseX;
    int m_mouseY;
    MouseState mouseState;
    MouseState mouseStateNext;
    KeyState keyState;
    std::list<PElement *> draw_queue;
    PFunctions callbacks;
};

PROCESSING_END_NAMESPACE

#endif // PCANVAS_H
