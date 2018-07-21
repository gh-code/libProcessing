/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PVECTOR_H
#define PVECTOR_H

#include "pglobal.h"
#include <vector>

PROCESSING_BEGIN_NAMESPACE

class PVectorPrivate;

class PVector
{
public:
    enum Type { None, V2D, V3D };

public:
    PVector();
    PVector(float x, float y);
    PVector(float x, float y, float z);
    PVector(const PVector &);
    PVector(PVectorPrivate *);
    PVector & operator=(const PVector &);
    bool operator==(const PVector &) const;
    bool operator!=(const PVector &) const;
    ~PVector();

    bool isNull() const;
    bool is2D() const { return type() == PVector::V2D; }
    bool is3D() const { return type() == PVector::V3D; }
    Type type() const;
    float x() const;
    float y() const;
    float z() const;
    float mag() const;
    float magSq() const;
    float dist(const PVector &v) const;
    float dot(float x, float y, float z) const;
    float dot(float x, float y) const;
    float dot(const PVector &v) const;
    float heading() const;
    PVector cross(const PVector &v) const;
    PVector copy() const;
    std::vector<float> array() const;

    PVector & to2D();
    PVector & to3D();
    PVector & set(float x, float y, float z);
    PVector & set(float x, float y);
    PVector & set(const PVector &v);
    PVector & add(float x, float y, float z);
    PVector & add(float x, float y);
    PVector & add(const PVector &v);
    PVector & sub(float x, float y, float z);
    PVector & sub(float x, float y);
    PVector & sub(const PVector &v);
    PVector & mult(float n);
    PVector & div(float n);
    PVector & normalize();
    PVector & limit(float max);
    PVector & setMag(float len);
    PVector & rotate(float theta);
    PVector & lerp(float x, float y, float z, float amt);
    PVector & lerp(float x, float y, float amt);
    PVector & lerp(const PVector &v, float amt);
    void dontWarn();

    static float dist(const PVector &v1, const PVector &v2);
    static float dot(const PVector &v1, const PVector &v2);
    static PVector add(const PVector &v1, const PVector &v2);
    static PVector add(const PVector &v1, const PVector &v2, PVector *target);
    static PVector sub(const PVector &v1, const PVector &v2);
    static PVector sub(const PVector &v1, const PVector &v2, PVector *target);
    static PVector mult(const PVector &v, float n);
    static PVector mult(const PVector &v, float n, PVector *target);
    static PVector div(const PVector &v, float n);
    static PVector div(const PVector &v, float n, PVector *target);
    static PVector lerp(const PVector &v1, const PVector &v2, float amt);
    // static PVector normalize(PVector *target);
    // static PVector cross(const PVector &v, PVector *target);
    static PVector cross(const PVector &v1, const PVector &v2, PVector *target);
    static PVector random2D();
    static PVector random2D(PVector *target);
    static PVector random3D();
    static PVector random3D(PVector *target);
    static PVector fromAngle(float angle);
    static PVector fromAngle(float angle, PVector *target);
    static float angleBetween(const PVector &v1, const PVector &v2);

    friend std::ostream & operator<<(std::ostream &os, const PVector &);

private:
    PVectorPrivate *impl;
    bool verbose;
};

PROCESSING_END_NAMESPACE

#endif // PVECTOR_H
