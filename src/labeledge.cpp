/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "labeledge.h"
#include "direction.h"
#include "render.h"
#include "point.h"
namespace douml
{

LabelEdge::LabelEdge()
{
    m_startLabel = nullptr;
    m_endLabel = nullptr;
}
du_char* LabelEdge::GetStartLabel()
{
    return m_startLabel;
}
void LabelEdge::SetStartLabel(du_char* l)
{
    m_startLabel = l;
}
du_char* LabelEdge::GetEndLabel()
{
    return m_endLabel;
}
void LabelEdge::SetEndLabel(du_char* l)
{
    m_endLabel = l;
}
void LabelEdge::Draw()
{
    du_int w0,h0,x_bearing,y_bearing;

    Edge::Draw();

    if(m_startLabel==nullptr && m_endLabel==nullptr)
        return;
    
    /*draw labels */
    Render* r = GetRender();
    Point s = GetStartLocationOnGraph();
	Point e = GetEndLocationOnGraph();
    if(m_startLabel!=nullptr) {
        Direction d = GetDirection(GetStartNode());
        Direction nearestCardinalDirection = d.GetNearestCardinalDirection();
        if(nearestCardinalDirection.Equals(Direction::NORTH))
        {
            r->TextBoxSize(m_startLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(s.GetX()+5,s.GetY()-h0+abs(y_bearing)-5);
            r->ShowText(m_startLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::SOUTH))
        {
            r->TextBoxSize(m_startLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(s.GetX()+5,s.GetY()+abs(y_bearing)+5);
            r->ShowText(m_startLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::WEST))
        {
            r->TextBoxSize(m_startLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(s.GetX()-5-w0,s.GetY()-h0+abs(y_bearing)-5);
            r->ShowText(m_startLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::EAST))
        {
            r->TextBoxSize(m_startLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(s.GetX()+5,s.GetY()+abs(y_bearing)+5);
            r->ShowText(m_startLabel);
        }
        /*should be reach here */
    }
    if(m_endLabel!=nullptr) {
        Direction d = GetDirection(GetEndNode());
        Direction nearestCardinalDirection = d.GetNearestCardinalDirection();
        if(nearestCardinalDirection.Equals(Direction::NORTH))
        {
            r->TextBoxSize(m_endLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(e.GetX()+5,e.GetY()-h0+abs(y_bearing)-5);
            r->ShowText(m_endLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::SOUTH))
        {
            r->TextBoxSize(m_endLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(e.GetX()+5,e.GetY()+abs(y_bearing)+5);
            r->ShowText(m_endLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::WEST))
        {
            r->TextBoxSize(m_endLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(e.GetX()-5-w0,e.GetY()-h0+abs(y_bearing)-5);
            r->ShowText(m_endLabel);
        }
        if(nearestCardinalDirection.Equals(Direction::EAST))
        {
            r->TextBoxSize(m_endLabel,w0,h0,x_bearing,y_bearing);
            r->MoveTo(e.GetX()+5,e.GetY()+abs(y_bearing)+5);
            r->ShowText(m_endLabel);
        }
        /*should be reach here */
    }
    
}

}