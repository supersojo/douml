/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "point.h"
#include "rect.h"
#include "toolitem.h"

namespace douml
{

Graph::Graph()
{
    m_nodes = new std::vector<Node *>;
    m_edges = new std::vector<Edge *>;
    m_needUpdateEdges = false;
    m_toolItems = new std::vector<ToolItem*>;
}
void Graph::VisitNodes(NodeVisitor *v)
{
    std::vector<Node *>::iterator i;
    for (i = m_nodes->begin(); i != m_nodes->end(); i++)
        v->Visit(*i);
}
void Graph::VisitEdges(EdgeVisitor *v)
{
    std::vector<Edge *>::iterator i;
    for (i = m_edges->begin(); i != m_edges->end(); i++)
        v->Visit(*i);
}
bool Graph::AddNode(Node *n, Point *p)
{
    Node *potentialParent = FindNode(*p);
    if (potentialParent != nullptr)
    {
        /*only when parent node can contains entire child node */
        Rect rectParent = potentialParent->GetBounds();
        Rect rectChild = n->GetBounds();

        bool x_ok = (rectChild.GetX()>rectParent.GetX()) && ((rectChild.GetX()+rectChild.GetW())<rectParent.GetX()+rectParent.GetW());
        bool y_ok = (rectChild.GetY()>rectParent.GetY()) && ((rectChild.GetY()+rectChild.GetH())<rectParent.GetY()+rectParent.GetH());

        if(x_ok && y_ok) {
            Point t = potentialParent->GetLocationOnGraph();
            t = (*p) - t;
            n->SetParent(potentialParent);
            n->SetLocation(t);
            potentialParent->AddChildNode(n);
        } else {
            /*update node position */
            n->SetLocation(*p);
            n->SetGraph(this);
            /*add to list */
            m_nodes->push_back(n);
        }
    }
    else
    {
        /*update node position */
        n->SetLocation(*p);
		n->SetGraph(this);
        /*add to list */
        m_nodes->push_back(n);
    }
    return true;
}
void Graph::CreateToolItems(std::vector<ToolItem*> &toolItems)
{

}
void Graph::GetToolItems(std::vector<ToolItem*>& tools)
{
    tools.clear();
    if(m_toolItems->size()==0)
    {
        /*first create tool items */
        CreateToolItems(*m_toolItems);
    }
    std::vector<ToolItem*>::iterator i;
    for(i=m_toolItems->begin();i!=m_toolItems->end();i++)
        tools.push_back(*i);
}
ToolItem* Graph::GetActiveToolItem()
{
    if(m_toolItems->size()==0)
        return nullptr;

    std::vector<ToolItem*>::iterator i;
    for(i=m_toolItems->begin();i!=m_toolItems->end();i++)
    {
        if ((*i)->GetSelected())
            return (*i);
    }
    return nullptr;
}
bool Graph::Connect(Edge* edge,
                Node* start,Point& startLocation,
                Node* end,Point& endLocation,
                Point* ps,du_int n)
{
    /*assert start and end in m_nodes */
    edge->SetStartNode(start);
    edge->SetStartLocation(startLocation);
    edge->SetEndNode(end);
    edge->SetEndLocation(endLocation);
    edge->SetTransitionPoints(ps,n);

    m_edges->push_back(edge);
	return true;
}
class RemoveNodeVisitor: public NodeVisitor
{
public:
    RemoveNodeVisitor();
    RemoveNodeVisitor(Graph* g);
    virtual void Visit(Node* n);
private:
    Graph* m_graph;
};
RemoveNodeVisitor::RemoveNodeVisitor()
{
    m_graph = nullptr;
}
RemoveNodeVisitor::RemoveNodeVisitor(Graph* g)
{
    m_graph = g;
}
void RemoveNodeVisitor::Visit(Node* n)
{
    m_graph->RemoveEdgesForNode(n);
}
void Graph::RemoveEdgesForNode(Node *n)
{
    std::vector<Edge *>::iterator j;
    if (n->HasChildrenNode() == false)
    {
        for (j = m_edges->begin(); j != m_edges->end(); )
        {
			if ((*j)->GetStartNode() == n) {
				j = m_edges->erase(j);
			}
			else if ((*j)->GetEndNode() == n)
			{
				j = m_edges->erase(j);
			}
			else
				j++;
        }
    }
    else
    {
        RemoveNodeVisitor v(this);
        n->VisitChildren(&v);
    }
    
}
void Graph::RemoveNode(Node *n)
{
    std::vector<Node *>::iterator i;
    for (i = m_nodes->begin(); i != m_nodes->end(); i++)
    {
        if ((*i) == n)
        {
            m_nodes->erase(i);
            break;
        }
        else
        {
            (*i)->RemoveChildNode(n);
        }
    }

    RemoveEdgesForNode(n);
}
void Graph::RemoveEdge(Edge *e)
{
    std::vector<Edge *>::iterator i;
    for (i = m_edges->begin(); i != m_edges->end(); i++)
    {
        if ((*i) == e)
        {
            m_edges->erase(i);
            break;
        }
    }
}
class FindNodeVisitor : public NodeVisitor
{
public:
    FindNodeVisitor();
    FindNodeVisitor(Point *p);
    ~FindNodeVisitor();
    Node *GetNode();
    virtual void Visit(Node *n);

private:
    bool m_found;
    Node *m_node;
    Point *m_point;
};
FindNodeVisitor::FindNodeVisitor()
{
    m_found = false;
    m_node = nullptr;
    m_point = new Point;
}
FindNodeVisitor::FindNodeVisitor(Point *p)
{
    m_found = false;
    m_node = nullptr;
    m_point = new Point;
    m_point->Set(*p);
}
Node *FindNodeVisitor::GetNode()
{
    return m_node;
}
FindNodeVisitor::~FindNodeVisitor()
{
    delete m_point;
}
void FindNodeVisitor::Visit(Node *n)
{
    bool x_ok = false;
    bool y_ok = false;

    //if (m_found)
    //    return;

    Rect r = n->GetBounds();

    x_ok = (m_point->GetX() > r.GetX()) && (m_point->GetX() < (r.GetX() + r.GetW()));
    y_ok = (m_point->GetY() > r.GetY()) && (m_point->GetY() < (r.GetY() + r.GetH()));

    if (x_ok && y_ok)
    {
        m_node = n;
        //m_found = true;
    }
    //else
    if(n->HasChildrenNode())
    {
        FindNodeVisitor v(m_point);
        n->VisitChildren(&v);
        
        if(v.GetNode()!=nullptr)
            m_node = v.GetNode();
    }
}
Node *Graph::FindNode(Point &p)
{
    FindNodeVisitor v(&p);
    VisitNodes(&v);
    return v.GetNode();
}
Node* Graph::FindNode(Node* n)
{
    std::vector<Node *>::iterator i;
    for (i = m_nodes->begin(); i != m_nodes->end(); i++)
        if((*i)==n)
            return (*i);
    return nullptr;
}
Edge* Graph::FindEdge(Edge* e)
{
    std::vector<Edge *>::iterator i;
    for (i = m_edges->begin(); i != m_edges->end(); i++)
        if((*i)==e)
            return (*i);
    return nullptr;
}
Edge* Graph::FindEdge(Point& p)
{
    return nullptr;
}
Edge* Graph::FindEdge(Node*s,Node*e)
{
    std::vector<Edge *>::iterator i;
    for (i = m_edges->begin(); i != m_edges->end(); i++)
        if((*i)->GetStartNode()==s && (*i)->GetEndNode()==e)
        return (*i);
    return nullptr;
}
void Graph::ClearNodes()
{
    std::vector<Node *>::iterator i;
    for (i = m_nodes->begin(); i != m_nodes->end(); i++)
        delete (*i);
}
void Graph::ClearEdges()
{
    std::vector<Edge *>::iterator i;
    for (i = m_edges->begin(); i != m_edges->end(); i++)
        delete (*i);
}
void Graph::Draw(Render* r)
{
    if(m_needUpdateEdges) {
        UpdateEdges();
        m_needUpdateEdges = false;
    }
    std::vector<Node *>::iterator i;
    for (i = m_nodes->begin(); i != m_nodes->end(); i++)
    {
        (*i)->SetRender(r);
        (*i)->Draw();
    }

    std::vector<Edge *>::iterator j;
    for (j = m_edges->begin(); j != m_edges->end(); j++)
    {
        (*j)->SetRender(r);
        (*j)->Draw();
    }
}
void Graph::SetUpdateEdges(bool need)
{
    m_needUpdateEdges = true;
}
void Graph::UpdateEdges()
{
    std::vector<Edge*>::iterator i;
    std::vector<Edge*> dump_edges;
    /*1)dump edges */
    for(i=m_edges->begin();i!=m_edges->end();i++)
    {
        dump_edges.push_back(*i);
    }
    /*2)clear edges */
    m_edges->clear();
    /*3)reinsert edges */
    for(i=dump_edges.begin();i!=dump_edges.end();i++)
    {
        Point s = (*i)->GetStartNode()->GetConnectionPoint(*i);
        Point e = (*i)->GetEndNode()->GetConnectionPoint(*i);
        
        Connect((*i), (*i)->GetStartNode(), s, (*i)->GetEndNode(), e, nullptr, 0);/*transition points? */
    }
}
Graph::~Graph()
{
    ClearNodes();
    ClearEdges();
    delete m_nodes;
    delete m_edges;

    std::vector<ToolItem*>::iterator i;
    for(i=m_toolItems->begin();i!=m_toolItems->end();i++)
        delete (*i);
    
    delete m_toolItems;
}

} // namespace douml