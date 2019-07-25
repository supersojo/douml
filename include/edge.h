/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_EDGE_H
#define DU_EDGE_H
#include "douml.h"
#include <vector>

namespace douml
{
	class Id;
    class Node;
    class Point;
    class Rect;
    class Edge;
    class Render;
    class Graph;
    class Direction;
    class BentStyle;
    class ArrowHead;
    class LineStyle;
class DU_API EdgeVisitor
{
public:
    virtual void Visit(Edge* e);
};

class DU_API Edge
{
public:
    Edge();
    ~Edge();
    Node* GetStartNode();
    Node* GetEndNode();

    void SetStartNode(Node* n);
    void SetEndNode(Node* n);

    Point GetStartLocation();
    Point GetEndLocation();

    void SetStartLocation(Point& p);
    void SetEndLocation(Point& p);

    Point GetStartLocationOnGraph();
    Point GetEndLocationOnGraph();

    Rect GetBounds();
    
    void SetTransitionPoints(Point*ps,du_int n);
    Point GetTransitionPoint(du_int i);

    bool Contains(Point& p);

    void GetConnectionPoints(Point&p0,Point&p1);

    Render* GetRender();
    void SetRender(Render* r);

    Graph* GetGraph();
    void SetGraph(Graph* g);

    Direction GetDirection(Node* n);

    virtual void Draw();
    virtual BentStyle* GetDefaultBentStyle();
    BentStyle* GetBentStyle();
    void SetBentStyle(BentStyle* bent);

    ArrowHead* GetStartArrowHead();
    void SetStartArrowHead(ArrowHead* ah);

    ArrowHead* GetEndArrowHead();
    void SetEndArrowHead(ArrowHead* ah);

    void SetLineStyle(LineStyle* ls);
    LineStyle* GetLineStyle();

    bool GetSelected();
    void SetSelected(bool s);
private:
    Id* m_id;
    Node* m_startNode;
    Node* m_endNode;
    Point* m_startLocation;
    Point* m_endLocation;
    std::vector<Point>* m_transitionPoints;
    Render* m_render;
	Graph* m_graph;
    LineStyle* m_lineStyle;
    BentStyle* m_bentStyle;
    ArrowHead* m_startArrowHead;
    ArrowHead* m_endArrowHead;
    bool m_selected;
};

} // namespace douml

#endif
