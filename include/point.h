/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_POINT_H
#define DU_POINT_H

#include "douml.h"
#include <string>

namespace douml
{

class DU_API Point
{
public:
    Point(du_int x, du_int y);
    Point();
	Point(const Point& p);
    du_int GetX()const;
    du_int GetY()const;
    void SetX(du_int x);
    void SetY(du_int y);
    void Set(Point& p);
    Point& operator+(const Point& p);
    Point& operator-(const Point& p);
    Point& operator=(const Point& p);
    friend Point operator+(const Point& p1, const Point& p2);
    friend Point operator-(const Point& p1, const Point& p2);
    std::string ToString();

private:
    du_int m_x;
    du_int m_y;
};

} // namespace douml

#endif
