/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "objectnode.h"
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
class ObjectNodeShape : public Shape
{
public:
    ObjectNodeShape();
    virtual void DrawBackground(Node *n);
    virtual void DrawBorder(Node *n);

    static du_int MIN_WIDTH;
    static du_int MIN_HEIGHT;
private:
    void FillRect(Render *r, du_int x, du_int y);

};
du_int ObjectNodeShape::MIN_WIDTH = 80;//100 -> 80
du_int ObjectNodeShape::MIN_HEIGHT = 45;
ObjectNodeShape::ObjectNodeShape()
{
    SetWidth(MIN_WIDTH);
    SetHeight(MIN_HEIGHT);
}

void ObjectNodeShape::DrawBackground(Node *n)
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
void ObjectNodeShape::FillRect(Render *r, du_int x, du_int y)
{
    r->MoveTo(x - 2, y - 2);
    r->LineTo(x + 2, y - 2);
    r->LineTo(x + 2, y + 2);
    r->LineTo(x - 2, y + 2);
    r->LineTo(x - 2, y - 2);
    r->Fill();
}
void ObjectNodeShape::DrawBorder(Node *n)
{
    du_int x, y;

    Render *r = n->GetRender();
    Point t = n->GetLocationOnGraph();

    r->SetColor(n->GetBorderColor());

    r->SetLineWidth(0.5);

    /*origin */
    r->MoveTo(t.GetX(), t.GetY());

    r->LineTo(t.GetX(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY() + GetHeight());
    r->LineTo(t.GetX() + GetWidth(), t.GetY());
    r->LineTo(t.GetX(), t.GetY());

    r->Stroke();
    if (n->GetSelected())
    {
        r->SetColor(Color(179,102,179));
        FillRect(r, t.GetX(), t.GetY());
        FillRect(r, t.GetX(), t.GetY() + GetHeight());
        FillRect(r, t.GetX() + GetWidth(), t.GetY() + GetHeight());
        FillRect(r, t.GetX() + GetWidth(), t.GetY());
    }
}
/*--------------------------------------------------------- */
class ObjectNodeLayer : public ViewLayer
{
public:
    ObjectNodeLayer();
    ObjectNodeLayer(ObjectNode *n);
    virtual void Draw(douml::Node *n);

private:
    ObjectNode *m_node;
};
ObjectNodeLayer::ObjectNodeLayer()
{
    SetW(ObjectNodeShape::MIN_WIDTH);
    SetH(ObjectNodeShape::MIN_HEIGHT);
    m_node = nullptr;
}
ObjectNodeLayer::ObjectNodeLayer(ObjectNode *n)
{
    SetW(ObjectNodeShape::MIN_WIDTH);
    SetH(ObjectNodeShape::MIN_HEIGHT);
    m_node = n;
}
void ObjectNodeLayer::Draw(Node *n)
{
	du_int x_bearing;
	du_int y_bearing;
    du_int delta_x = 0;
    du_int delta_y = 0;
    du_int pos = 0;
    du_int index = 0;
    du_int w0 = 0, h0 = 0;


    /* 1) all empty */
    if(m_node->GetName()==nullptr &&
        m_node->GetFields()->size()==0)
    {
        return;
    }

    Point t = n->GetLocationOnGraph();
    Render *r = n->GetRender();

    /*2)  name */
    if(m_node->GetName()!=nullptr)
    {
        r->TextBoxSize(m_node->GetName(),w0,h0, x_bearing, y_bearing);

        /*assert GetW()>w0 */
        delta_x = (GetW()-w0)/2;
        delta_y = (ObjectNodeShape::MIN_HEIGHT-h0)/2;

        r->SetColor(n->GetTextColor());
        r->MoveTo(t.GetX() + delta_x, t.GetY() + delta_y+abs(y_bearing));
        r->ShowText(m_node->GetName());
        
    }
    r->SetColor(Color(0,0,0));
    r->MoveTo(t.GetX(),t.GetY()+ObjectNodeShape::MIN_HEIGHT);
    r->LineTo(t.GetX()+GetW(),t.GetY()+ObjectNodeShape::MIN_HEIGHT);
    r->Stroke();

    /*3)fields */
    Rect rect;
    rect = m_node->GetFieldsRect();
    rect.SetY(t.GetY()+ObjectNodeShape::MIN_HEIGHT);

    std::vector<du_char*>::iterator i;
    pos = 0;
    for(index=0,i=m_node->GetFields()->begin();i!=m_node->GetFields()->end();i++,index++)
    {
        r->TextBoxSize((*i),w0,h0, x_bearing, y_bearing);
        r->SetColor(n->GetTextColor());
        r->MoveTo(rect.GetX() + ObjectNode::GAP_X, rect.GetY() + pos + ObjectNode::GAP_Y+abs(y_bearing));
        r->ShowText(*i);

        if(m_node->GetFieldSelected()&&m_node->GetFieldSelectedIndex()==index)
        {
            r->FillRect(rect.GetX()-2,rect.GetY()+pos-2+ObjectNode::GAP_Y/2,4,4);
            r->FillRect(rect.GetX()+GetW()-2,rect.GetY()+pos-2+ObjectNode::GAP_Y/2,4,4);
            r->FillRect(rect.GetX()-2,rect.GetY()+pos-2+h0+3*ObjectNode::GAP_Y/2,4,4);
            r->FillRect(rect.GetX()+GetW()-2,rect.GetY()+pos-2+h0+3*ObjectNode::GAP_Y/2,4,4);
        }

        pos = pos + h0 + ObjectNode::GAP_Y;
        
    }
}
/*--------------------------------------------------------- */
du_int ObjectNode::GAP_X = 5;
du_int ObjectNode::GAP_Y = 5;

ObjectNode::ObjectNode()
{
    m_name = nullptr;
    m_fields = new std::vector<du_char *>;

    m_nameRect = new Rect;
    m_fieldsRect = new Rect;

    BackgroundLayer *background = new BackgroundLayer;
    background->SetShape(new ObjectNodeShape);

    BorderLayer *border = new BorderLayer;
    border->SetShape(new ObjectNodeShape);

    SetBackgroundColor(Color(255, 255, 255));
    SetBorderColor(Color(0,0,0));

    SetViewLayers(background, border, new ObjectNodeLayer(this));
}
ObjectNode::~ObjectNode()
{
    delete m_fields;

    delete m_nameRect;
    delete m_fieldsRect;
}
du_char* ObjectNode::GetName()
{
    return m_name;
}
void ObjectNode::SetName(du_char* n)
{
    m_name = n;
}
Rect ObjectNode::GetNameRect()
{
	return *m_nameRect;
}
Rect ObjectNode::GetFieldsRect()
{
	return *m_fieldsRect;
}
std::vector<du_char*>* ObjectNode::GetFields()
{
    return m_fields;
}
bool ObjectNode::GetNodeSelected()
{
    return m_nodeSelected;
}
void ObjectNode::SetNodeSelected(bool s)
{
    m_nodeSelected = s;
}
du_int ObjectNode::GetFieldSelectedIndex()
{
    return m_fieldSelectedIndex;
}
void ObjectNode::SetFieldSelectedIndex(du_int index)
{
    m_fieldSelectedIndex = index;
}
bool ObjectNode::GetFieldSelected()
{
    return m_fieldSelected;
}
void ObjectNode::SetFieldSelected(bool s)
{
    m_fieldSelected = s;
}
bool ObjectNode::GetChanged()
{
    return m_changed;
}
void ObjectNode::SetChanged(bool c)
{
    m_changed = c;
}
void ObjectNode::AddField(du_int preIndex,du_char* n)
{
    std::vector<du_char*>::iterator i;
    if(m_fields->size()==0)
    {
        m_fields->push_back(n);
        m_fieldSelectedIndex = 0;
        m_fieldSelected = true;
        m_nodeSelected = false;
        return;
    }
    if(preIndex<0||preIndex>=(du_int)m_fields->size())
        return;

    i = m_fields->begin();
    i += preIndex+1;

    m_fields->insert(i,n);//insert at pre i 
    m_fieldSelectedIndex = preIndex+1;
    m_fieldSelected = true;
    m_nodeSelected = false;
    
}
void ObjectNode::RemoveField(du_int index)
{
    std::vector<du_char*>::iterator i;
    if(m_fields->size()==0)
        return;
    if(index<0||index>=(du_int)m_fields->size())
        return;
    i = m_fields->begin()+index;
    m_fields->erase(i);
    if(m_fieldSelected && m_fieldSelectedIndex==index) {
        m_fieldSelected = false;
        m_fieldSelectedIndex = 0;
    }
}
void ObjectNode::UpdateMinRects()
{
	du_int x_bearing;
	du_int y_bearing;

    du_int x,y;
    du_int offset;

    Render *r = GetRender();
    du_int gap = 0;
    du_int rows0 = 0, rows1 = 0;
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
        rows0 += h0+2*GAP_Y;
    }
    
    std::vector<du_char *>::iterator i;
    for (i = m_fields->begin(); i != m_fields->end(); i++)
    {
        if (*i)
        {
            r->TextBoxSize((*i), w0, h0, x_bearing, y_bearing);
            w = w0 > w ? w0 : w;
            h += h0;
            rows1 += h0 + GAP_Y;
        }
    }

    if(rows1>0)
        rows1 += GAP_Y;

    
    offset = 0;

    m_nameRect->SetW(w+2*GAP_X);
    m_nameRect->SetX(x);
    m_nameRect->SetY(y);
    m_fieldsRect->SetW(w+2*GAP_X);
    m_fieldsRect->SetX(x);


    if (rows0 > 0){
        offset += rows0;
        m_nameRect->SetH(rows0);
    }else{
       m_nameRect->SetH(GAP_Y*2);
       offset += GAP_Y*2;
    }
    
    m_fieldsRect->SetY(y+offset);

    if (rows1 > 0){
        offset += rows1;
        m_fieldsRect->SetH(rows1);
    }else{
        m_fieldsRect->SetH(GAP_Y*2);
        offset += GAP_Y*2;
    }
}
void ObjectNode::NotifyCallback()
{
    if (!GetChanged())
        return;

	//GetRender()->SetFont("Microsoft YaHei UI");

    ViewLayer *v;

    v = GetView()->GetContentLayer();

    UpdateMinRects();

    /*tell viewlayer size changed */
    v->SetMinW(m_nameRect->GetW());
    v->SetMinH(m_nameRect->GetH()+m_fieldsRect->GetH());

    SetChanged(false);
}

}