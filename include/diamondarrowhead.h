/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_DIAMONDARROWHEAD_H
#define DU_DIAMONDARROWHEAD_H
#include "douml.h"
#include "arrowhead.h"

namespace douml
{
    class Render;
    class Point;
    
class DU_API DiamondArrowHead : public ArrowHead
{
public:
    virtual void Draw(Render* r,Point&p, Point& q);
    virtual ~DiamondArrowHead();
};

}
#endif
