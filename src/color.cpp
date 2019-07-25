/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "color.h"

namespace douml
{

Color::Color()
{
    m_r = m_g = m_b = 0;
}
Color::Color(du_int r, du_int g, du_int b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}
du_int Color::GetR()
{
    return m_r;
}
du_int Color::GetG()
{
    return m_g;
}
du_int Color::GetB()
{
    return m_b;
}
void Color::SetR(du_int r)
{
    m_r = r;
}
void Color::SetG(du_int g)
{
    m_r = g;
}
void Color::SetB(du_int b)
{
    m_b = b;
}
void Color::Set(Color &c)
{
    m_r = c.GetR();
    m_g = c.GetG();
    m_b = c.GetB();
}
std::string Color::ToString()
{
    char buf[64] = {0};
    _snprintf_s(buf, sizeof(buf), "(%d,%d,%d)", m_r, m_g, m_b);
    return std::string(buf);
}
} // namespace douml