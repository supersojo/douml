/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "shape.h"
#include "node.h"
namespace douml
{

void Shape::DrawBackground(Node *n)
{
}
void Shape::DrawBorder(Node *n)
{
}
void Shape::SetWidth(du_int w)
{
    m_width = w;
}
void Shape::SetHeight(du_int h)
{
    m_height = h;
}
du_int Shape::GetWidth()
{
    return m_width;
}
du_int Shape::GetHeight()
{
    return m_height;
}
} // namespace douml