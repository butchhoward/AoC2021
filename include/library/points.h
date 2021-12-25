#ifndef POINTS_H_
#define POINTS_H_

#include <iostream>
#include <vector>

typedef struct Point {
    int x;
    int y;
} Point;
typedef std::vector<Point> Points;

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}
inline bool operator<(const Point& lhs, const Point& rhs)
{
    return lhs.x < rhs.x ||
            (lhs.x == rhs.x && lhs.y < rhs.y);
}

typedef struct Line {
    Point p1;
    Point p2;
} Line;
typedef std::vector<Line> Lines;

std::ostream & operator<<(std::ostream &os, const Point& point);
std::ostream & operator<<(std::ostream &os, const Points& points);
std::ostream & operator<<(std::ostream &os, const Line& line);
std::ostream & operator<<(std::ostream &os, const Lines& lines);

#endif
