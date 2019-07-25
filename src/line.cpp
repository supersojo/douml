/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "line.h"
#include "point.h"

namespace douml
{
Line::Line()
{
    m_start = new Point;
    m_end = new Point;
}
Point Line::GetStart()
{
    return *m_start;
}
Point Line::GetEnd()
{
    return *m_end;
}
void Line::SetStart(Point &p)
{
    m_start->Set(p);
}
void Line::SetEnd(Point &p)
{
    m_end->Set(p);
}
Line::~Line()
{
    delete m_start;
    delete m_end;
}
} // namespace douml