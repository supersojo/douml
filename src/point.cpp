/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "point.h"

namespace douml
{
Point::Point()
{
    m_x = 0;
    m_y = 0;
}
Point::Point(du_int x, du_int y)
{
    m_x = x;
    m_y = y;
}
Point::Point(const Point& p)
{
    m_x = p.GetX();
    m_y = p.GetY();
}
du_int Point::GetX()const
{
    return m_x;
}
du_int Point::GetY()const
{
    return m_y;
}
void Point::SetX(du_int x)
{
    m_x = x;
}
void Point::SetY(du_int y)
{
    m_y = y;
}
void Point::Set(Point &p)
{
    m_x = p.GetX();
    m_y = p.GetY();
}
Point& Point::operator+(const Point& p)
{
    
    m_x += p.GetX();
    m_y += p.GetY();
    return *this;
}
Point& Point::operator-(const Point& p)
{
    
    m_x -= p.GetX();
    m_y -= p.GetY();
    return *this;
}
Point& Point::operator=(const Point& p)
{
    m_x = p.GetX();
    m_y = p.GetY();
    return *this;
}
Point operator+(const Point& p1, const Point& p2)
{
    Point t;
    t.SetX(p1.GetX()+p2.GetX());
    t.SetX(p1.GetY()+p2.GetY());
    return t;
}
Point operator-(const Point& p1, const Point& p2)
{
    Point t;
    t.SetX(p1.GetX()-p2.GetX());
    t.SetX(p1.GetY()-p2.GetY());
    return t;
}
std::string Point::ToString()
{
    char buf[64] = {0};
    _snprintf_s(buf, sizeof(buf), "(%d,%d)", m_x, m_y);
    return std::string(buf);
}

} // namespace douml