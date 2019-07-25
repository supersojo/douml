/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "associateedge.h"
#include "arrowhead.h"
#include "linestyle.h"

namespace douml
{

AssociateEdge::AssociateEdge()
{
    SetLineStyle(&LineStyle::SOLIDLINE);
    SetStartArrowHead(nullptr);
    SetEndArrowHead(new ArrowHead);
}


}