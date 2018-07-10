/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QT_DRAW_ELEMENT_H
#define P_QT_DRAW_ELEMENT_H

/**
 * I'm not sure about this. I think switch-case is enough currently.
 */
#include "draw_element.h"
#include "macro.h"

PROCESSING_BEGIN_NAMESPACE

class QtDrawBackground : public DrawBackground
{
public:
    void draw() const OVERRIDE;
};

class QtDrawPoint : public DrawPoint
{
public:
    void draw() const OVERRIDE;
};

class QtDrawLine : public DrawLine
{
public:
    void draw() const OVERRIDE;
};

PROCESSING_END_NAMESPACE

#endif // P_QT_DRAW_ELEMENT_H
