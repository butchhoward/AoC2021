#include "library/points.h"

#include <iostream>
#include <sstream>

// more to come later

std::ostream & operator<<(std::ostream &os, const Point& point)
{
    os << "("
       << point.x
       << ","
       << point.y
       << ")"
       ;
    return os;
}

std::ostream & operator<<(std::ostream &os, const Line& line)
{
    os << line.p1
       << " -> "
       << line.p2
       ;

    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const Lines& lines)
{
    for (auto line : lines)
    {
        os << line << std::endl;
    }
    return os;
}
