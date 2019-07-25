/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_DEPENDEDGE_H
#define DU_DEPENDEDGE_H
#include "douml.h"
#include "labeledge.h"

namespace douml
{

class DU_API DependEdge : public LabelEdge 
{
public:
    DependEdge();
};

}
#endif
