/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "pvector.h"
#include <qatomic.h>
#include <iostream>
#include <cmath>

PROCESSING_BEGIN_NAMESPACE

float random(float high);
float random(float low, float high);
void randomSeed(int seed);

class PVectorPrivate
{
public:
    PVectorPrivate() {}
    virtual ~PVectorPrivate() {}

    virtual PVector::Type type() const = 0;

    virtual float x() const = 0;
    virtual float y() const = 0;
    virtual float z() const = 0;

    virtual float mag() const = 0;
    virtual float magSq() const = 0;
    virtual float dot(float x, float y) const = 0;
    virtual float dot(float x, float y, float z) const = 0;
    virtual float heading() const = 0;

    virtual void set(float x, float y) = 0;
    virtual void set(float x, float y, float z) = 0;
    virtual void add(float x, float y) = 0;
    virtual void add(float x, float y, float z) = 0;
    virtual void sub(float x, float y) = 0;
    virtual void sub(float x, float y, float z) = 0;
    virtual void mult(float n) = 0;
    virtual void div(float n) = 0;
    virtual void normalize() = 0;
    virtual void limit(float max) = 0;
    virtual void setMag(float len) = 0;
    virtual void rotate(float theta) = 0;
    virtual void lerp(float x, float y, float amt) = 0;
    virtual void lerp(float x, float y, float z, float amt) = 0;

    QAtomicInt ref;
    bool verbose;
};

class PVector2D : public PVectorPrivate
{
public:
    PVector2D(float x, float y);

    virtual PVector::Type type() const OVERRIDE { return PVector::V2D; }

    float x() const OVERRIDE { return m_x; }
    float y() const OVERRIDE { return m_y; }
    virtual float z() const OVERRIDE { throw "no z dimension for 2D vector"; }

    virtual float mag() const OVERRIDE { return sqrt(magSq()); }
    virtual float magSq() const OVERRIDE { return m_x * m_x + m_y * m_y; }
    virtual float dot(float x, float y) const OVERRIDE { return x * m_x + y * m_y; }
    virtual float dot(float x, float y, float z) const OVERRIDE;
    virtual float heading() const OVERRIDE;

    virtual void set(float x, float y) OVERRIDE;
    virtual void set(float x, float y, float z) OVERRIDE;
    virtual void add(float x, float y) OVERRIDE;
    virtual void add(float x, float y, float z) OVERRIDE;
    virtual void sub(float x, float y) OVERRIDE;
    virtual void sub(float x, float y, float z) OVERRIDE;
    virtual void mult(float n) OVERRIDE;
    virtual void div(float n) OVERRIDE;
    virtual void normalize() OVERRIDE;
    virtual void limit(float max) OVERRIDE;
    virtual void setMag(float len) OVERRIDE;
    virtual void rotate(float theta) OVERRIDE;
    virtual void lerp(float x, float y, float amt) OVERRIDE;
    virtual void lerp(float x, float y, float z, float amt) OVERRIDE;

    float m_x;
    float m_y;
};

class PVector3D : public PVector2D
{
public:
    PVector3D(float x, float y, float z);

    PVector::Type type() const OVERRIDE { return PVector::V3D; }

    float z() const OVERRIDE { return m_z; }

    float magSq() const OVERRIDE { return PVector2D::magSq() + m_z * m_z; }
    float dot(float x, float y, float z) const OVERRIDE { return PVector2D::dot(x, y) + z * m_z; }
    float heading() const OVERRIDE { throw "PVector::heading() is only for 2D vector"; }

    void set(float x, float y) OVERRIDE;
    void set(float x, float y, float z) OVERRIDE;
    void add(float x, float y, float z) OVERRIDE;
    void sub(float x, float y, float z) OVERRIDE;
    void mult(float n) OVERRIDE;
    void div(float n) OVERRIDE;
    void normalize() OVERRIDE;
    void rotate(float theta) OVERRIDE;
    void lerp(float x, float y, float amt) OVERRIDE;
    void lerp(float x, float y, float z, float amt) OVERRIDE;

    float m_z;
};

PVector2D::PVector2D(float x, float y)
    : m_x(x), m_y(y)
{
    ref = 1;
    verbose = 1;
}

float PVector2D::dot(float x, float y, float z) const
{
    (void) x;
    (void) y;
    (void) z;
    throw "no z for 2D vector";
}

float PVector2D::heading() const
{
    if (m_x == 0.0)
    {
        if (m_y == 0.0)
            return 0.0;
        return (m_y > 0.0 ? M_PI_2 : -M_PI_2);
    }
    return atanf(m_y / m_x);
}

void PVector2D::set(float x, float y)
{
    m_x = x;
    m_y = y;
}

void PVector2D::set(float x, float y, float z)
{
    (void) x;
    (void) y;
    (void) z;
    throw "no z for 2D vector";
}

void PVector2D::add(float x, float y)
{
    m_x += x;
    m_y += y;
}

void PVector2D::add(float x, float y, float z)
{
    (void) x;
    (void) y;
    (void) z;
    throw "no z for 2D vector";
}

void PVector2D::sub(float x, float y)
{
    m_x -= x;
    m_y -= y;
}

void PVector2D::sub(float x, float y, float z)
{
    (void) x;
    (void) y;
    (void) z;
    throw "no z for 2D vector";
}

void PVector2D::mult(float n)
{
    m_x *= n;
    m_y *= n;
}

void PVector2D::div(float n)
{
    if (n == 0.0)
        throw "divided by zero";
    m_x /= n;
    m_y /= n;
}

void PVector2D::normalize()
{
    float m = mag();
    if (m) // avoid devided by 0
    {
        m_x /= m;
        m_y /= m;
    }
}

void PVector2D::limit(float max)
{
    normalize();
    mult(max);
}

void PVector2D::setMag(float len)
{
    float m = mag();
    if (m) // avoid devided by 0
    {
        float scale = len / m;
        mult(scale);
    }
}

void PVector2D::rotate(float theta)
{
    float new_x = m_x * cos(theta) - m_y * sin(theta);
    float new_y = m_x * sin(theta) + m_y * cos(theta);
    m_x = new_x;
    m_y = new_y;
}

void PVector2D::lerp(float x, float y, float amt)
{
    float new_x = m_x + amt * (x - m_x);
    float new_y = m_y + amt * (y - m_y);
    m_x = new_x;
    m_y = new_y;
}

void PVector2D::lerp(float x, float y, float z, float amt)
{
    (void) x;
    (void) y;
    (void) z;
    (void) amt;
    throw "no z for 2D vector";
}

PVector3D::PVector3D(float x, float y, float z)
    : PVector2D(x, y), m_z(z)
{
}

void PVector3D::set(float x, float y)
{
    PVector2D::set(x, y);
    if (verbose)
        std::cerr << "Warning: z is set to 0\n";
    m_z = 0.0;
}

void PVector3D::set(float x, float y, float z)
{
    PVector2D::set(x, y);
    m_z = z;
}

void PVector3D::add(float x, float y, float z)
{
    PVector2D::add(x, y);
    m_z += z;
}

void PVector3D::sub(float x, float y, float z)
{
    PVector2D::sub(x, y);
    m_z -= z;
}

void PVector3D::mult(float n)
{
    PVector2D::mult(n);
    m_z *= n;
}

void PVector3D::div(float n)
{
    PVector2D::div(n);
    m_z /= n;
}

void PVector3D::normalize()
{
    float m = mag();
    if (m) // avoid devided by 0
    {
        m_x /= m;
        m_y /= m;
        m_z /= m;
    }
}

void PVector3D::rotate(float theta)
{
    if (verbose)
        std::cerr << "Warning: rotate about z-axis";
    PVector2D::rotate(theta);
}

void PVector3D::lerp(float x, float y, float amt)
{
    if (verbose)
        std::cerr << "Warning: lerp() z is assumed 0";
    lerp(x, y, 0.0, amt);
}

void PVector3D::lerp(float x, float y, float z, float amt)
{
    float new_x = m_x + amt * (x - m_x);
    float new_y = m_y + amt * (y - m_y);
    float new_z = m_z + amt * (z - m_z);
    m_x = new_x;
    m_y = new_y;
    m_z = new_z;
}

PVector::PVector()
{
    impl = 0;
    verbose = 1;
}

PVector::PVector(float x, float y, float z)
{
    impl = new PVector3D(x, y, z);
    verbose = 1;
}

PVector::PVector(float x, float y)
{
    impl = new PVector2D(x, y);
    verbose = 1;
}

PVector::PVector(const PVector &v)
{
    impl = v.impl;
    if (impl)
        impl->ref.ref();
}

PVector::PVector(PVectorPrivate *v)
{
    impl = v;
    if (impl)
        impl->ref.ref();
}

PVector & PVector::operator=(const PVector &v)
{
    if (v.impl)
        v.impl->ref.ref();
    if (impl && !impl->ref.deref())
        delete impl;
    impl = v.impl;
    return *this;
}

bool PVector::operator==(const PVector &v) const
{
    return (impl == v.impl);
}

bool PVector::operator!=(const PVector &v) const
{
    return (impl != v.impl);
}

PVector::~PVector()
{
    if (impl && !impl->ref.deref())
        delete impl;
}

bool PVector::isNull() const
{
    return (impl == 0);
}

PVector::Type PVector::type() const
{
    if (!impl)
        return PVector::None;
    return impl->type();
}

float PVector::x() const
{
    if (!impl)
        return 0.0;
    return impl->x();
}

float PVector::y() const
{
    if (!impl)
        return 0.0;
    return impl->y();
}

float PVector::z() const
{
    if (!impl)
        return 0.0;
    return impl->z();
}

float PVector::mag() const
{
    if (!impl)
        return 0.0;
    return impl->mag();
}

float PVector::magSq() const
{
    if (!impl)
        return 0.0;
    return impl->magSq();
}

float PVector::dist(const PVector &v) const
{
    if (!impl)
        return 0.0;
    PVector temp = copy();
    return temp.sub(v).mag();
}

float PVector::dist(const PVector &v1, const PVector &v2)
{
    return v1.dist(v2);
}

float PVector::dot(float x, float y) const
{
    if (!impl)
        return 0.0;
    return impl->dot(x, y);
}

float PVector::dot(float x, float y, float z) const
{
    if (!impl)
        return 0.0;
    return impl->dot(x, y, z);
}

float PVector::dot(const PVector &v) const
{
    float result = 0.0;
    if (v.type() != type())
        throw "PVector::dot(): can't dot vector between 2D and 3D";
    switch (type())
    {
        case PVector::None:
            break;
        case PVector::V2D:
            result = dot(v.x(), v.y());
            break;
        case PVector::V3D:
            result = dot(v.x(), v.y(), v.z());
            break;
    }
    return result;
}

float PVector::dot(const PVector &v1, const PVector &v2)
{
    return v1.dot(v2);
}

float PVector::heading() const
{
    if (impl)
        return impl->heading();
    return 0.0;
}

PVector PVector::cross(const PVector &v) const
{
    PVector temp;
    if (!impl || !v.impl)
        return temp;
    PVector a = copy();
    PVector b = v.copy();
    if (a.is2D())
        a.to3D();
    if (b.is2D())
        b.to3D();
    float s1 = a.y() * b.z() - a.z() * b.y();
    float s2 = a.z() * b.x() - a.x() * b.z();
    float s3 = a.x() * b.y() - a.y() * b.x();
    temp = PVector(s1, s2, s3);
    return temp;
}

PVector PVector::cross(const PVector &v1, const PVector &v2, PVector *target)
{
    PVector temp = v1.cross(v2);
    if (target)
        (*target) = temp;
    return temp;
}

PVector PVector::copy() const
{
    PVector temp;
    switch (type())
    {
        case PVector::None:
            break;
        case PVector::V2D:
            temp = PVector(x(), y());
            break;
        case PVector::V3D:
            temp = PVector(x(), y(), z());
            break;
    }
    return temp;
}

std::vector<float> PVector::array() const
{
    std::vector<float> temp(3, 0.0);
    if (!impl)
        return temp;
    temp[0] = x();
    temp[1] = y();
    temp[2] = (is3D() ? z() : 0);
    return temp;
}

PVector & PVector::to2D()
{
    if (verbose && z())
        std::cerr << "z is threw away\n";
    PVector temp(x(), y());
    (*this) = temp;
    return (*this);
}

PVector & PVector::to3D()
{
    PVector temp(x(), y(), 0.0);
    (*this) = temp;
    return (*this);
}

PVector & PVector::set(float x, float y, float z)
{
    if (impl)
        impl->set(x, y, z);
    return (*this);
}

PVector & PVector::set(float x, float y)
{
    if (impl)
        impl->set(x, y);
    return (*this);
}

PVector & PVector::set(const PVector &v)
{
    if (!impl)
    {
        (*this) = v.copy();
        return (*this);
    }
    if (v.type() != type())
        throw "PVector::set(): can't set vector between 2D and 3D";
    switch (type())
    {
        case PVector::V2D:
            impl->set(v.x(), v.y());
            break;
        case PVector::V3D:
            impl->set(v.x(), v.y(), v.z());
            break;
        case PVector::None:
            break;
    }
    return (*this);
}

PVector & PVector::add(float x, float y)
{
    if (impl)
        impl->add(x, y);
    return (*this);
}

PVector & PVector::add(float x, float y, float z)
{
    if (impl)
        impl->add(x, y, z);
    return (*this);
}

PVector & PVector::add(const PVector &v)
{
    if (v.type() != type())
        throw "PVector::add(): can't add vector between 2D and 3D";
    switch (type())
    {
        case PVector::None:
            break;
        case PVector::V2D:
            add(v.x(), v.y());
            break;
        case PVector::V3D:
            add(v.x(), v.y(), v.z());
            break;
    }
    return (*this);
}

PVector PVector::add(const PVector &v1, const PVector &v2)
{
    PVector temp = v1.copy();
    temp.add(v2);
    return temp;
}

PVector PVector::add(const PVector &v1, const PVector &v2, PVector *target)
{
    PVector temp = v1.copy();
    temp.add(v2);
    if (target)
        (*target) = temp;
    return temp;
}

PVector & PVector::sub(float x, float y)
{
    if (impl)
        impl->sub(x, y);
    return (*this);
}

PVector & PVector::sub(float x, float y, float z)
{
    if (impl)
        impl->sub(x, y, z);
    return (*this);
}

PVector & PVector::sub(const PVector &v)
{
    if (v.type() != type())
        throw "PVector::sub(): can't sub vector between 2D and 3D";
    switch (type())
    {
        case PVector::None:
            break;
        case PVector::V2D:
            sub(v.x(), v.y());
            break;
        case PVector::V3D:
            sub(v.x(), v.y(), v.z());
            break;
    }
    return (*this);
}

PVector PVector::sub(const PVector &v1, const PVector &v2)
{
    PVector temp = v1.copy();
    temp.sub(v2);
    return temp;
}

PVector PVector::sub(const PVector &v1, const PVector &v2, PVector *target)
{
    PVector temp = v1.copy();
    temp.sub(v2);
    if (target)
        (*target) = temp;
    return temp;
}

PVector & PVector::mult(float n)
{
    if (impl)
        impl->mult(n);
    return (*this);
}

PVector PVector::mult(const PVector &v, float n)
{
    PVector temp = v.copy();
    temp.mult(n);
    return temp;
}

PVector PVector::mult(const PVector &v, float n, PVector *target)
{
    PVector temp = v.copy();
    temp.mult(n);
    if (target)
        (*target) = temp;
    return temp;
}

PVector & PVector::div(float n)
{
    if (impl)
        impl->div(n);
    return (*this);
}

PVector PVector::div(const PVector &v, float n)
{
    PVector temp = v.copy();
    temp.div(n);
    return temp;
}

PVector PVector::div(const PVector &v, float n, PVector *target)
{
    PVector temp = v.copy();
    temp.div(n);
    if (target)
        (*target) = temp;
    return temp;
}

PVector PVector::lerp(const PVector &v1, const PVector &v2, float amt)
{
    PVector temp = v1.copy();
    temp.lerp(v2, amt);
    return temp;
}

PVector & PVector::normalize()
{
    if (impl)
        impl->normalize();
    return (*this);
}

PVector & PVector::limit(float max)
{
    if (impl)
        impl->limit(max);
    return (*this);
}

PVector & PVector::setMag(float len)
{
    if (impl)
        impl->setMag(len);
    return (*this);
}

PVector & PVector::rotate(float theta)
{
    if (impl)
        impl->rotate(theta);
    return (*this);
}

PVector & PVector::lerp(float x, float y, float z, float amt)
{
    if (impl)
        impl->lerp(x, y, z, amt);
    return (*this);
}

PVector & PVector::lerp(float x, float y, float amt)
{
    if (impl)
        impl->lerp(x, y, amt);
    return (*this);
}

PVector & PVector::lerp(const PVector &v, float amt)
{
    if (v.type() != type())
        throw "PVector::lerp(): can't lerp vector between 2D and 3D";
    switch (type())
    {
        case PVector::None:
            break;
        case PVector::V2D:
            lerp(v.x(), v.y(), amt);
            break;
        case PVector::V3D:
            lerp(v.x(), v.y(), v.z(), amt);
            break;
    }
    return (*this);
}

void PVector::dontWarn()
{
    if (impl)
        impl->verbose = 0;
    verbose = 0;
}

PVector PVector::random2D()
{
    float rx = random(-1.0, 1.0);
    float ry = random(-1.0, 1.0);
    PVector temp(new PVector2D(rx, ry));
    return temp;
}

PVector PVector::random2D(PVector *target)
{
    PVector temp = PVector::random2D();
    if (target)
        (*target) = temp;
    return temp;
}

PVector PVector::random3D()
{
    float rx = random(-1.0, 1.0);
    float ry = random(-1.0, 1.0);
    float rz = random(-1.0, 1.0);
    PVector temp(new PVector3D(rx, ry, rz));
    return temp;
}

PVector PVector::random3D(PVector *target)
{
    PVector temp = PVector::random3D();
    if (target)
        (*target) = temp;
    return temp;
}

PVector PVector::fromAngle(float angle)
{
    float x = cos(angle);
    float y = sin(angle);
    PVector temp(new PVector2D(x, y));
    return temp;
}

PVector PVector::fromAngle(float angle, PVector *target)
{
    PVector temp = PVector::fromAngle(angle);
    if (target)
        (*target) = temp;
    return temp;
}

float PVector::angleBetween(const PVector &v1, const PVector &v2)
{
    float ab = v1.mag() * v2.mag();
    return (ab ? acos(v1.dot(v2) / ab) : M_PI_2);
}

std::ostream & operator<<(std::ostream &os, const PVector &v)
{
    os << "[ " << v.x()
       << ", " << v.y();
    if (v.is3D())
        os << ", " << v.z();
    os << " ]\n";
    return os;
}

PROCESSING_END_NAMESPACE