/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "packagenode.h"
#include "shape.h"
#include "render.h"
#include "viewlayer.h"
#include "nodeview.h"
#include "point.h"
#include "graph.h"
#include "edge.h"
#include "direction.h"
#include "rect.h"
#include "color.h"
#include <cmath>

namespace douml
{
/*----------------------------------------------------- */
class PackageNodeShape : public Shape
{
public:
    PackageNodeShape();
    virtual void DrawBackground(Node *n);
    virtual void DrawBorder(Node *n);

    static du_int MIN_WIDTH;
    static du_int MIN_HEIGHT;

private:
    void FillRect(Render *r, du_int x, du_int y);
};

du_int PackageNodeShape::MIN_WIDTH = 100;
du_int PackageNodeShape::MIN_HEIGHT = 65;/* */

PackageNodeShape::PackageNodeShape()
{
    SetWidth(MIN_WIDTH);
    SetHeight(MIN_HEIGHT);
}

void PackageNodeShape::DrawBackground(Node *n)
{
    du_int w, h;
    du_int x, y;

    /*assert m_node == n */
    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    x = t.GetX();
    y = t.GetY();

    w = PackageNode::TOP_X;
    h = PackageNode::TOP_Y;

    r->SetColor(n->GetBackgroundColor());

    /*origin */
    r->MoveTo(x, y);

    r->LineTo(x + w, y);
    r->LineTo(x + w, y + h);
    r->LineTo(x, y + h);
    r->LineTo(x, y);

    r->Fill();

    w = GetWidth();
    h = GetHeight() - PackageNode::TOP_Y;

    y = y + PackageNode::TOP_Y;

    r->MoveTo(x, y);

    r->LineTo(x + w, y);
    r->LineTo(x + w, y + h);
    r->LineTo(x, y + h);
    r->LineTo(x, y);

    r->Fill();
}
void PackageNodeShape::FillRect(Render *r, du_int x, du_int y)
{
    r->MoveTo(x - 2, y - 2);
    r->LineTo(x + 2, y - 2);
    r->LineTo(x + 2, y + 2);
    r->LineTo(x - 2, y + 2);
    r->LineTo(x - 2, y - 2);
    r->Fill();
}
void PackageNodeShape::DrawBorder(Node *n)
{
    du_int w, h;
    du_int x, y;

    /*assert m_node == n */
    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    x = t.GetX();
    y = t.GetY();

    w = PackageNode::TOP_X;
    h = PackageNode::TOP_Y;

    r->SetColor(n->GetBorderColor());

    /*origin */
    r->MoveTo(x, y);

    r->LineTo(x + w, y);
    r->LineTo(x + w, y + h);
    r->LineTo(x, y + h);
    r->LineTo(x, y);

    r->Stroke();

    w = GetWidth();
    h = GetHeight() - PackageNode::TOP_Y;

    y = y + PackageNode::TOP_Y;

    r->MoveTo(x, y);

    r->LineTo(x + w, y);
    r->LineTo(x + w, y + h);
    r->LineTo(x, y + h);
    r->LineTo(x, y);

    r->Stroke();

    if (n->GetSelected())
    {
        FillRect(r, t.GetX(), t.GetY());
        FillRect(r, t.GetX(), t.GetY() + GetHeight());
        FillRect(r, t.GetX() + GetWidth(), t.GetY() + GetHeight());
        FillRect(r, t.GetX() + GetWidth(), t.GetY());
    }
}
/*--------------------------------------------------------- */
class PackageNodeView : public NodeView 
{
public:
    virtual void CalcConnectionPointForEdges(Node* n,std::vector<Edge*>& edges,Direction d,Edge* e);
};

void PackageNodeView::CalcConnectionPointForEdges(Node* n,std::vector<Edge*>& edges,Direction d,Edge* e)
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
        /*init */
        delta_x = r.GetW() / (s + 1);
        delta_y = r.GetH() / (s + 1);

        if ((*i)->GetStartNode() == n)
        {
            if (d.Equals(Direction::NORTH))
            {
                delta_x = PackageNode::TOP_X / (s + 1);
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
                delta_y = (r.GetH()-PackageNode::TOP_Y) / (s + 1);
                (*i)->SetStartLocation(Point(r.GetW(), PackageNode::TOP_Y + delta_y * (pos + 1)));
            }
        }
        if ((*i)->GetEndNode() == n)
        {
            if (d.Equals(Direction::NORTH))
            {
                delta_x = PackageNode::TOP_X / (s + 1);
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
                delta_y = (r.GetH()-PackageNode::TOP_Y) / (s + 1);
                (*i)->SetEndLocation(Point(r.GetW(), PackageNode::TOP_Y + delta_y * (pos + 1)));
            }
        }
    }
}
/*--------------------------------------------------------- */
class PackageNodeLayer : public ViewLayer
{
public:
    PackageNodeLayer();
    PackageNodeLayer(PackageNode *n);
    virtual void Draw(douml::Node *n);

private:
    PackageNode *m_node;
};
PackageNodeLayer::PackageNodeLayer()
{
    SetW(PackageNodeShape::MIN_WIDTH);
    SetH(PackageNodeShape::MIN_HEIGHT);
    m_node = nullptr;
}

PackageNodeLayer::PackageNodeLayer(PackageNode *n)
{
    SetW(PackageNodeShape::MIN_WIDTH);
    SetH(PackageNodeShape::MIN_HEIGHT);
    m_node = n;
}

void PackageNodeLayer::Draw(Node *n)
{
    du_int x_bearing;
    du_int y_bearing;
    du_int delta_x = 0;
    du_int delta_y = 0;
    du_int pos = 0;
    du_int w0 = 0, h0 = 0;

    Point t = n->GetLocationOnGraph();
    Render *r = n->GetRender();

    /* 1) all empty */
    if (m_node->GetName() == nullptr &&
        m_node->GetContent()->size() == 0)
    {
        return;
    }

    /*2) only name */
    if (m_node->GetName() != nullptr &&
        m_node->GetContent()->size() == 0)
    {
        r->TextBoxSize(m_node->GetName(), w0, h0, x_bearing, y_bearing);

        /*assert GetW()>w0 */
        delta_x = (GetW() - w0) / 2;
        delta_y = (GetH() - PackageNode::TOP_Y - h0) / 2;

        r->SetColor(n->GetTextColor());
        r->MoveTo(t.GetX() + delta_x, t.GetY() + PackageNode::TOP_Y + delta_y + abs(y_bearing));
        r->ShowText(m_node->GetName());
        return;
    }

    /*3)others */
    Rect rect;
    rect = m_node->GetNameRect();
    if (m_node->GetName() != nullptr)
    {
        r->TextBoxSize(m_node->GetName(), w0, h0, x_bearing, y_bearing);

        /*assert GetW()>w0 */
        delta_x = (GetW() - w0) / 2;

        r->SetColor(n->GetTextColor());
        r->MoveTo(rect.GetX() + delta_x, rect.GetY() + PackageNode::GAP_Y + abs(y_bearing));
        r->ShowText(m_node->GetName());
    }
    /*separator */
    r->MoveTo(rect.GetX(), rect.GetY() + rect.GetH());
    r->LineTo(rect.GetX() + rect.GetW(), rect.GetY() + rect.GetH());
    r->Stroke();

    std::vector<du_char *>::iterator i;

    rect = m_node->GetContentRect();
    pos = 0;
    for (i = m_node->GetContent()->begin(); i != m_node->GetContent()->end(); i++)
    {
        r->TextBoxSize((*i), w0, h0, x_bearing, y_bearing);
        r->SetColor(n->GetTextColor());
        r->MoveTo(rect.GetX() + PackageNode::GAP_X, rect.GetY() + pos + PackageNode::GAP_Y + abs(y_bearing));
        r->ShowText(*i);
        pos = pos + h0 + PackageNode::GAP_Y;
    }
}
/*--------------------------------------------------------- */
du_int PackageNode::TOP_X = 50;
du_int PackageNode::TOP_Y = 20;

du_int PackageNode::GAP_X = 5;
du_int PackageNode::GAP_Y = 5;

PackageNode::PackageNode():Node(new PackageNodeView)
{
    m_name = nullptr;
    m_content = new std::vector<du_char *>;

    m_nameRect = new Rect;
    m_contentRect = new Rect;

    BackgroundLayer *background = new BackgroundLayer;
    background->SetShape(new PackageNodeShape);

    BorderLayer *border = new BorderLayer;
    border->SetShape(new PackageNodeShape);

    SetBackgroundColor(Color(255, 255, 255));
    SetBorderColor(Color(0,0,0));

    SetViewLayers(background, border, new PackageNodeLayer(this));
}

PackageNode::~PackageNode()
{
    delete m_content;

    delete m_nameRect;
    delete m_contentRect;
}
bool PackageNode::GetChanged()
{
    return m_changed;
}
void PackageNode::SetChanged(bool c)
{
    m_changed = c;
}
du_char *PackageNode::GetName()
{
    return m_name;
}
void PackageNode::SetName(du_char *n)
{
    m_name = n;
    SetChanged(true);
}

std::vector<du_char *> *PackageNode::GetContent()
{
    return m_content;
}
void PackageNode::SetContent(std::vector<du_char *> &content)
{
    m_content->clear();

    std::vector<du_char *>::iterator i;
    for (i = content.begin(); i != content.end(); i++)
    {
        m_content->push_back(*i);
    }
    SetChanged(true);
}
Rect PackageNode::GetNameRect()
{
    return *m_nameRect;
}
Rect PackageNode::GetContentRect()
{
    return *m_contentRect;
}
void PackageNode::UpdateMinRects()
{
    du_int x_bearing;
    du_int y_bearing;

    du_int x, y;
    du_int offset;

    Render *r = GetRender();
    du_int gap = 0;
    du_int rows0 = 0, rows1 = 0, rows2 = 0;
    du_int w0, h0;
    du_int w, h;
    w = 0;
    h = 0;

    x = GetLocationOnGraph().GetX();
    y = GetLocationOnGraph().GetY();

    /*update y */
    y = y + PackageNode::TOP_Y;

    if (m_name)
    {
        r->TextBoxSize(m_name, w0, h0, x_bearing, y_bearing);
        w = w0 > w ? w0 : w;
        h += h0;
        rows0 += h0 + 2 * GAP_Y;
    }

    std::vector<du_char *>::iterator i;

    for (i = m_content->begin(); i != m_content->end(); i++)
    {
        if (*i)
        {
            r->TextBoxSize((*i), w0, h0, x_bearing, y_bearing);
            w = w0 > w ? w0 : w;
            h += h0;
            rows2 += h0 + GAP_Y;
        }
    }

    if (rows2 > 0)
        rows2 += GAP_Y;

    offset = 0;

    m_nameRect->SetW(w + 2 * GAP_X);
    m_nameRect->SetX(x);
    m_nameRect->SetY(y);

    m_contentRect->SetW(w + 2 * GAP_X);
    m_contentRect->SetX(x);

    if (rows0 > 0)
    {
        offset += rows0;
        m_nameRect->SetH(rows0);
    }
    else
    {
        m_nameRect->SetH(GAP_Y * 2);
        offset += GAP_Y * 2;
    }

    m_contentRect->SetY(y + offset);

    if (rows2 > 0)
        m_contentRect->SetH(rows2);
    else
        m_contentRect->SetH(GAP_Y * 2);
}
void PackageNode::NotifyCallback()
{
    if (!GetChanged())
        return;

    //GetRender()->SetFont("Microsoft YaHei UI");

    ViewLayer *v;

    v = GetView()->GetContentLayer();

    UpdateMinRects();

    /*tell viewlayer size changed */
    v->SetMinW(m_nameRect->GetW());
    v->SetMinH(m_nameRect->GetH() + m_contentRect->GetH() + PackageNode::TOP_Y);

    SetChanged(false);
}

} // namespace douml