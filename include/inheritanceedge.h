/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_INHERITANCEEDGE_H
#define DU_INHERITANCEEDGE_H
#include "douml.h"
#include "labeledge.h"
namespace douml
{
    class ArrowHead;
class DU_API InheritanceEdge : public LabelEdge 
{
public:
    InheritanceEdge();
    ~InheritanceEdge();
    
private:
    ArrowHead* m_startArrowHead;
    ArrowHead* m_endArrowHead;
};

};
#endif
