/**
 * Processing
 *
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#define P_USE_USER_MAIN
#include "processing.h"
#include "guiengine.h"
#include <cstdlib>
#include <ctime>

PROCESSING_BEGIN_NAMESPACE

int width;
int height;
int frameRate;
Args args;

static const char *const title = "Processing";
static GuiEngine *engine;
static Window *window;
static Canvas *canvas;
static enum Renderer renderer;

/**
 * Processing class
 */
int Processing::exec(int argc, char *argv[], PFunctions &callbacks)
{
    srand(time(NULL));

    args.length = argc;
    args.argv = argv;
    frameRate = P_FRAMERATE_DEFAULT;
    width = P_WIDTH_DEFAULT;
    height = P_HEIGHT_DEFAULT;
    renderer = PDEFAULT;

    engine = GuiEngine::create(GuiEngine::Qt, argc, argv);

    window = engine->createWindow();
    canvas = window->createCanvas(renderer);
    canvas->stroke(0);
    canvas->fill(255);

    if (callbacks["setup"])
        callbacks["setup"]();

    window->setWindowTitle(title);
    window->setFixedSize(width, height);
    canvas = window->replaceCanvas(renderer);
    canvas->setFixedSize(width, height);
    canvas->registerCallbacks(callbacks);
    canvas->setAllElementsPersistent();
    window->show();
    window->start(frameRate);

    int rc = engine->exec();
    delete engine;

    if (callbacks["leave"])
        callbacks["leave"]();

    return rc;
}

/**
 * Functions
 */
void exit()
{
    engine->quit();
}

void loop()
{
    window->loop();
}

void noLoop()
{
    window->noLoop();
}

void pushStyle()
{
    canvas->pushStyle();
}

void popStyle()
{
    canvas->popStyle();
}

void size(int w, int h, enum Renderer r)
{
    if (w < P_WIDTH_MINIMUM)
        w = P_WIDTH_MINIMUM;
    if (h < P_HEIGHT_MINIMUM)
        h = P_HEIGHT_MINIMUM;
    width = w;
    height = h;
    renderer = r;
}

void setFrameRate(int fps)
{
    if (frameRate < P_FRAMERATE_MINIMUM)
        frameRate = P_FRAMERATE_DEFAULT;
    frameRate = fps;
}

void arc(float a, float b, float c, float d, float start, float stop, ArcMode mode)
{
    canvas->arc(a, b, c, d, start, stop, mode);
}

void ellipse(float a, float b, float c, float d)
{
    canvas->ellipse(a, b, c, d);
}

void line(float x1, float y1, float x2, float y2)
{
    canvas->line(x1, y1, x2, y2);
}

void point(float x, float y)
{
    canvas->point(x, y);
}

void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    canvas->quad(x1, y1, x2, y2, x3, y3, x4, y4);
}

void rect(float a, float b, float c, float d)
{
    canvas->rect(a, b, c, d);
}

void rect(float a, float b, float c, float d, float r)
{
    canvas->rect(a, b, c, d, r);
}

void rect(float a, float b, float c, float d, float tl, float tr, float br, float bl)
{
    canvas->rect(a, b, c, d, tl, tr, br, bl);
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    canvas->triangle(x1, y1, x2, y2, x3, y3);
}

void background(color c)
{
    canvas->background(red(c), green(c), blue(c), alpha(c));
}

void background(int rgb)
{
    canvas->background(rgb);
}

void background(int v1, int v2, int v3, int alpha)
{
    canvas->background(v1, v2, v3, alpha);
}

void colorMode(ColorMode mode)
{
    // canvas->colorMode(mode);
}

void fill(color c)
{
    canvas->fill(red(c), green(c), blue(c), alpha(c));
}

void fill(int gray, int alpha)
{
    canvas->fill(gray, alpha);
}

void fill(int v1, int v2, int v3, int alpha)
{
    canvas->fill(v1, v2, v3, alpha);
}

void noFill()
{
    canvas->noFill();
}

void stroke(color c)
{
    canvas->stroke(red(c), green(c), blue(c), alpha(c));
}

void stroke(int gray, int alpha)
{
    canvas->stroke(gray, alpha);
}

void stroke(int v1, int v2, int v3, int alpha)
{
    canvas->stroke(v1, v2, v3, alpha);
}

void noStroke()
{
    canvas->noStroke();
}

float alpha(color rgb)
{
    return (rgb.toInt() & 0xFF);
}

float blue(color rgb)
{
    return ((rgb.toInt() >> 8) & 0xFF);
}

float brightness(color rgb)
{
    return ((rgb.toHsbInt() >> 8) & 0xFF);
}

void color::store(int v1, int v2, int v3, int alpha)
{
    data = ((v1 & 0xFF) << 24) | ((v2 & 0xFF) << 16) | ((v3 & 0xFF) << 8) | (alpha & 0xFF);
}

color::color(int v1, int v2, int v3, int alpha)
{
    store(v1, v2, v3, alpha);
}

static bool is_digit(char c)
{
    return ('0' <= c || c <= '9' || 'A' <= c || c <= 'F' || 'a' <= c || c <= 'f');
}

static int hex_to_int(char c)
{
    int i = c - '0';
    if (i > 9)
        i = c - 'A' + 10;
    if (i > 15)
        i = c - 'a' + 10;
    return i;
}

color::color(const char *hex)
{
    if (hex[0] != '#')
        throw "bad hex notation: no '#'";
    const char *tmp = hex + 1;
    int d[8];
    int i;
    for (i = 0; i < 8; i++)
    {
        char c = tmp[i];
        if (c == '\0')
            break;
        if (!is_digit(c))
            throw "bad hex notation: not digit";
        d[i] = hex_to_int(c);
    }
    if (tmp[i] != '\0')
        throw "bad hex notation";

    int r, g, b, a = 0xFF;
    switch (i)
    {
    case 3:
        r = (d[0] << 4) | d[0];
        g = (d[1] << 4) | d[1];
        b = (d[2] << 4) | d[2];
        break;
    case 6:
        r = (d[0] << 4) | d[1];
        g = (d[2] << 4) | d[3];
        b = (d[4] << 4) | d[5];
        break;
    case 8:
        r = (d[0] << 4) | d[1];
        g = (d[2] << 4) | d[3];
        b = (d[4] << 4) | d[5];
        a = (d[6] << 4) | d[7];
        break;
    default:
        throw "bad hex notation: only support format: #RGB, #RRGGBB, #RRGGBBAA";
    }
    store(r, g, b, a);
}

float green(color rgb)
{
    return ((rgb.toInt() >> 16) & 0xFF);
}

float hue(color rgb)
{
    return ((rgb.toHsbInt() >> 24) & 0xFF);
}

//int lerpColor(int c1, int c2, float amt)
//{
//}

float red(color rgb)
{
    return ((rgb.toInt() >> 24) & 0xFF);
}

float saturation(color rgb)
{
    return ((rgb.toHsbInt() >> 16) & 0xFF);
}

void ellipseMode(DrawMode mode)
{
    canvas->ellipseMode(mode);
}

void rectMode(DrawMode mode)
{
    canvas->rectMode(mode);
}

void strokeWeight(int weight)
{
    canvas->strokeWeight(weight);
}

void rotate(float angle)
{
    canvas->rotate(angle);
}

void translate(float x, float y)
{
    canvas->translate(x, y);
}

int constrain(int amt, int low, int high)
{
    return ((amt < low) ? low : ((amt > high) ? high : amt));
}

float constrain(float amt, float low, float high)
{
    return ((amt < low) ? low : ((amt > high) ? high : amt));
}

float dist(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

float dist(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float lerp(float start, float stop, float amt)
{
    if (amt < 0.0 || amt > 1.0) { throw "lerp(): amt is bad"; }
    return start + amt * (stop - start);
}

float mag(float a, float b)
{
    return sqrt(a * a + b * b);
}

float mag(float a, float b, float c)
{
    return sqrt(a * a + b * b + c * c);
}

float map(float value, float start1, float stop1, float start2, float stop2)
{
    return start2 + (value * (stop2 - start2)) / (stop1 - start1);
}

float norm(float value, float start, float stop)
{
    return start + (value / (stop - start));
}

float degrees(float rad)
{
    if (rad < 0 || rad > (float) TWO_PI) { throw "degree(): rad is bad"; }
    if (rad == 0)           { return 0; }
    if (rad == QUARTER_PI)  { return 45; }
    if (rad == HALF_PI)     { return 90; }
    if (rad == PI)          { return 180; }
    if (rad == TWO_PI || rad == TAU) { return 360; }
    return (rad * (180.0 / PI));
}

float radians(float deg)
{
    if (deg < 0 || deg > 360.0) { throw "radians(): deg is bad"; }
    if (deg == 0)   { return 0; }
    if (deg == 45)  { return QUARTER_PI; }
    if (deg == 90)  { return HALF_PI; }
    if (deg == 180) { return PI; }
    if (deg == 360) { return TWO_PI; }
    return ((deg * PI) / 180.0);
}

float random(float high)
{
    return random(0.0, high);
}

float random(float low, float high)
{
    return (low + ((high - low) * (float) rand()) / (float) RAND_MAX);
}

void randomSeed(int seed)
{
    srand(seed);
}

PROCESSING_END_NAMESPACE
