/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "bentstyle.h"
#include "point.h"
#define _USE_MATH_DEFINES //??
#include <math.h>

namespace douml
{

 BentStyle BentStyle::STRAIGHT("straight");
 BentStyle BentStyle::FREE("free");
 BentStyle BentStyle::HV("hv");
 BentStyle BentStyle::VH("vh");
 BentStyle BentStyle::VHV("vhv");
 BentStyle BentStyle::HVH("hvh");

BentStyle::BentStyle()
{
	m_name = nullptr;
}
BentStyle::BentStyle(du_char* n)
{
	m_name = n;
}
BentStyle* BentStyle::Clone() 
{
	BentStyle* bent = new BentStyle;
	bent->SetName(GetName());
	
	return bent;
}

du_char* BentStyle::GetName()
{
	return m_name;
}
void BentStyle::SetName(du_char* n)
{
	m_name = n;
}
void BentStyle::GetStraightPath(std::vector<Point> &path, Point &s, Point &e)
{
    path.push_back(s);
    path.push_back(e);
}

void BentStyle::GetFreePath(std::vector<Point> &path, std::vector<Point> &src)
{
    std::vector<Point>::iterator i;
    for (i = src.begin(); i != src.end(); i++)
        path.push_back(*i);
}

void BentStyle::GetHVPath(std::vector<Point> &path, Point &s, Point &e)
{
    /*
	---+
	   |
	*/

    du_int x1 = s.GetX();
	du_int y1 = s.GetY();

    du_int x2 = e.GetX();
    du_int y2 = e.GetY();

    // x direction
	if(abs(x1-x2)<MIN_SEGMENT)
        return;

    // y direction
    if(abs(y1-y2)<MIN_SEGMENT)
        return;

    path.push_back(Point(x1, y1));
    path.push_back(Point(x2, y1));
    path.push_back(Point(x2, y2));
}
void BentStyle::GetVHPath(std::vector<Point> &path, Point &s, Point &e)
{
    /*
    |
    +---
	*/
	du_int x1 = s.GetX();
	du_int y1 = s.GetY();

	du_int x2 = e.GetX();
	du_int y2 = e.GetY();

	// x direction
	if (abs(x1 - x2)<MIN_SEGMENT)
		return;

	// y direction
	if (abs(y1 - y2)<MIN_SEGMENT)
		return;


    path.push_back(Point(x1, y1));
    path.push_back(Point(x1, y2));
    path.push_back(Point(x2, y2));
}
void BentStyle::GetHVHPath(std::vector<Point> &path, Point &s, Point &e)
{
    /*
	 ---+
		|
		+----
	*/
	du_int x1 = s.GetX();
	du_int y1 = s.GetY();

	du_int x2 = e.GetX();
	du_int y2 = e.GetY();

	// x direction
	if (abs(x1 - x2)<2*MIN_SEGMENT)
		return;

	if (abs(y1 - y2) <= MIN_SEGMENT)
		return;

    path.push_back(Point(x1, y1));
    path.push_back(Point((x1 + x2) / 2, y1));
    path.push_back(Point((x1 + x2) / 2, y2));
    path.push_back(Point(x2, y2));
    
}
void BentStyle::GetVHVPath(std::vector<Point> &path, Point &s, Point &e)
{
    /*
    |
    +---+
        |
	*/
	du_int x1 = s.GetX();
	du_int y1 = s.GetY();

	du_int x2 = e.GetX();
	du_int y2 = e.GetY();

	// x direction
	if (abs(x1 - x2)< MIN_SEGMENT)
		return;

	if (abs(y1 - y2) <= 2*MIN_SEGMENT)
		return;
    
    path.push_back(Point(x1, y1));
    path.push_back(Point(x1, (y1 + y2) / 2));
    path.push_back(Point(x2, (y1 + y2) / 2));
	path.push_back(Point(x2, y2));

}

} // namespace douml