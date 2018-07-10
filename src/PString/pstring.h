/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#ifndef PSTRING_H
#define PSTRING_H

#include <string>
#include <sstream>

class String
{
public:
    template <class T>
    String(T d) { std::ostringstream ss; ss << d; data = ss.str(); }

private:
    std::string data;
};

#endif // PSTRING_H
