/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "dependedge.h"
#include "arrowhead.h"
#include "linestyle.h"

namespace douml
{

DependEdge::DependEdge()
{
    SetLineStyle(&LineStyle::DOTTEDLINE);
    SetStartArrowHead(nullptr);
    SetEndArrowHead(new ArrowHead);
}


}