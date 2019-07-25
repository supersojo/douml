/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_LABELEDGE_H
#define DU_LABELEDGE_H
#include "douml.h"
#include "edge.h"
namespace douml
{

class DU_API LabelEdge : public Edge 
{
public:
    LabelEdge();
    
    virtual void Draw();
    
    void SetStartLabel(du_char* l);
    du_char* GetStartLabel();

    void SetEndLabel(du_char* l);
    du_char* GetEndLabel();

private:
    du_char* m_startLabel;
    du_char* m_endLabel;
};

}
#endif
