/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_DIRECTION_H
#define DU_DIRECTION_H
#include "douml.h"

namespace douml
{
    class Point;
class DU_API Direction
{
public:
    Direction();
    Direction(du_float x,du_float y);
    Direction(Point& p,Point& q);
    du_float GetX();
    du_float GetY();
    void SetX(du_float x);
    void SetY(du_float y);
    void Set(Point& p,Point& q);
    Direction GetNearestCardinalDirection();
    bool Equals(Direction& d);
    static Direction NORTH;
    static Direction SOUTH;
    static Direction WEST;
    static Direction EAST;
private:
    du_float m_x;
    du_float m_y;
};

}

#endif
