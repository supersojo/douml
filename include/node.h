/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_NODE_H
#define DU_NODE_H

#include "douml.h"
#include <vector>

namespace douml
{
    class Point;
    class Id;
    class Color;
    class NodeView;
    class ViewLayer;
    class Render;
    class Node;
    class Edge;
    class Rect;
    class Graph;
} // namespace douml

namespace douml
{

class DU_API NodeVisitor
{
public:
    virtual void Visit(Node* n);
};
class DU_API Node
{
public:
    Node();
    Node(NodeView* nv);
    virtual ~Node();
    Node* GetParent();
    void SetParent(Node* n);
    Point GetLocation();
    void SetLocation(Point& p);
    Point GetLocationOnGraph(); 
    Id& GetId();
    void AddChildNode(Node* n);
    void RemoveChildNode(Node* n);
    bool HasParent()const;
    bool HasChildrenNode()const;
    void VisitChildren(NodeVisitor* v);
    Color& GetBackgroundColor();
    Color& GetBorderColor();
    Color& GetTextColor();
    void SetBackgroundColor(Color& c);
    void SetBorderColor(Color& c);
    void SetTextColor(Color& c);
    void SetViewLayers(ViewLayer*background,ViewLayer*border,ViewLayer*content);
    virtual Point GetConnectionPoint(Edge* e);
    Render* GetRender();
    void SetRender(Render* render);
    Graph* GetGraph();
    void GetConnectedEdges(std::vector<Edge*>& edges);
    void GetEdgesOnSameSide(std::vector<Edge*>&edges,Edge*e);
    void SetGraph(Graph* g);
    Rect GetBounds();
    NodeView* GetView();
    virtual void Draw();
    virtual void NotifyCallback();
    virtual Point GetCenterLocationOnGraph();
    bool GetSelected();
    void SetSelected(bool s);
private:
    Node *m_parent;
    Point *m_location;
    Id *m_id;
    std::vector<Node *> *m_children;

    void ClearChildNodes();

    bool m_selected;
    
    Color *m_backgroundColor;
    Color *m_borderColor;
    Color *m_textColor;

    NodeView *m_view;

    Render* m_render;

    Graph* m_graph;
};

} // namespace douml

#endif