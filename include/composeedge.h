/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_COMPOSEEDGE_H
#define DU_COMPOSEEDGE_H
#include "douml.h"
#include "labeledge.h"

namespace douml
{

class DU_API ComposeEdge : public LabelEdge 
{
public:
    ComposeEdge();
};

}
#endif