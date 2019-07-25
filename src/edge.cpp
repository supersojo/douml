/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "edge.h"
#include "point.h"
#include "node.h"
#include "rect.h"
#include <vector>
#include "render.h"
#include "id.h"
#include "graph.h"
#include "direction.h"
#include "bentstyle.h"
#include "linestyle.h"
#include "arrowhead.h"
#include "color.h"

namespace douml
{
void EdgeVisitor::Visit(Edge *e)
{
}
Edge::Edge()
{
    m_id = new Id;
    m_startNode = nullptr;
    m_endNode = nullptr;
    m_startLocation = new Point;
    m_endLocation = new Point;

    m_transitionPoints = new std::vector<Point>;

    m_render = nullptr;
    m_graph = nullptr;
    m_bentStyle = nullptr;

    m_startArrowHead = nullptr;
    m_endArrowHead = nullptr;

    m_selected = false;
}
bool Edge::GetSelected()
{
    return m_selected;
}
void Edge::SetSelected(bool s)
{
    m_selected = s;
}
Node *Edge::GetStartNode()
{
    return m_startNode;
}
Node *Edge::GetEndNode()
{
    return m_endNode;
}
void Edge::SetStartNode(Node *n)
{
    m_startNode = n;
}
void Edge::SetEndNode(Node *n)
{
    m_endNode = n;
}
Point Edge::GetStartLocation()
{
    return *m_startLocation;
}
Point Edge::GetEndLocation()
{
    return *m_endLocation;
}
void Edge::SetStartLocation(Point &p)
{
    m_startLocation->Set(p);
}
void Edge::SetEndLocation(Point &p)
{
    m_endLocation->Set(p);
}
Point Edge::GetStartLocationOnGraph()
{
    Point t = m_startNode->GetLocationOnGraph();
    t = t + (*m_startLocation);
    return t;
}
Point Edge::GetEndLocationOnGraph()
{
    Point t = m_endNode->GetLocationOnGraph();
    t = t + (*m_endLocation);
    return t;
}
void Edge::SetTransitionPoints(Point *ps, du_int n)
{
    delete m_transitionPoints;
    m_transitionPoints = new std::vector<Point>;

    du_int i = 0;
    for (; i < n; i++)
        m_transitionPoints->push_back(*(ps + i));
}
Point Edge::GetTransitionPoint(du_int i)
{
    if (i >= (du_int)(m_transitionPoints->size()))
        return Point();
    return m_transitionPoints->at(i);
}
Rect Edge::GetBounds()
{
    Rect r;
    du_int x0, y0, x1, y1;
    Point s = GetStartLocationOnGraph();
    Point e = GetEndLocationOnGraph();

    x0 = (s.GetX() < e.GetX()) ? s.GetX() : e.GetX();
    y0 = (s.GetY() < e.GetY()) ? s.GetY() : e.GetY();

    x1 = (s.GetX() > e.GetX()) ? s.GetX() : e.GetX();
    y1 = (s.GetY() > e.GetY()) ? s.GetY() : e.GetY();

    r.SetX(x0);
    r.SetY(y0);
    r.SetW(x1 - x0);
    r.SetH(y1 - y0);

    return r;
}
bool Edge::Contains(Point& p)
{   
    Point s = GetStartLocationOnGraph();
    Point e = GetEndLocationOnGraph();
    if(strcmp(m_bentStyle->GetName(),BentStyle::STRAIGHT.GetName())==0)
    {
    }
    return false;
}
void Edge::GetConnectionPoints(Point &p0, Point &p1)
{

    Point start = m_startNode->GetLocationOnGraph();
    Point end = m_endNode->GetLocationOnGraph();

    Point relativeStart = m_startNode->GetConnectionPoint(this);
    Point relativeEnd = m_endNode->GetConnectionPoint(this);

    p0 = start + relativeStart;
    p1 = end + relativeEnd;

    // grid align?
}

Render *Edge::GetRender()
{
    return m_render;
}
void Edge::SetRender(Render *r)
{
    m_render = r;
}
Graph* Edge::GetGraph()
{
    return m_graph;
}
void Edge::SetGraph(Graph* g)
{
    m_graph = g;
}
ArrowHead* Edge::GetStartArrowHead()
{
    return m_startArrowHead;
}
void Edge::SetStartArrowHead(ArrowHead* ah)
{
    m_startArrowHead = ah;
}

ArrowHead* Edge::GetEndArrowHead()
{
    return m_endArrowHead;
}
void Edge::SetEndArrowHead(ArrowHead* ah)
{
    m_endArrowHead = ah;
}

/*direction from node n */
Direction Edge::GetDirection(Node* n)
{
    /*assert n==startnode or endnode */
    Point s = GetStartNode()->GetCenterLocationOnGraph();
    Point e = GetEndNode()->GetCenterLocationOnGraph();

    Direction d;
    if(GetStartNode()==n)
    {
        d.Set(s,e);
    }
    else
    {
        d.Set(e,s);
    }
    
	return d;
}
void Edge::Draw()
{
    BentStyle* bent = GetBentStyle();
    Render* r = GetRender();
    std::vector<Point> path;
    if(bent==nullptr)
    {
        bent = GetDefaultBentStyle();
		/*m_bentStyle only be set by user not program self*/
        //m_bentStyle = bent->Clone();
    }
    if(strcmp(bent->GetName(),BentStyle::STRAIGHT.GetName())==0)
        bent->GetStraightPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());
    if(strcmp(bent->GetName(),BentStyle::FREE.GetName())==0)
        bent->GetFreePath(path,path);
    if(strcmp(bent->GetName(),BentStyle::HV.GetName())==0)
        bent->GetHVPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());
    if(strcmp(bent->GetName(),BentStyle::VH.GetName())==0)
        bent->GetVHPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());
    if(strcmp(bent->GetName(),BentStyle::HVH.GetName())==0)
        bent->GetHVHPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());
    if(strcmp(bent->GetName(),BentStyle::VHV.GetName())==0)
        bent->GetVHVPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());

    if(path.size()==0)
        bent->GetStraightPath(path,GetStartLocationOnGraph(),GetEndLocationOnGraph());
    
    /*assert size!=0 */
    du_int lines = path.size() - 1;

    /*line style */
    if(GetLineStyle()==&LineStyle::DOTTEDLINE)
    {
        r->SetDash(true);
    }
    if(GetLineStyle()==&LineStyle::SOLIDLINE)
    {
        r->SetDash(false);
    }

    r->SetColor(Color(0,0,0));
    /*draw lines */
    r->MoveTo(path.at(0).GetX(),path.at(0).GetY());
    
    for(du_int i=0;i<lines;i++)
    {
        r->LineTo(path.at(i+1).GetX(),path.at(i+1).GetY());
    }
    
    r->Stroke();


    r->SetDash(false);

    /*draw arrowheads */

    if(m_startArrowHead)
    {
        Point p = path.at(0);
        Point q = path.at(1);
        m_startArrowHead->Draw(r,q,p);
    }
    if(m_endArrowHead)
    {
        Point p = path.at(path.size()-2);
        Point q = path.at(path.size()-1);
        m_endArrowHead->Draw(r,p,q);
    }
    /*selected rect */
    if(m_selected)
    {
        r->SetColor(Color(179,102,179));
        du_int x;
        du_int y;
        /*start */
        x = path.at(0).GetX();
        y = path.at(0).GetY();
        r->MoveTo(x - 2, y - 2);
        r->LineTo(x + 2, y - 2);
        r->LineTo(x + 2, y + 2);
        r->LineTo(x - 2, y + 2);
        r->LineTo(x - 2, y - 2);
        r->Fill();
        /*end */
        x = path.at(path.size()-1).GetX();
        y = path.at(path.size()-1).GetY();
        r->MoveTo(x - 2, y - 2);
        r->LineTo(x + 2, y - 2);
        r->LineTo(x + 2, y + 2);
        r->LineTo(x - 2, y + 2);
        r->LineTo(x - 2, y - 2);
        r->Fill();

    }
}
BentStyle* Edge::GetDefaultBentStyle()
{
    std::vector<Point> path;
    Point s = GetStartLocationOnGraph();
	Point e = GetEndLocationOnGraph();
    Direction d = GetDirection(GetStartNode());
    Direction nearestCardinalDirection = d.GetNearestCardinalDirection();

    if(nearestCardinalDirection.Equals(Direction::NORTH)||nearestCardinalDirection.Equals(Direction::SOUTH))
    {
        /*VHV */
        BentStyle::VHV.GetVHVPath(path,s,e);
        if(path.size()!=0)
            return &BentStyle::VHV;

        BentStyle::VH.GetVHPath(path,s,e);
		if (path.size() != 0)
            return &BentStyle::VH;

        return &BentStyle::STRAIGHT;
        
    }
    if(nearestCardinalDirection.Equals(Direction::WEST)||nearestCardinalDirection.Equals(Direction::EAST))
    {
        /*VHV */
        BentStyle::HVH.GetHVHPath(path,s,e);
        if(path.size()!=0)
            return &BentStyle::HVH;

        BentStyle::HV.GetHVPath(path,s,e);
		if (path.size() != 0)
            return &BentStyle::HV;
        return &BentStyle::STRAIGHT;
    }

    return &BentStyle::STRAIGHT;
}
BentStyle* Edge::GetBentStyle()
{
    return m_bentStyle;


}
void Edge::SetBentStyle(BentStyle* bent)
{
	if (m_bentStyle) {
		delete m_bentStyle;
		m_bentStyle = nullptr;
	}
    m_bentStyle = bent;
}
void Edge::SetLineStyle(LineStyle* ls)
{
    m_lineStyle = ls;
}
LineStyle* Edge::GetLineStyle()
{
    return m_lineStyle;
}
Edge::~Edge()
{
    delete m_id;

    delete m_startLocation;
    delete m_endLocation;

    delete m_transitionPoints;

    if(m_bentStyle)
        delete m_bentStyle;

    if(m_startArrowHead)
        delete m_startArrowHead;

    if(m_endArrowHead)
        delete m_endArrowHead;
}

} // namespace douml