# Author: Gary Huang <gh.nctu+code@gmail.com>

QT += testlib opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG -= debug_and_release debug_and_release_target
TARGET = TestPVector
processing_dir = ../..
LIBS += -L$${processing_dir}/lib -lProcessing
INCLUDEPATH += $${processing_dir}/include

# Input
SOURCES += testpvector.cpp

PRE_TARGETDEPS += $${processing_dir}/lib/libProcessing.a
QMAKE_EXTRA_TARGETS += processing

processing.target = $${processing_dir}/lib/libProcessing.a
processing.depends = FORCE
processing.commands = cd $${processing_dir}/src && qmake && make
