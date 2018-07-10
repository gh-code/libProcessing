/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef ARGS_H
#define ARGS_H

#include "macro.h"

PROCESSING_BEGIN_NAMESPACE

class Args
{
public:
    int length;
    char * operator[](int i) const { return argv[i]; }

private:
    friend class Processing;
    char **argv;
};

PROCESSING_END_NAMESPACE

#endif // ARGS_H
