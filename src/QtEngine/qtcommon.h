/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTCOMMON_H
#define P_QTCOMMON_H

#include <QtGlobal>
#if QT_VERSION >= 0x050400
#include <QOpenGLWidget>
#define QOPENGLWIDGET QOpenGLWidget
#else
#include <QtOpenGL/QGLWidget>
#define QOPENGLWIDGET QGLWidget
#endif

#endif // P_QTCOMMON_H
