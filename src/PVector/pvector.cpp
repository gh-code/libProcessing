/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include "pvector.h"
#include <cmath>

PVector::PVector()
    : x(0.0), y(0.0), z(0.0)
{
}

PVector::PVector(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
{
}

PVector::PVector(float x_, float y_)
    : x(x_), y(y_), z(0.0)
{
}

PVector & PVector::set(float x_, float y_, float z_)
{
    x = x_;
    y = y_;
    z = z_;
    return (*this);
}

PVector & PVector::set(float x_, float y_)
{
    x = x_;
    y = y_;
    z = 0.0;
    return (*this);
}

PVector & PVector::set(const PVector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return (*this);
}

PVector PVector::copy() const
{
    return (*this);
}

PVector PVector::add(const PVector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return (*this);
}

float PVector::mag() const
{
    return sqrt(x * x + y * y + z * z);
}
