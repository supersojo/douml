/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "diamondarrowhead.h"
#include "point.h"
#include "render.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace douml
{
DiamondArrowHead::~DiamondArrowHead()
{

}
void DiamondArrowHead::Draw(Render* r, Point& p,Point&q)
{
    du_float angle = CalculateAngle(q, p);

    du_float x = ARROW_LENGTH * cos(ARROW_ANGLE);
    du_float y = ARROW_LENGTH * sin(ARROW_ANGLE);

    Point p0((du_int)x, (du_int)y);
    Point p1(0, 0);//origin
    Point p2((du_int)x, (du_int)-y);
	Point p3((du_int)(2 * x), 0);

    Transform(p0,angle);
    Transform(p2,angle);
	Transform(p3, angle);


    r->SetColor(GetBorderColor());
    /*the border */
    r->MoveTo(q.GetX(),q.GetY());//origin
    r->LineTo(p0.GetX()+q.GetX(),p0.GetY()+q.GetY());
    r->LineTo(p3.GetX()+q.GetX(),p3.GetY()+q.GetY());
    r->LineTo(p2.GetX()+q.GetX(),p2.GetY()+q.GetY());
    r->LineTo(q.GetX(),q.GetY());

    r->Stroke();

    r->MoveTo(q.GetX(),q.GetY());//origin
    r->LineTo(p0.GetX()+q.GetX(),p0.GetY()+q.GetY());
    r->LineTo(p3.GetX()+q.GetX(),p3.GetY()+q.GetY());
    r->LineTo(p2.GetX()+q.GetX(),p2.GetY()+q.GetY());
    r->LineTo(q.GetX(),q.GetY());

    r->SetColor(GetFillColor());
    /*the internel */
    r->Fill();
}

}