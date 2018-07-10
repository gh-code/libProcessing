/**
 * Processing
 *
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#define P_USE_USER_MAIN
#include "processing.h"
#undef P_USE_USER_MAIN
#include "guiengine.h"
#include <list>
#include <cstdlib>
#include <ctime>

PROCESSING_BEGIN_NAMESPACE

int width;
int height;
int frameRate;
Args args;

/**
 * ProcessingPrivate class
 */
class ProcessingPrivate
{
public:
    const char * const title = "Processing";

public:
    ~ProcessingPrivate();
    static ProcessingPrivate *getInstance()
    {
        static ProcessingPrivate *inst = 0;
        if (!inst)
            inst = new ProcessingPrivate;
        return inst;
    }

    inline void exit() { engine->quit(); }
    inline void loop() { window->loop(); }
    inline void noLoop() { window->noLoop(); }
    inline void pushStyle() { canvas->pushStyle(); }
    inline void popStyle() { canvas->popStyle(); }

    inline void size(int w, int h, enum Renderer r)
    {
        if (w < P_WIDTH_MINIMUM)
            w = P_WIDTH_MINIMUM;
        if (h < P_HEIGHT_MINIMUM)
            h = P_HEIGHT_MINIMUM;
        width = w;
        height = h;
        renderer = r;
        PROCESSING_NAMESPACE::width = w;
        PROCESSING_NAMESPACE::height = h;
    }
    inline void setFrameRate(int fps) {
        if (frameRate < P_FRAMERATE_MINIMUM)
            frameRate = P_FRAMERATE_DEFAULT;
        frameRate = fps;
        // TODO: calculate frame rate
        PROCESSING_NAMESPACE::frameRate = frameRate;
    }
    inline void ellipse(float a, float b, float c, float d) { canvas->ellipse(a, b, c, d); }
    inline void line(float x1, float y1, float x2, float y2) { canvas->line(x1, y1, x2, y2); }
    inline void point(float x, float y) { canvas->point(x, y); }
    inline void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) { canvas->quad(x1, y1, x2, y2, x3, y3, x4, y4); }
    inline void rect(float a, float b, float c, float d) { canvas->rect(a, b, c, d); }
    inline void triangle(float x1, float y1, float x2, float y2, float x3, float y3) { canvas->triangle(x1, y1, x2, y2, x3, y3); }

    inline void background(int rgb) { canvas->background(rgb); }
    inline void background(int v1, int v2, int v3, int alpha=255) { canvas->background(v1, v2, v3, alpha); }
    inline void colorMode(ColorMode mode) {}
    inline void fill(int gray, int alpha=255) { canvas->fill(gray, alpha); }
    inline void fill(int v1, int v2, int v3, int alpha=255) { canvas->fill(v1, v2, v3, alpha); }
    inline void noFill() { canvas->noFill(); }
    inline void stroke(int gray, int alpha=255) { canvas->stroke(gray, alpha); }
    inline void stroke(int v1, int v2, int v3, int alpha=255) { canvas->stroke(v1, v2, v3, alpha); }
    inline void noStroke() { canvas->noStroke(); }

    inline void strokeWeight(int weight) { canvas->strokeWeight(weight); }

    inline void rotate(float angle) { canvas->rotate(angle); }
    inline void translate(float x, float y) { canvas->translate(x, y); }

    int exec(int, char **);

private:
    friend class Processing;

    ProcessingPrivate();
    ProcessingPrivate & operator=(const ProcessingPrivate &);

    int width;
    int height;
    enum Renderer renderer;
    int frameRate;

    GuiEngine *engine;
    Window *window;
    Canvas *canvas;
    PFunctions callbacks;
};

ProcessingPrivate::~ProcessingPrivate()
{
    // These will be deleted elsewhere
    // engine;
    // window;
    // canvas;
}

ProcessingPrivate::ProcessingPrivate()
    : width(P_WIDTH_DEFAULT), height(P_HEIGHT_DEFAULT), renderer(PDEFAULT),
      frameRate(P_FRAMERATE_DEFAULT), engine(0), window(0), canvas(0)
{
}

int ProcessingPrivate::exec(int argc, char *argv[])
{
    engine = GuiEngine::create(GuiEngine::Qt, argc, argv);

    window = engine->createWindow();
    window->setWindowTitle(title);
    canvas = window->createCanvas(renderer);
    canvas->fill(255);

    if (callbacks["setup"])
        callbacks["setup"]();

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
 * Processing clase
 */
int Processing::exec(int argc, char *argv[], PFunctions &callbacks)
{
    args.length = argc;
    args.argv = argv;

    srand(time(NULL));

    ProcessingPrivate *inst = ProcessingPrivate::getInstance();
    inst->callbacks = callbacks;
    int rc = inst->exec(argc, argv);
    delete inst;

    return rc;
}

/**
 * Functions
 */
void exit()
{
    ProcessingPrivate::getInstance()->exit();
}

void loop()
{
    ProcessingPrivate::getInstance()->loop();
}

void noLoop()
{
    ProcessingPrivate::getInstance()->noLoop();
}

void pushStyle()
{
    ProcessingPrivate::getInstance()->pushStyle();
}

void popStyle()
{
    ProcessingPrivate::getInstance()->popStyle();
}

void size(int width, int height, enum Renderer renderer)
{
    ProcessingPrivate::getInstance()->size(width, height, renderer);
}

void setFrameRate(int fps)
{
    ProcessingPrivate::getInstance()->setFrameRate(fps);
}

void ellipse(float a, float b, float c, float d)
{
    ProcessingPrivate::getInstance()->ellipse(a, b, c, d);
}

void line(float x1, float y1, float x2, float y2)
{
    ProcessingPrivate::getInstance()->line(x1, y1, x2, y2);
}

void point(float x, float y)
{
    ProcessingPrivate::getInstance()->point(x, y);
}

void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    ProcessingPrivate::getInstance()->quad(x1, y1, x2, y2, x3, y3, x4, y4);
}

void rect(float a, float b, float c, float d)
{
    ProcessingPrivate::getInstance()->rect(a, b, c, d);
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    ProcessingPrivate::getInstance()->triangle(x1, y1, x2, y2, x3, y3);
}

void background(int rgb)
{
    ProcessingPrivate::getInstance()->background(rgb);
}

void background(int v1, int v2, int v3, int alpha)
{
    ProcessingPrivate::getInstance()->background(v1, v2, v3, alpha);
}

void colorMode(ColorMode mode)
{
    ProcessingPrivate::getInstance()->colorMode(mode);
}

void fill(int gray, int alpha)
{
    ProcessingPrivate::getInstance()->fill(gray, alpha);
}

void fill(int v1, int v2, int v3, int alpha)
{
    ProcessingPrivate::getInstance()->fill(v1, v2, v3, alpha);
}

void noFill()
{
    ProcessingPrivate::getInstance()->noFill();
}

void stroke(int gray, int alpha)
{
    ProcessingPrivate::getInstance()->stroke(gray, alpha);
}

void stroke(int v1, int v2, int v3, int alpha)
{
    ProcessingPrivate::getInstance()->stroke(v1, v2, v3, alpha);
}

void noStroke()
{
    ProcessingPrivate::getInstance()->noStroke();
}

void strokeWeight(int weight)
{
    ProcessingPrivate::getInstance()->strokeWeight(weight);
}

void rotate(float angle)
{
    ProcessingPrivate::getInstance()->rotate(angle);
}

void translate(float x, float y)
{
    ProcessingPrivate::getInstance()->translate(x, y);
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
