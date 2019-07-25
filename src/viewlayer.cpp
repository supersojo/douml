/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "viewlayer.h"
#include "node.h"
#include "rect.h"
#include "shape.h"

namespace douml
{
/*-------------------------------------------------- */
ViewLayer::ViewLayer()
{
    m_w = m_h = m_minw = m_minh = 0;
    m_parent = nullptr;
    m_child = nullptr;
}
ViewLayer::~ViewLayer()
{
    
}
du_int ViewLayer::GetW()
{
    return m_w>m_minw?m_w:m_minw;
}
du_int ViewLayer::GetH()
{
    return m_h>m_minh?m_h:m_minh;
}
du_int ViewLayer::GetMinW()
{
    return m_minw;
}
du_int ViewLayer::GetMinH()
{
    return m_minh;
}
ViewLayer* ViewLayer::GetParent()
{
    return m_parent;
}
void ViewLayer::SetParent(ViewLayer &p)
{
    m_parent = &p;
}
ViewLayer* ViewLayer::GetChild()
{
    return m_child;
}
void ViewLayer::SetChild(ViewLayer &c)
{
    m_child = &c;
}
void ViewLayer::SetW(du_int w)
{
    m_w = w;
}
void ViewLayer::SetH(du_int h)
{
    m_h = h;
}
void ViewLayer::SetMinW(du_int minw)
{
    m_minw = minw;
    Refresh();
}
void ViewLayer::SetMinH(du_int minh)
{
    m_minh = minh;
    Refresh();
}
Rect ViewLayer::GetBounds()
{
    /*only w,h valid */
    Rect r;
    r.SetW(GetMinH());
    r.SetH(GetMinW());
    return r;
}
void ViewLayer::Refresh()
{
    RefreshUp();
    RefreshDown();
}
void ViewLayer::RefreshUp()
{
    if(m_child!=nullptr)
        m_child->RefreshUp();
}
void ViewLayer::RefreshDown()
{
    if(m_parent!=nullptr)
        m_parent->RefreshDown();
}
void ViewLayer::Draw(Node* n)
{
}
/*----------------------------------------- */
BackgroundLayer::BackgroundLayer()
{
    m_shape = nullptr;
}
Rect BackgroundLayer::GetBounds()
{
    Rect r;
    r.SetW(m_shape->GetWidth());
    r.SetH(m_shape->GetHeight());
    return r;
}

BackgroundLayer::~BackgroundLayer()
{
    if(m_shape!=nullptr)
        delete m_shape;
}
void BackgroundLayer::Draw(douml::Node *n)
{
    m_shape->DrawBackground(n);
}
void BackgroundLayer::RefreshUp()
{
/*do nothing we are the bottom*/
}
void BackgroundLayer::RefreshDown()
{
    du_int w,h;
    ViewLayer* v = GetChild();
    w = GetW();
    h = GetH();
    if(w<v->GetW())
        w = v->GetW();
    if(h<v->GetH())
        h = v->GetH();

    SetW(w);
    SetH(h);
    m_shape->SetWidth(w);
    m_shape->SetHeight(h);

    ViewLayer::RefreshDown();
/*child size changed adjust self */
}
Shape* BackgroundLayer::GetShape()
{
    return m_shape;
}
void BackgroundLayer::SetShape(Shape* s)
{
    m_shape = s;
    SetW(m_shape->GetWidth());
    SetH(m_shape->GetHeight());
}
/*--------------------------------------------- */
BorderLayer::BorderLayer()
{
    m_shape = nullptr;
}
Rect BorderLayer::GetBounds()
{
    Rect r;
    r.SetW(m_shape->GetWidth());
    r.SetH(m_shape->GetHeight());
    return r;
}
BorderLayer::~BorderLayer()
{
    if(m_shape!=nullptr)
        delete m_shape;
}
void BorderLayer::Draw(douml::Node *n)
{
    m_shape->DrawBorder(n);
}
void BorderLayer::RefreshUp()
{
    /* */
    du_int w,h;
    ViewLayer* v = GetParent();
    w = GetW();
    h = GetH();
    if(w<v->GetW())
        w = v->GetW();
    if(h<v->GetH())
        h = v->GetH();

    SetW(w);
    SetH(h);
    m_shape->SetWidth(w);
    m_shape->SetHeight(h);
    
    ViewLayer::RefreshUp();
}
void BorderLayer::RefreshDown()
{
    /* */
    du_int w,h;
    ViewLayer* v = GetChild();
    w = GetW();
    h = GetH();
    if(w<v->GetW())
        w = v->GetW();
    if(h<v->GetH())
        h = v->GetH();

    SetW(w);
    SetH(h);
    m_shape->SetWidth(w);
    m_shape->SetHeight(h);
    
    ViewLayer::RefreshDown();
}
Shape* BorderLayer::GetShape()
{
    return m_shape;
}
void BorderLayer::SetShape(Shape* s)
{
    m_shape = s;
    SetW(m_shape->GetWidth());
    SetH(m_shape->GetHeight());
}
/*------------------------------------- */
} // namespace douml