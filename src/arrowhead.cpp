/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "arrowhead.h"
#include "color.h"
#include "point.h"
#include "render.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace douml
{

du_float ArrowHead::ARROW_ANGLE = M_PI / 6;
du_float ArrowHead::ARROW_LENGTH = 10;

ArrowHead::ArrowHead()
{
    m_border = new Color;
    m_fill = new Color;
    m_arrowLength = ARROW_LENGTH;
}
du_int ArrowHead::GetArroweLength()
{
    return m_arrowLength;
}
void ArrowHead::SetArrowLength(du_int l)
{
    m_arrowLength = l;
}
ArrowHead::~ArrowHead()
{
    delete m_border;
    delete m_fill;
}
void ArrowHead::Draw(Render *r, Point &p, Point &q)
{
    du_float angle = CalculateAngle(q, p);

    du_float x = GetArroweLength() * cos(ARROW_ANGLE);
    du_float y = GetArroweLength() * sin(ARROW_ANGLE);

    Point p0((du_int)x, (du_int)y);
    Point p1(0, 0);
    Point p2((du_int)x, (du_int)-y);

    Transform(p0,angle);
    Transform(p2,angle);


    r->MoveTo(q.GetX(),q.GetY());
    r->LineTo(p0.GetX()+q.GetX(),p0.GetY()+q.GetY());

    r->MoveTo(q.GetX(),q.GetY());
    r->LineTo(p2.GetX()+q.GetX(),p2.GetY()+q.GetY());

    r->Stroke();
}
void ArrowHead::SetBorderColor(Color &c)
{
    m_border->Set(c);
}
void ArrowHead::SetFillColor(Color &c)
{
    m_fill->Set(c);
}
Color &ArrowHead::GetBorderColor()
{
    return *m_border;
}
Color &ArrowHead::GetFillColor()
{
    return *m_fill;
}
du_float ArrowHead::CalculateAngle(Point &p, Point &q)
{
    return atan2((du_float)(q.GetY() - p.GetY()), (du_float)(q.GetX() - p.GetX()));
}
void ArrowHead::Transform(Point &p, du_float angle)
{

        du_float x0 = p.GetX();
        du_float y0 = p.GetY();
        du_float x1 = x0 * cos(angle) - y0 * sin(angle);
        du_float y1 = x0 * sin(angle) + y0 * cos(angle);
        p.SetX((du_int)round(x1)); // 防止转换丢失精度 使用round
        p.SetY((du_int)round(y1)); //


}
} // namespace douml