/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_PELEMENT_H
#define P_PELEMENT_H

#include "global.h"

PROCESSING_BEGIN_NAMESPACE

class PElement
{
public:
    enum PElementType
    {
        None,
        PushStyle,
        PopStyle,
        Arc,
        Ellipse,
        Line,
        Point,
        Quad,
        Rect,
        Triangle,
        Background,
        Fill,
        NoFill,
        Stroke,
        NoStroke,
        EllipseMode,
        RectMode,
        StrokeWeight,
        Rotate,
        Translate
    };

public:
    PElement() : persistent(false) {}
    virtual ~PElement() {}

    virtual PElementType type() const { return PElement::None; }
    virtual void draw() const {}
    virtual PElement * clone() const { return new PElement; }
    void setPersistent() { persistent = true; }
    bool isPersistent() const { return persistent; }

private:
    bool persistent;
};

class PPushStyle : public PElement
{
public:
    PPushStyle() {}
    PElement::PElementType type() const { return PElement::PushStyle; }
    PElement * clone() const { return new PPushStyle; }
};

class PPopStyle : public PElement
{
public:
    PPopStyle() {}
    PElement::PElementType type() const { return PElement::PopStyle; }
    PElement * clone() const { return new PPopStyle; }
};

class PArc : public PElement
{
public:
    PArc(float a, float b, float c, float d, float start, float stop, ArcMode mode=OPEN_PIE)
        : m_a(a), m_b(b), m_c(c), m_d(d), m_start(start), m_stop(stop), m_mode(mode) {}

    PElement::PElementType type() const { return PElement::Arc; }
    PElement * clone() const { return new PArc(m_a, m_b, m_c, m_d, m_start, m_stop, m_mode); }
    float a() const { return m_a; }
    float b() const { return m_b; }
    float c() const { return m_c; }
    float d() const { return m_d; }
    float start() const { return m_start; }
    float stop() const { return m_stop; }
    ArcMode mode() const { return m_mode; }

private:
    float m_a, m_b, m_c, m_d, m_start, m_stop;
    ArcMode m_mode;
};

class PEllipse : public PElement
{
public:
    PEllipse(float a, float b, float c, float d)
        : m_a(a), m_b(b), m_c(c), m_d(d) {}

    PElement::PElementType type() const { return PElement::Ellipse; }
    PElement * clone() const { return new PEllipse(m_a, m_b, m_c, m_d); }
    float a() const { return m_a; }
    float b() const { return m_b; }
    float c() const { return m_c; }
    float d() const { return m_d; }

private:
    float m_a, m_b, m_c, m_d;
};

class PLine : public PElement
{
public:
    PLine(float x1, float y1, float x2, float y2)
        : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

    PElement::PElementType type() const { return PElement::Line; }
    PElement * clone() const { return new PLine(m_x1, m_y1, m_x2, m_y2); }
    float x1() const { return m_x1; }
    float y1() const { return m_y1; }
    float x2() const { return m_x2; }
    float y2() const { return m_y2; }

private:
    float m_x1, m_y1, m_x2, m_y2;
};

class PPoint : public PElement
{
public:
    PPoint(float x, float y)
        : m_x(x), m_y(y) {}

    PElement::PElementType type() const { return PElement::Point; }
    PElement * clone() const { return new PPoint(m_x, m_y); }
    float x() const { return m_x; }
    float y() const { return m_y; }

private:
    float m_x, m_y;
};

class PQuad : public PElement
{
public:
    PQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
        : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3), m_x4(x4), m_y4(y4) {}

    PElement::PElementType type() const { return PElement::Quad; }
    PElement * clone() const { return new PQuad(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4); }
    float x1() const { return m_x1; }
    float y1() const { return m_y1; }
    float x2() const { return m_x2; }
    float y2() const { return m_y2; }
    float x3() const { return m_x3; }
    float y3() const { return m_y3; }
    float x4() const { return m_x4; }
    float y4() const { return m_y4; }

private:
    float m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4;
};

class PRect : public PElement
{
public:
    PRect(float a, float b, float c, float d)
        : m_a(a), m_b(b), m_c(c), m_d(d) {}

    PElement::PElementType type() const { return PElement::Rect; }
    PElement * clone() const { return new PRect(m_a, m_b, m_c, m_d); }
    float a() const { return m_a; }
    float b() const { return m_b; }
    float c() const { return m_c; }
    float d() const { return m_d; }

private:
    float m_a, m_b, m_c, m_d;
};

class PTriangle : public PElement
{
public:
    PTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
        : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3) {}

    PElement::PElementType type() const { return PElement::Triangle; }
    PElement * clone() const { return new PTriangle(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3); }
    float x1() const { return m_x1; }
    float y1() const { return m_y1; }
    float x2() const { return m_x2; }
    float y2() const { return m_y2; }
    float x3() const { return m_x3; }
    float y3() const { return m_y3; }

private:
    float m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;
};

class PBackground : public PElement
{
public:
    PBackground(int v1, int v2, int v3, int alpha=255)
        : m_v1(v1), m_v2(v2), m_v3(v3), m_alpha(alpha) {}

    PElement::PElementType type() const { return PElement::Background; }
    PElement * clone() const { return new PBackground(m_v1, m_v2, m_v3, m_alpha); }
    int v1() const { return m_v1; }
    int v2() const { return m_v2; }
    int v3() const { return m_v3; }
    int alpha() const { return m_alpha; }

private:
    int m_v1, m_v2, m_v3, m_alpha;
};

class PFill : public PElement
{
public:
    PFill(int v1, int v2, int v3, int alpha=255)
        : m_v1(v1), m_v2(v2), m_v3(v3), m_alpha(alpha) {}

    PElement::PElementType type() const { return PElement::Fill; }
    PElement * clone() const { return new PFill(m_v1, m_v2, m_v3, m_alpha); }
    int v1() const { return m_v1; }
    int v2() const { return m_v2; }
    int v3() const { return m_v3; }
    int alpha() const { return m_alpha; }

private:
    int m_v1, m_v2, m_v3, m_alpha;
};

class PNoFill : public PElement
{
public:
    PNoFill() {}
    PElement::PElementType type() const { return PElement::NoFill; }
    PElement * clone() const { return new PNoFill; }
};

class PStroke : public PElement
{
public:
    PStroke(int v1, int v2, int v3, int alpha=255)
        : m_v1(v1), m_v2(v2), m_v3(v3), m_alpha(alpha) {}

    PElement::PElementType type() const { return PElement::Stroke; }
    PElement * clone() const { return new PStroke(m_v1, m_v2, m_v3, m_alpha); }
    int v1() const { return m_v1; }
    int v2() const { return m_v2; }
    int v3() const { return m_v3; }
    int alpha() const { return m_alpha; }

private:
    int m_v1, m_v2, m_v3, m_alpha;
};

class PNoStroke : public PElement
{
public:
    PNoStroke() {}
    PElement::PElementType type() const { return PElement::NoStroke; }
    PElement * clone() const { return new PNoStroke; }
};

class PEllipseMode : public PElement
{
public:
    PEllipseMode(DrawMode mode)
        : m_mode(mode) {}

    PElement::PElementType type() const { return PElement::EllipseMode; }
    PElement * clone() const { return new PEllipseMode(m_mode); }
    DrawMode mode() const { return m_mode; }

private:
    DrawMode m_mode;
};

class PRectMode : public PElement
{
public:
    PRectMode(DrawMode mode)
        : m_mode(mode) {}

    PElement::PElementType type() const { return PElement::RectMode; }
    PElement * clone() const { return new PRectMode(m_mode); }
    DrawMode mode() const { return m_mode; }

private:
    DrawMode m_mode;
};

class PStrokeWeight : public PElement
{
public:
    PStrokeWeight(int weight)
        : m_weight(weight) {}

    PElement::PElementType type() const { return PElement::StrokeWeight; }
    PElement * clone() const { return new PStrokeWeight(m_weight); }
    int weight() const { return m_weight; }

private:
    int m_weight;
};

class PRotate : public PElement
{
public:
    PRotate(float angle)
        : m_angle(angle) {}

    PElement::PElementType type() const { return PElement::Rotate; }
    PElement * clone() const { return new PRotate(m_angle); }
    float angle() const { return m_angle; }

private:
    float m_angle;
};

class PTranslate : public PElement
{
public:
    PTranslate(float x, float y)
        : m_x(x), m_y(y) {}

    PElement::PElementType type() const { return PElement::Translate; }
    PElement * clone() const { return new PTranslate(m_x, m_y); }
    float x() const { return m_x; }
    float y() const { return m_y; }

private:
    float m_x, m_y;
};

PROCESSING_END_NAMESPACE

#endif // P_PELEMENT_H
