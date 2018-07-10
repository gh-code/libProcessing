/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTWINDOW_H
#define P_QTWINDOW_H

#include <QTimer>
#include <QWidget>
#include "window.h"
#include "macro.h"

class QHBoxLayout;

PROCESSING_BEGIN_NAMESPACE

class QtWindow : public Window, public QWidget
{
public:
    QtWindow();
    ~QtWindow();

    void setWindowTitle(const char *title) OVERRIDE { QWidget::setWindowTitle(title); }
    void setFixedSize(int width, int height) OVERRIDE { QWidget::setFixedSize(width, height); }
    bool hasParent() const { return true; } // which is QApplication
    bool hasOtherParent() const { return true; } // which is QApplication
    void show() OVERRIDE { QWidget::show(); }
    void start(int fps) OVERRIDE;
    Canvas * createCanvas(enum Renderer) OVERRIDE;
    Canvas * replaceCanvas(enum Renderer) OVERRIDE;

    void loop() { timer->start(); }
    void noLoop() { timer->stop(); }

private:
    QTimer *timer;
    QHBoxLayout *layout;
};

PROCESSING_END_NAMESPACE

#endif // P_QTWINDOW_H
