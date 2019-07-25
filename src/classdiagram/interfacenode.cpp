/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "interfacenode.h"
#include "shape.h"
#include "render.h"
#include "viewlayer.h"
#include "nodeview.h"
#include "point.h"
#include "rect.h"
#include "color.h"
#include <cmath>
namespace douml
{
/*----------------------------------------------------- */
class InterfaceNodeShape : public Shape
{
public:
    InterfaceNodeShape();
    virtual void DrawBackground(Node *n);
    virtual void DrawBorder(Node *n);

    static du_int MIN_WIDTH;
    static du_int MIN_HEIGHT;

private:
    void FillRect(Render *r, du_int x, du_int y);
};

du_int InterfaceNodeShape::MIN_WIDTH = 100;
du_int InterfaceNodeShape::MIN_HEIGHT = 45;

InterfaceNodeShape::InterfaceNodeShape()
{
    SetWidth(MIN_WIDTH);
    SetHeight(MIN_HEIGHT);
}

void InterfaceNodeShape::DrawBackground(Node *n)
{
    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    r->SetColor(n->GetBackgroundColor());

    /*origin */
    r->MoveTo(t.GetX(), t.GetY());

    r->LineTo(t.GetX(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY());
    r->LineTo(t.GetX(), t.GetY());

    r->Fill();
}
void InterfaceNodeShape::FillRect(Render *r, du_int x, du_int y)
{
    r->MoveTo(x - 2, y - 2);
    r->LineTo(x + 2, y - 2);
    r->LineTo(x + 2, y + 2);
    r->LineTo(x - 2, y + 2);
    r->LineTo(x - 2, y - 2);
    r->Fill();
}
void InterfaceNodeShape::DrawBorder(Node *n)
{
    du_int x, y;

    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    r->SetColor(n->GetBorderColor());

    /*origin */
    r->MoveTo(t.GetX(), t.GetY());

    r->LineTo(t.GetX(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY());
    r->LineTo(t.GetX(), t.GetY());

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
class InterfaceNodeLayer : public ViewLayer
{
public:
    InterfaceNodeLayer();
    InterfaceNodeLayer(InterfaceNode *n);
    virtual void Draw(douml::Node *n);

private:
    InterfaceNode *m_node;
};
InterfaceNodeLayer::InterfaceNodeLayer()
{
    SetW(InterfaceNodeShape::MIN_WIDTH);
    SetH(InterfaceNodeShape::MIN_HEIGHT);
    m_node = nullptr;
}
InterfaceNodeLayer::InterfaceNodeLayer(InterfaceNode *n)
{
    SetW(InterfaceNodeShape::MIN_WIDTH);
    SetH(InterfaceNodeShape::MIN_HEIGHT);
    m_node = n;
}
void InterfaceNodeLayer::Draw(Node *n)
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
        m_node->GetMethods()->size() == 0)
    {
        du_char *interface_str = "<<interface>>";
        r->TextBoxSize(interface_str, w0, h0, x_bearing, y_bearing);

        /*assert GetW()>w0 */
        delta_x = (GetW() - w0) / 2;
        delta_y = (GetH() - h0) / 2;

        r->SetColor(n->GetTextColor());
        r->MoveTo(t.GetX() + delta_x, t.GetY() + delta_y + abs(y_bearing));
        r->ShowText(interface_str);
        return;
    }

    /*2) only name */
    if (m_node->GetName() != nullptr &&
        m_node->GetMethods()->size() == 0)
    {
        r->TextBoxSize(m_node->GetName(), w0, h0, x_bearing, y_bearing);

        /*assert GetW()>w0 */
        delta_x = (GetW() - w0) / 2;
        delta_y = (GetH() - h0) / 2;

        r->SetColor(n->GetTextColor());
        r->MoveTo(t.GetX() + delta_x, t.GetY() + delta_y + abs(y_bearing));
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
        r->MoveTo(rect.GetX() + delta_x, rect.GetY() + InterfaceNode::GAP_Y + abs(y_bearing));
        r->ShowText(m_node->GetName());
    }
    /*separator */
    r->MoveTo(rect.GetX(), rect.GetY() + rect.GetH());
    r->LineTo(rect.GetX() + rect.GetW(), rect.GetY() + rect.GetH());
    r->Stroke();

    std::vector<du_char *>::iterator i;

    rect = m_node->GetMethodsRect();
    pos = 0;
    for (i = m_node->GetMethods()->begin(); i != m_node->GetMethods()->end(); i++)
    {
        r->TextBoxSize((*i), w0, h0, x_bearing, y_bearing);
        r->SetColor(n->GetTextColor());
        r->MoveTo(rect.GetX() + InterfaceNode::GAP_X, rect.GetY() + pos + InterfaceNode::GAP_Y + abs(y_bearing));
        r->ShowText(*i);
        pos = pos + h0 + InterfaceNode::GAP_Y;
    }
}
/*--------------------------------------------------------- */
du_int InterfaceNode::GAP_X = 5;
du_int InterfaceNode::GAP_Y = 5;

InterfaceNode::InterfaceNode()
{
    m_name = nullptr;
    m_methods = new std::vector<du_char *>;

    m_nameRect = new Rect;
    m_methodsRect = new Rect;

    BackgroundLayer *background = new BackgroundLayer;
    background->SetShape(new InterfaceNodeShape);

    BorderLayer *border = new BorderLayer;
    border->SetShape(new InterfaceNodeShape);

    SetBackgroundColor(Color(255, 255, 255));
    SetBorderColor(Color(0,0,0));

    SetViewLayers(background, border, new InterfaceNodeLayer(this));
}

InterfaceNode::~InterfaceNode()
{
    delete m_methods;

    delete m_nameRect;
    delete m_methodsRect;
}
bool InterfaceNode::GetChanged()
{
    return m_changed;
}
void InterfaceNode::SetChanged(bool c)
{
    m_changed = c;
}
du_char *InterfaceNode::GetName()
{
    return m_name;
}
void InterfaceNode::SetName(du_char *n)
{
    m_name = n;
    SetChanged(true);
}

std::vector<du_char *> *InterfaceNode::GetMethods()
{
    return m_methods;
}
void InterfaceNode::SetMethods(std::vector<du_char *> &methods)
{
    m_methods->clear();

    std::vector<du_char *>::iterator i;
    for (i = methods.begin(); i != methods.end(); i++)
    {
        m_methods->push_back(*i);
    }
    SetChanged(true);
}
Rect InterfaceNode::GetNameRect()
{
    return *m_nameRect;
}
Rect InterfaceNode::GetMethodsRect()
{
    return *m_methodsRect;
}
void InterfaceNode::UpdateMinRects()
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

    if (m_name)
    {
        r->TextBoxSize(m_name, w0, h0, x_bearing, y_bearing);
        w = w0 > w ? w0 : w;
        h += h0;
        rows0 += h0 + 2 * GAP_Y;
    }

    std::vector<du_char *>::iterator i;

    for (i = m_methods->begin(); i != m_methods->end(); i++)
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

    m_methodsRect->SetW(w + 2 * GAP_X);
    m_methodsRect->SetX(x);

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

    m_methodsRect->SetY(y + offset);

    if (rows2 > 0)
        m_methodsRect->SetH(rows2);
    else
        m_methodsRect->SetH(GAP_Y * 2);
}
void InterfaceNode::NotifyCallback()
{
    if (!GetChanged())
        return;

    //GetRender()->SetFont("Microsoft YaHei UI");

    ViewLayer *v;

    v = GetView()->GetContentLayer();

    UpdateMinRects();

    /*tell viewlayer size changed */
    v->SetMinW(m_nameRect->GetW());
    v->SetMinH(m_nameRect->GetH() + m_methodsRect->GetH());

    SetChanged(false);
}

} // namespace douml