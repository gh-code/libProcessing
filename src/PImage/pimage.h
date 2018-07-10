/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PIMAGE_H
#define PIMAGE_H

enum PFormat
{
    RGB,
    ARGB,
    ALPHA
};

class PImage
{
public:
};

PImage createImage(int w, int h, enum PFormat format) {}
void image(const PImage &img, float a, float b, float c, float d) {}

#endif // PIMAGE_H
