TEMPLATE = lib
TARGET = Processing

DESTDIR = ../lib
#CONFIG += staticlib
#CONFIG += debug
CONFIG -= debug_and_release debug_and_release_target

INCLUDEPATH += Args Macro PString Exception Processing Mouse GuiEngine QtEngine

include(Args/args.pri)
include(Macro/Macro.pri)
include(Processing/processing.pri)
include(Mouse/mouse.pri)
include(PVector/pvector.pri)
include(GuiEngine/guiengine.pri)
include(QtEngine/qtengine.pri)

POST_TARGETDEPS += copy_headers
QMAKE_EXTRA_TARGETS += copy_headers clean distclean extraclean

copy_headers.depends = FORCE
win32: copy_headers.commands = \
    copy Args\\args.h ..\\include & \
    copy Macro\\macro.h ..\\include & \
    copy PString\\pstring.h ..\\include & \
    copy PVector\\pvector.h ..\\include & \
    copy Processing\\processing.h ..\\include & \
    copy Mouse\\mouse.h ..\\include
unix: copy_headers.commands = \
    cp Args/args.h ../include; \
    cp Macro/macro.h ../include; \
    cp PString/pstring.h ../include; \
    cp PVector/pvector.h ../include; \
    cp Processing/processing.h ../include; \
    cp Mouse/mouse.h ../include

clean.depends = extraclean
distclean.depends = extraclean
win32: extraclean.commands = del /q /f ..\\include\\*.h
unix: extraclean.commands = rm -f ../include/*.h
