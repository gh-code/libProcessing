/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "canvas.h"
#include "pelement.h"
#include <iostream>

PROCESSING_BEGIN_NAMESPACE

int frameCount;

bool isMousePressed;
int mouseX;
int mouseY;
int pmouseX;
int pmouseY;

bool iskeyPressed;
int keyCode;
char key;

Canvas::Canvas()
    : m_mouseX(0), m_mouseY(0),
      mouseState(S_MOUSE_NONE),
      mouseStateNext(S_MOUSE_NONE),
      keyState(S_KEY_NONE)
{
    frameCount = 0;
}

Canvas::~Canvas()
{
    clearAllElements(true);
}

void Canvas::setAllElementsPersistent()
{
    for (std::list<PElement *>::const_iterator it = draw_queue.cbegin();
            it != draw_queue.cend(); ++it)
    {
        PElement *e = (*it);
        e->setPersistent();
    }
}

void Canvas::copyAllElementsFrom(const Canvas &other)
{
    for (std::list<PElement *>::const_iterator it = other.draw_queue.cbegin();
            it != other.draw_queue.cend(); ++it)
        draw_queue.push_back((*it)->clone());
}

void Canvas::clearAllElements(bool force)
{
    if (force)
    {
        while (!draw_queue.empty())
        {
            PElement *e = draw_queue.front();
            draw_queue.pop_front();
            delete e;
        }
    }
    else
    {
        std::list<PElement *> temp_queue;
        while (!draw_queue.empty())
        {
            PElement *e = draw_queue.front();
            draw_queue.pop_front();
            if (e->isPersistent())
                temp_queue.push_back(e);
            else
                delete e;
        }
        while (!temp_queue.empty())
        {
            PElement *e = temp_queue.front();
            temp_queue.pop_front();
            draw_queue.push_back(e);
        }
    }
}

void Canvas::animate()
{
    // Clear the queue
    clearAllElements();

    // Create mouse event for the client
    pmouseX = mouseX;
    pmouseY = mouseY;
    mouseX = m_mouseX;
    mouseY = m_mouseY;
    if (callbacks["mousePressed"] && (mouseState == S_MOUSE_PRESSED))
        callbacks["mousePressed"]();
    if (callbacks["mouseMoved"] && (mouseState == S_MOUSE_MOVED))
        callbacks["mouseMoved"]();
    if (callbacks["mouseReleased"] && (mouseState == S_MOUSE_RELEASED))
        callbacks["mouseReleased"]();
    mouseState = mouseStateNext;

    // The client creates draw elements and add to the queue
    if (callbacks["draw"])
        callbacks["draw"]();

    keyState = S_KEY_NONE;
    frameCount++;
}

void Canvas::pushStyle()
{
    draw_queue.push_back(new PPushStyle);
}

void Canvas::popStyle()
{
    draw_queue.push_back(new PPopStyle);
}

void Canvas::arc(float a, float b, float c, float d, float start, float stop, ArcMode mode)
{
    draw_queue.push_back(new PArc(a, b, c, d, start, stop, mode));
}

void Canvas::ellipse(float a, float b, float c, float d)
{
    draw_queue.push_back(new PEllipse(a, b, c, d));
}

void Canvas::line(float x1, float y1, float x2, float y2)
{
    draw_queue.push_back(new PLine(x1, y1, x2, y2));
}

void Canvas::point(float x, float y)
{
    draw_queue.push_back(new PPoint(x, y));
}

void Canvas::quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    draw_queue.push_back(new PQuad(x1, y1, x2, y2, x3, y3, x4, y4));
}

void Canvas::rect(float a, float b, float c, float d)
{
    draw_queue.push_back(new PRect(a, b, c, d));
}

void Canvas::rect(float a, float b, float c, float d, float r)
{
    draw_queue.push_back(new PRoundedRect(a, b, c, d, r));
}

void Canvas::rect(float a, float b, float c, float d, float tl, float tr, float br, float bl)
{
    draw_queue.push_back(new PRoundedRectC4(a, b, c, d, tl, tr, br, bl));
}

void Canvas::triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    draw_queue.push_back(new PTriangle(x1, y1, x2, y2, x3, y3));
}

void Canvas::background(int rgb)
{
    background(rgb, rgb, rgb);
}

void Canvas::background(int v1, int v2, int v3, int alpha)
{
    draw_queue.push_back(new PBackground(v1, v2, v3, alpha));
}

void Canvas::fill(int gray, int alpha)
{
    fill(gray, gray, gray, alpha);
}

void Canvas::fill(int v1, int v2, int v3, int alpha)
{
    draw_queue.push_back(new PFill(v1, v2, v3, alpha));
}

void Canvas::noFill()
{
    draw_queue.push_back(new PNoFill);
}

void Canvas::stroke(int gray, int alpha)
{
    stroke(gray, gray, gray, alpha);
}

void Canvas::stroke(int v1, int v2, int v3, int alpha)
{
    draw_queue.push_back(new PStroke(v1, v2, v3, alpha));
}

void Canvas::noStroke()
{
    draw_queue.push_back(new PNoStroke);
}

void Canvas::ellipseMode(DrawMode mode)
{
    draw_queue.push_back(new PEllipseMode(mode));
}

void Canvas::rectMode(DrawMode mode)
{
    draw_queue.push_back(new PRectMode(mode));
}

void Canvas::strokeWeight(int weight)
{
    draw_queue.push_back(new PStrokeWeight(weight));
}

void Canvas::rotate(float angle)
{
    draw_queue.push_back(new PRotate(angle));
}

void Canvas::translate(float x, float y)
{
    draw_queue.push_back(new PTranslate(x, y));
}

PROCESSING_END_NAMESPACE
