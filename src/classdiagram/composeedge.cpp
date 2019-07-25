/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "composeedge.h"
#include "diamondarrowhead.h"
#include "linestyle.h"

namespace douml
{

ComposeEdge::ComposeEdge()
{
    SetLineStyle(&LineStyle::SOLIDLINE);
    SetStartArrowHead(nullptr);
    SetEndArrowHead(new DiamondArrowHead);
}


}