/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "node.h"
#include "point.h"
#include "id.h"
#include "color.h"
#include "nodeview.h"
#include "viewlayer.h"
#include "render.h"
#include "rect.h"
#include "graph.h"
#include "edge.h"
#include "direction.h"

namespace douml
{

void NodeVisitor::Visit(Node *n)
{
}

Node::Node()
{
    m_parent = nullptr;
    m_location = new Point;
    m_id = new Id;
    m_children = new std::vector<Node *>;

    m_backgroundColor = new Color;
    m_borderColor = new Color;
    m_textColor = new Color;

    m_view = new NodeView;
    m_render = nullptr;

    m_selected = false;
}
Node::Node(NodeView* nv)
{
    m_parent = nullptr;
    m_location = new Point;
    m_id = new Id;
    m_children = new std::vector<Node *>;

    m_backgroundColor = new Color;
    m_borderColor = new Color;
    m_textColor = new Color;

    /*assert nv!= null */
    m_view = nv;
    m_render = nullptr;

    m_selected = false;
}
Node *Node::GetParent()
{
    return m_parent;
}
Rect Node::GetBounds()
{
    Point t = GetLocationOnGraph();

    Rect r = m_view->GetBounds();

    r.SetX(t.GetX());
    r.SetY(t.GetY());

    return r;
}
void Node::SetParent(Node *n)
{
    m_parent = n;
}
Point Node::GetCenterLocationOnGraph()
{
    Point t;
    Rect r = GetBounds();
    t.SetX(r.GetX() + r.GetW() / 2);
    t.SetY(r.GetY() + r.GetH() / 2);
    return t;
}
Point Node::GetLocation()
{
    return *m_location;
}
Point Node::GetLocationOnGraph()
{
    Point t = *m_location;
    if (m_parent != nullptr)
    {
        t = t + m_parent->GetLocationOnGraph();
    }
    return t;
}
void Node::SetLocation(Point &p)
{
    *m_location = p;
}
void Node::AddChildNode(Node *n)
{
    n->SetGraph(GetGraph());
    m_children->push_back(n);
}
void Node::RemoveChildNode(Node *n)
{
    std::vector<Node *>::iterator i;
    for (i = m_children->begin(); i != m_children->end(); i++)
    {
        if ((*i) == n)
        {
            m_children->erase(i);
            break;
        }
        else
        {
            (*i)->RemoveChildNode(n);
        }
    }
}
bool Node::HasParent() const
{
    return m_parent != nullptr;
}
bool Node::HasChildrenNode() const
{
    return !m_children->empty();
}
void Node::VisitChildren(NodeVisitor *v)
{
    std::vector<Node *>::iterator i;
    for (i = m_children->begin(); i != m_children->end(); i++)
    {
        v->Visit(*i);
    }
}
Color &Node::GetBackgroundColor()
{
    return *m_backgroundColor;
}
Color &Node::GetBorderColor()
{
    return *m_borderColor;
}
Color &Node::GetTextColor()
{
    return *m_textColor;
}
void Node::SetBackgroundColor(Color &c)
{
    m_backgroundColor->Set(c);
}
void Node::SetBorderColor(Color &c)
{
    m_borderColor->Set(c);
}
void Node::SetTextColor(Color &c)
{
    m_textColor->Set(c);
}
void Node::ClearChildNodes()
{
    std::vector<Node *>::iterator i;
    for (i = m_children->begin(); i != m_children->end(); i++)
    {
        delete (*i);
    }
}
void Node::SetViewLayers(ViewLayer *background, ViewLayer *border, ViewLayer *content)
{
    /*link them together */
    background->SetChild(*border);

    border->SetParent(*background);
    border->SetChild(*content);

    content->SetParent(*border);

    /*set */
    m_view->SetBackgroundLayer(background);
    m_view->SetBorderLayer(border);
    m_view->SetContentLayer(content);
}
class AllEdgeVisitor : public EdgeVisitor
{
public:
    AllEdgeVisitor();
    AllEdgeVisitor(Node *n, std::vector<Edge *> &edges);
    virtual void Visit(Edge *e);

private:
    Node *m_node;
    std::vector<Edge *> *m_edges;
};
AllEdgeVisitor::AllEdgeVisitor()
{
    m_node = nullptr;
    m_edges = nullptr;
}
AllEdgeVisitor::AllEdgeVisitor(Node *n, std::vector<Edge *> &edges)
{
    m_node = n;
    m_edges = &edges;
}
void AllEdgeVisitor::Visit(Edge *e)
{
    if (e->GetStartNode() == e->GetEndNode())
        return;

    if (e->GetStartNode() == m_node)
        m_edges->push_back(e);

    if (e->GetEndNode() == m_node)
        m_edges->push_back(e);
}
void Node::GetConnectedEdges(std::vector<Edge *> &edges)
{
    edges.clear();
    AllEdgeVisitor v(this, edges);
    GetGraph()->VisitEdges(&v);
}

void Node::GetEdgesOnSameSide(std::vector<Edge *> &edges, Edge *e)
{
    std::vector<Edge *> connectedEdges;
    Direction d = e->GetDirection(e->GetStartNode());
    Direction d1 = e->GetDirection(e->GetEndNode());

    Direction cardinalDirectionToSearch = d.GetNearestCardinalDirection();   /*from the node */
    Direction cardinalDirectionToSearch1 = d1.GetNearestCardinalDirection(); /*to the node */

    /*assert |x|=|x| |y|=|y| */
    GetConnectedEdges(connectedEdges);

    std::vector<Edge *>::iterator i;
    for (i = connectedEdges.begin(); i != connectedEdges.end(); i++)
    {
        if (e->GetStartNode() == this)
        {
            if ((*i)->GetStartNode() == this)
            {
                Direction edgeDirection = (*i)->GetDirection((*i)->GetStartNode());
                Direction nearestCardinalDirection = edgeDirection.GetNearestCardinalDirection();
                if ((cardinalDirectionToSearch.GetX() == nearestCardinalDirection.GetX()) &&
                    (cardinalDirectionToSearch.GetY() == nearestCardinalDirection.GetY()))
                {
                    edges.push_back((*i));
                }
            }
            if ((*i)->GetEndNode() == this)
            {
                Direction edgeDirection1 = (*i)->GetDirection((*i)->GetStartNode());
                Direction nearestCardinalDirection1 = edgeDirection1.GetNearestCardinalDirection();

                if ((cardinalDirectionToSearch1.GetX() == nearestCardinalDirection1.GetX()) &&
                    (cardinalDirectionToSearch1.GetY() == nearestCardinalDirection1.GetY()))
                {
                    edges.push_back((*i));
                }
            }
        }
        if (e->GetEndNode() == this)
        {
            if ((*i)->GetEndNode() == this)
            {
                Direction edgeDirection = (*i)->GetDirection((*i)->GetStartNode());
                Direction nearestCardinalDirection = edgeDirection.GetNearestCardinalDirection();
                if ((cardinalDirectionToSearch.GetX() == nearestCardinalDirection.GetX()) &&
                    (cardinalDirectionToSearch.GetY() == nearestCardinalDirection.GetY()))
                {
                    edges.push_back((*i));
                }
            }
            if ((*i)->GetStartNode() == this)
            {
                Direction edgeDirection1 = (*i)->GetDirection((*i)->GetStartNode());
                Direction nearestCardinalDirection1 = edgeDirection1.GetNearestCardinalDirection();

                if ((cardinalDirectionToSearch1.GetX() == nearestCardinalDirection1.GetX()) &&
                    (cardinalDirectionToSearch1.GetY() == nearestCardinalDirection1.GetY()))
                {
                    edges.push_back((*i));
                }
            }
        }
    }
}
/*
Edge * e = new Edge;
e->SetStart();
e->SetEnd();
start->GetConnectionPoint(e)
end->GetConnectionPoint(e)
graph->Connet(s,start,e,end,nullptr,0)
 */
Point Node::GetConnectionPoint(Edge *e)
{
    du_int size;
    std::vector<Edge *> edges;
    GetEdgesOnSameSide(edges, e);

    size = edges.size();

    Direction edgeDirection = e->GetDirection(this);

    Direction nearestCardinalDirection = edgeDirection.GetNearestCardinalDirection();

    GetView()->CalcConnectionPointForEdges(this, edges, nearestCardinalDirection, e);

    if (e->GetStartNode() == this)
        return e->GetStartLocation();
    if (e->GetEndNode() == this)
        return e->GetEndLocation();
    return Point();
}
void Node::SetRender(Render *r)
{
    m_render = r;
}
Render *Node::GetRender()
{
    return m_render;
}
bool Node::GetSelected()
{
    return m_selected;
}
void Node::SetSelected(bool s)
{
    m_selected = s;
}
Graph *Node::GetGraph()
{
    return m_graph;
}
void Node::SetGraph(Graph *g)
{
    m_graph = g;
}
NodeView *Node::GetView()
{
    return m_view;
}
/*----------------------------------------- */
class DrawChildNode : public NodeVisitor
{
public:
    DrawChildNode();
    DrawChildNode(Render *r);
    virtual void Visit(Node *n);

private:
    Render *m_render;
};
void DrawChildNode::Visit(Node *n)
{
    /*assert m_render */
    n->SetRender(m_render);
    n->Draw();
}
DrawChildNode::DrawChildNode()
{
    m_render = nullptr;
}
DrawChildNode::DrawChildNode(Render *r)
{
    m_render = r;
}
/*---------------------------------------- */
void Node::NotifyCallback()
{
}
void Node::Draw()
{
    /*before draw first call notify if model has changed */
    NotifyCallback();

    if (m_view != nullptr)
        m_view->Draw(this);
    if (HasChildrenNode())
    {
        DrawChildNode d(GetRender());
        VisitChildren(&d);
    }
}
Node::~Node()
{
    delete m_location;
    delete m_id;

    ClearChildNodes();
    delete m_children;

    delete m_backgroundColor;
    delete m_borderColor;
    delete m_textColor;

    delete m_view;
}

} // namespace douml