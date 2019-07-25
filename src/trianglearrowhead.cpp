/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "trianglearrowhead.h"
#include "point.h"
#include "render.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace douml
{
TriangleArrowHead::~TriangleArrowHead()
{
    
}
void TriangleArrowHead::Draw(Render* r, Point& p,Point&q)
{
    du_float angle = CalculateAngle(q, p);

    du_float x = GetArroweLength() * cos(ARROW_ANGLE);
    du_float y = GetArroweLength() * sin(ARROW_ANGLE);

    Point p0((du_int)x, (du_int)y);
    Point p1(0, 0);
    Point p2((du_int)x, (du_int)-y);

    Transform(p0,angle);
    Transform(p2,angle);


    r->SetColor(GetBorderColor());
    /*the border */
    r->MoveTo(q.GetX(),q.GetY());
    r->LineTo(p0.GetX()+q.GetX(),p0.GetY()+q.GetY());
    r->LineTo(p2.GetX()+q.GetX(),p2.GetY()+q.GetY());
    r->LineTo(q.GetX(),q.GetY());

    r->Stroke();

    r->MoveTo(q.GetX(),q.GetY());
    r->LineTo(p0.GetX()+q.GetX(),p0.GetY()+q.GetY());
    r->LineTo(p2.GetX()+q.GetX(),p2.GetY()+q.GetY());
    r->LineTo(q.GetX(),q.GetY());

    r->SetColor(GetFillColor());
    /*the internel */
    r->Fill();
}

}