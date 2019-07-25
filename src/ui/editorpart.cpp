/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "editorpart.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "workspace.h"
#include "point.h"
namespace douml
{
void EditorPart::CreateEditorPart()
{

}
void EditorPart::OnXXXX()
{
    
}
void EditorPart::OnNewNode(Point& p,Node* n)
{
    Graph* g = m_workspace->GetActiveGraph();
    g->AddNode(n,&p);
}
void EditorPart::OnNewEdge(Node* start,Node* end,Edge* e)
{
    Graph* g = m_workspace->GetActiveGraph();
    e->SetStartNode(start);
    e->SetEndNode(end);
    Point t1 = start->GetConnectionPoint(e);
    Point t2 = end->GetConnectionPoint(e);
    g->Connect(e,start,t1,end,t2,nullptr,0);
}
void EditorPart::OnSelectNode(Node* n)
{
    n->SetSelected(true);
}
void EditorPart::OnSelectEdge(Edge* e)
{
    e->SetSelected(true);
}

}