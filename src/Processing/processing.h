/**
 * Processing
 *
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PROCESSING_H
#define PROCESSING_H

#include "macro.h"
#include "args.h"

#include <cmath>
#include <iostream>

// Non-cross compilers
#define PB(x) void __attribute__((weak)) x();
PFUNCTIONS
#undef PB

PROCESSING_BEGIN_NAMESPACE

class Processing
{
public:
    static int start(int argc, char *argv[])
    {
        PFunctions functions;
#define PB(x) functions[#x] = x;
        PFUNCTIONS
#undef PB
        return Processing::exec(argc, argv, functions);
    }

private:
    static int exec(int argc, char *argv[], PFunctions &);
};

enum EllipseMode
{
    RADIUS,
    CENTER,
    CORNER,
    CORNERS
};

enum ColorMode
{
    RGB,
    HSB
};

// Structure
void exit();
void loop();
void noLoop();
void pushStyle();
void popStyle();

// Environment
void size(int width, int height, enum Renderer renderer=PDEFAULT);
void setFrameRate(int fps);

// 2D Primitives
void ellipse(float a, float b, float c, float d);
void line(float x1, float y1, float x2, float y2);
void point(float x, float y);
void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void rect(float a, float b, float c, float d);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);

// Color
void background(int);
void background(int v1, int v2, int v3, int alpha=255);
void colorMode(ColorMode mode);
void fill(int gray, int alpha=255);
void fill(int v1, int v2, int v3, int alpha=255);
void noFill();
void stroke(int gray, int alpha=255);
void stroke(int v1, int v2, int v3, int alpha=255);
void noStroke();

// Attribute
void ellipseMode(EllipseMode mode);
void strokeWeight(int weight);

// Output
template <class T>
inline void print(T what) { std::cout << what << std::endl; }

// Transform
void rotate(float angle);
void translate(float x, float y);

// Math
int constrain(int amt, int low, int high);
float constrain(float amt, float low, float high);
float dist(float x1, float y1, float x2, float y2);
float dist(float x1, float y1, float z1, float x2, float y2, float z2);
float lerp(float start, float stop, float amt);
float mag(float a, float b);
float mag(float a, float b, float c);
float map(float value, float start1, float stop1, float start2, float stop2);
float norm(float value, float start, float stop);

inline int max(int a, int b) { return (a >= b ? a : b); }
inline int min(int a, int b) { return (a <= b ? a : b); }
inline float max(float a, float b) { return (a >= b ? a : b); }
inline float min(float a, float b) { return (a <= b ? a : b); }
inline int max(int a, int b, int c) { return (a >= b ? max(a, c) : max(b, c)); }
inline int min(int a, int b, int c) { return (a <= b ? min(a, c) : min(b, c)); }
inline float max(float a, float b, float c) { return (a >= b ? max(a, c) : max(b, c)); }
inline float min(float a, float b, float c) { return (a <= b ? min(a, c) : min(b, c)); }
inline float sq(float n) { return n * n; }

float degrees(float rad);
float radians(float deg);

float random(float high);
float random(float low, float high);
void randomSeed(int seed);

#define HALF_PI     1.57079632679489661923
#define PI          3.14159265358979323846
#define QUARTER_PI  0.785398163397448309616
#define TAU         6.28318530717958647692
#define TWO_PI      6.28318530717958647692

// Global variables
extern PROCESSING_NAMESPACE::Args args;
extern int width;
extern int height;
extern int frameRate;
extern int frameCount;
extern int keyCode;
extern bool isKeyPressed;
extern char key;

PROCESSING_END_NAMESPACE

#ifndef P_USE_USER_MAIN
int main(int argc, char *argv[])
{
    try {
        return PROCESSING_NAMESPACE::Processing::start(argc, argv);
    } catch (const char *str) {
        std::cout << "Error: " << str << std::endl;
    }
}
#endif // P_USE_USER_MAIN

#endif // PROCESSING_H