/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_GRAPH_H
#define DU_GRAPH_H
#include "douml.h"
#include <vector>

namespace douml
{
	class Point;
    class Node;
    class Edge;
	class Render;
    class NodeVisitor;
    class EdgeVisitor;
    class ToolItem;
class DU_API Graph 
{
public:
    Graph();
    void VisitNodes(NodeVisitor* v);
    void VisitEdges(EdgeVisitor* v);
    bool AddNode(Node* n,Point* p);
    bool Connect(Edge* edge,
                Node* start,Point& startLocation,
                Node* end,Point& endLocation,
                Point* ps,du_int n);
    void RemoveNode(Node* n);
    void RemoveEdge(Edge* e);
    void RemoveEdgesForNode(Node* n);
    Node* FindNode(Point& p);
    Node* FindNode(Node* n);
    Edge* FindEdge(Point& p);
    Edge* FindEdge(Edge* e);
    Edge* FindEdge(Node*s,Node*e);
    void UpdateEdges();
    void SetUpdateEdges(bool need);
    virtual void Draw(Render* r);
    virtual void GetToolItems(std::vector<ToolItem*>& tools);
    ToolItem* GetActiveToolItem();
    virtual void CreateToolItems(std::vector<ToolItem*> &toolItems);
    virtual ~Graph();
private:
    
    void ClearNodes();
    void ClearEdges();
    std::vector<Node*>* m_nodes;
    std::vector<Edge*>* m_edges;

    bool m_needUpdateEdges;
    std::vector<ToolItem*>* m_toolItems;

};

}
#endif