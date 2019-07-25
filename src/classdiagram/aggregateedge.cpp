/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "aggregateedge.h"
#include "diamondarrowhead.h"
#include "linestyle.h"
#include "color.h"

namespace douml
{

AggregateEdge::AggregateEdge()
{
    SetLineStyle(&LineStyle::SOLIDLINE);
    SetStartArrowHead(nullptr);
    SetEndArrowHead(new DiamondArrowHead);
    GetEndArrowHead()->SetBorderColor(Color(0,0,0));
    GetEndArrowHead()->SetFillColor(Color(255,255,255));
}


}