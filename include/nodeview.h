/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_NODEVIEW_H
#define DU_NODEVIEW_H

#include "douml.h"
#include <vector>
namespace douml
{
class ViewLayer;
class Node;
class Rect;
class Direction;
class Edge;
} // namespace douml

namespace douml
{
class DU_API NodeView
{
public:
    NodeView();
    ~NodeView();
    void SetBackgroundLayer(ViewLayer *v);
    void SetBorderLayer(ViewLayer *v);
    void SetContentLayer(ViewLayer *v);
    ViewLayer* GetBackgroundLayer();
    ViewLayer* GetBorderLayer();
    ViewLayer* GetContentLayer();
    virtual void CalcConnectionPointForEdges(Node* n,std::vector<Edge*>& edges,Direction d,Edge* e);
    Rect GetBounds();
    void Draw(Node *node);

private:
    ViewLayer *m_background;
    ViewLayer *m_border;
    ViewLayer *m_content;
};
} // namespace douml

#endif
