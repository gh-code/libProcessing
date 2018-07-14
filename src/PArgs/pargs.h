/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PARGS_H
#define PARGS_H

#include "pglobal.h"

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

#endif // PARGS_H
