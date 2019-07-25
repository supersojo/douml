/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "direction.h"
#include "point.h"
#define _USE_MATH_DEFINES //??
#include <math.h>

namespace douml
{

Direction Direction::NORTH(0, -1);
Direction Direction::SOUTH(0, 1);
Direction Direction::WEST(-1, 0);
Direction Direction::EAST(1, 0);

Direction::Direction()
{
    m_x = m_y = 0;
}
Direction::Direction(du_float x, du_float y)
{
    m_x = x;
    m_y = y;
}
Direction::Direction(Point &p, Point &q)
{
    du_int x = q.GetX() - p.GetX();
    du_int y = q.GetY() - p.GetY();

    du_float len = sqrt(x * x + y * y);

    m_x = (du_float)x / len;
    m_y = (du_float)y / len;
}
du_float Direction::GetX()
{
    return m_x;
}
du_float Direction::GetY()
{
    return m_y;
}
void Direction::SetX(du_float x)
{
    m_x = x;
}
void Direction::SetY(du_float y)
{
    m_y = y;
}
void Direction::Set(Point &p, Point &q)
{
    du_int x = q.GetX() - p.GetX();
    du_int y = q.GetY() - p.GetY();

    du_float len = sqrt(x * x + y * y);

    m_x = (du_float)x / len;
    m_y = (du_float)y / len;
}
Direction Direction::GetNearestCardinalDirection()
{
    du_int x, y;
    x = (du_int)round(GetX());
    y = (du_int)round(GetY());
    if ((abs(x) == 1) && (abs(y) == 1))
    {
        if (abs(GetX()) >= abs(GetY()))
            y = 0;
        if (abs(GetX()) < abs(GetY()))
            x = 0;
    }
    if (x == 0 && y == -1)
        return Direction::NORTH;
    if (x == 0 && y == 1)
        return Direction::SOUTH;
    if (x == 1 && y == 0)
        return Direction::EAST;
    if (x == -1 && y == 0)
        return Direction::WEST;
    /* should never happen */
    return *this;
}
bool Direction::Equals(Direction& d)
{
    bool x_ok = abs(m_x - d.GetX())<0.000001;
    bool y_ok = abs(m_y - d.GetY())<0.000001;
    return (x_ok && y_ok);
}
} // namespace douml