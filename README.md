# libProcessing

[Processing](https://processing.org "Processing") is a flexible software sketchbook and a language for learning how to code within the context of the visual arts.
libProcessing is a C++ library for Processing.

## Requirement
* Qt 5

## Usage
Please see [libProcessingTemplate](https://github.com/gh-code/libProcessingTemplate "libProcessingTemplate").

## Reference
WARNING: This is a starting project and most of the APIs are not supported yet or partially implemented. Some API interfaces are C/C++ specific because of the language limitations.

Official/Java version is [Processing Reference](https://processing.org/reference/ "Processing Reference").

WARNING: I have a real job so I can only spend a little time on this project. The functionality of functions are only partially tested and it is not recommented for real use.

### Structure
* () (parentheses)
* , (comma)
* . (dot)
* /* */ (multiline comment)
* /** */ (doc comment)
* // (comment)
* ; (semicolon)
* = (assign)
* [] (array access)
* {} (curly braces)
* catch
* class
* draw()
* exit()
* false
* final (C++ 11)
* loop()
* new
* noLoop()
* nullptr (C++ 11)
* popStyle()
* private
* public
* pushStyle()
* return
* setup()
* static
* this
* true
* try
* void

### Envrionment
* frameCount
* frameRate
* height
* setFrameRate()
* size()
* width

### Data
#### Primitive
* bool
* char
* double
* float
* int
* long

### Control
#### Relational Operators
* != (inequality)
* < (less than)
* <= (less than or equal to)
* == (equality)
* \> (greater than)
* \>= (greater than or equal to)

#### Iteration
* for
* while

#### Conditionals
* ?: (conditional)
* break
* case
* continue
* default
* else
* if
* switch

#### Logical Operators
* ! (logical NOT)
* && (logical AND)
* || (logical OR)

### Shape
#### 2D Primitives
* arc()
* ellipse()
* line()
* point()
* quad()
* rect()
* triangle()

#### Attributes
* ellipseMode()
* rectMode()
* strokeWeight()

### Input
#### Mouse
* mouseClicked()
* mouseDragged()
* mouseMoved()
* mousePressed()
* isMousePressed
* mouseReleased()
* mouseX
* mouseY
* pmouseX
* pmouseY

#### Keyboard
* key
* keyCode
* keyPressed()
* isKeyPressed
* keyReleased()
* keyTyped()

### Output
#### Text Area
* print()
* println()

### Transform
* rotate()
* translate()

### Color
#### Setting
* background()
* fill()
* noFill()
* noStroke()
* stroke()

### Math
#### Operators
* % (modulo)
* \* (multiply)
* *= (multiply assign)
* \+ (addition)
* ++ (increment)
* += (add assign)
* \- (minus)
* -- (decrement)
* -= (subtract assign)
* / (divide)
* /= (divide assign)

#### Bitwise Operators
* & (bitwise AND)
* << (left shift)
* \>> (right shift)
* | (bitwise OR)

#### Calculation
* abs()
* ceil()
* constrain()
* dist()
* exp()
* floor()
* lerp()
* log()
* mag()
* map()
* max()
* min()
* norm()
* pow()
* round()
* sq()
* sqrt()

#### Trigonometry
* acos()
* asin()
* atan()
* atan2()
* cos()
* degrees()
* radians()
* sin()
* tan()

#### Random
* random()
* randomGaussian()
* randomSeed()

### Constants 
* HALF_PI
* PI
* QUARTER_PI
* TAU
* TWO_PI

## License
GNU Lesser General Public License (LGPL) version 3
