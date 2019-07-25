/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "rect.h"

namespace douml
{

Rect::Rect()
{
    m_x = m_y = m_w = m_h = 0;
}
du_int Rect::GetX()
{
    return m_x;
}
du_int Rect::GetY()
{
    return m_y;
}
du_int Rect::GetW()
{
    return m_w;
}
du_int Rect::GetH()
{
    return m_h;
}
void Rect::SetX(du_int x)
{
    m_x = x;
}
void Rect::SetY(du_int y)
{
    m_y = y;
}
void Rect::SetW(du_int w)
{
    m_w = w;
}
void Rect::SetH(du_int h)
{
    m_h = h;
}
Rect& Rect::operator=( Rect& r)
{
    m_x = r.GetX();
    m_y = r.GetY();
    m_w = r.GetW();
    m_h = r.GetH();
    return *this;
}

}