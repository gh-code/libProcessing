/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PVECTOR_H
#define PVECTOR_H

class PVector
{
public:
    PVector();
    PVector(float x, float y, float z);
    PVector(float x, float y);

    PVector & set(float x, float y, float z);
    PVector & set(float x, float y);
    PVector & set(const PVector &v);
    PVector copy() const;
    PVector add(const PVector &v);
    float mag() const;

private:
    float x;
    float y;
    float z;
};

#endif // PVECTOR_H
