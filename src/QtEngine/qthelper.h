/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef P_QTHELPER_H
#define P_QTHELPER_H

#include "pglobal.h"

class QPainter;
class QPaintEvent;

PROCESSING_BEGIN_NAMESPACE

class QtHelper
{
public:
    QtHelper() {}
    virtual ~QtHelper() {}
    virtual void paint(QPainter *painter, QPaintEvent *event) = 0;
};

PROCESSING_END_NAMESPACE

#endif // P_QTHELPER_H
