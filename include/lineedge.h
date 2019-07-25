/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_LINEEDGE_H
#define DU_LINEEDGE_H
#include "douml.h"
#include "edge.h"

namespace douml
{
class DU_API LineEdge : public Edge 
{
public:
    virtual void Draw();
private:
};

#endif
