TEMPLATE = lib
TARGET = Processing

DESTDIR = ../lib
#CONFIG += staticlib
#CONFIG += debug
CONFIG -= debug_and_release debug_and_release_target

INCLUDEPATH += PArgs PGlobal PString Exception Processing Mouse GuiEngine QtEngine

include(PArgs/pargs.pri)
include(PGlobal/pglobal.pri)
include(Processing/processing.pri)
include(PVector/pvector.pri)
include(GuiEngine/guiengine.pri)
include(QtEngine/qtengine.pri)

POST_TARGETDEPS += copy_headers
QMAKE_EXTRA_TARGETS += copy_headers clean distclean extraclean

copy_headers.depends = FORCE
win32: copy_headers.commands = \
    copy PArgs\\pargs.h ..\\include & \
    copy PGlobal\\pglobal.h ..\\include & \
    copy PString\\pstring.h ..\\include & \
    copy PVector\\pvector.h ..\\include & \
    copy Processing\\processing.h ..\\include
unix: copy_headers.commands = \
    cp PArgs/pargs.h ../include; \
    cp PGlobal/pglobal.h ../include; \
    cp PString/pstring.h ../include; \
    cp PVector/pvector.h ../include; \
    cp Processing/processing.h ../include

clean.depends = extraclean
distclean.depends = extraclean
win32: extraclean.commands = del /q /f ..\\include\\*.h
unix: extraclean.commands = rm -f ../include/*.h
