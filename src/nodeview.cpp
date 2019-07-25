/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "nodeview.h"
#include "viewlayer.h"
#include "node.h"
#include "render.h"
#include "point.h"
#include "rect.h"
#include "edge.h"
#include "direction.h"
#include "graph.h"

namespace douml
{

NodeView::NodeView()
{
    m_background = nullptr;
    m_border = nullptr;
    m_content = nullptr;
}
NodeView::~NodeView()
{
    if (m_background != nullptr)
        delete m_background;
    if (m_border != nullptr)
        delete m_border;
    if (m_content != nullptr)
        delete m_content;
}
void NodeView::SetBackgroundLayer(ViewLayer *v)
{
    m_background = v;
}
void NodeView::SetBorderLayer(ViewLayer *v)
{
    m_border = v;
}
void NodeView::SetContentLayer(ViewLayer *v)
{
    m_content = v;
}
ViewLayer *NodeView::GetBackgroundLayer()
{
    return m_background;
}
ViewLayer *NodeView::GetBorderLayer()
{
    return m_border;
}
ViewLayer *NodeView::GetContentLayer()
{
    return m_content;
}
Rect NodeView::GetBounds()
{
    /*get max viewlayer's bounds */
    du_int w, h;
    Rect r1, r2, r3;
    if (m_background != nullptr)
        r1 = m_background->GetBounds();
    if (m_border != nullptr)
        r2 = m_border->GetBounds();
    if (m_content != nullptr)
        r3 = m_content->GetBounds();

    w = r1.GetW();
    w = r2.GetW() > w ? r2.GetW() : w;
    w = r3.GetW() > w ? r3.GetW() : w;

    h = r1.GetH();
    h = r2.GetH() > w ? r2.GetH() : h;
    h = r3.GetH() > w ? r3.GetH() : h;

    Rect r;
    r.SetW(w);
    r.SetH(h);

    return r;
}
void NodeView::Draw(Node *n)
{
    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    r->MoveTo(t.GetX(), t.GetY());

    if (m_background != nullptr)
        m_background->Draw(n);

    r->MoveTo(t.GetX(), t.GetY());

    if (m_border != nullptr)
        m_border->Draw(n);

    r->MoveTo(t.GetX(), t.GetY());

    if (m_content != nullptr)
        m_content->Draw(n);
}

void NodeView::CalcConnectionPointForEdges(Node *n, std::vector<Edge *> &edges, Direction d, Edge *e)
{
    du_int pos = 0;

    Rect r = GetBounds();
	
    if(!(n->GetGraph()->FindEdge(e)))
		edges.push_back(e);

	du_int s = edges.size();

    du_int delta_x = 0;
    du_int delta_y = 0;

    delta_x = r.GetW() / (s + 1);
    delta_y = r.GetH() / (s + 1);

    /*n->GetView()==this */
	/*sort edges by position */
	

    std::vector<Edge *>::iterator i;
    for (i = edges.begin(), pos = 0; i != edges.end(); i++, pos++)
    {
        if ((*i)->GetStartNode() == n)
        {
            if (d.Equals(Direction::NORTH))
            {
                (*i)->SetStartLocation(Point(delta_x * (pos + 1), 0));
            }
            if (d.Equals(Direction::SOUTH))
            {
                (*i)->SetStartLocation(Point(delta_x * (pos + 1), r.GetH()));
            }
            if (d.Equals(Direction::WEST))
            {
                (*i)->SetStartLocation(Point(0, delta_y * (pos + 1)));
            }
            if (d.Equals(Direction::EAST))
            {
                (*i)->SetStartLocation(Point(r.GetW(), delta_y * (pos + 1)));
            }
        }
        if ((*i)->GetEndNode() == n)
        {
            if (d.Equals(Direction::NORTH))
            {
                (*i)->SetEndLocation(Point(delta_x * (pos + 1), 0));
            }
            if (d.Equals(Direction::SOUTH))
            {
                (*i)->SetEndLocation(Point(delta_x * (pos + 1), r.GetH()));
            }
            if (d.Equals(Direction::WEST))
            {
                (*i)->SetEndLocation(Point(0, delta_y * (pos + 1)));
            }
            if (d.Equals(Direction::EAST))
            {
                (*i)->SetEndLocation(Point(r.GetW(), delta_y * (pos + 1)));
            }
        }
    }

}

} // namespace douml