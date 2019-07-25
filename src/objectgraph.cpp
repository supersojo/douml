/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "objectgraph.h"
#include "toolitem.h"
#include "render.h"
#include "point.h"
#include "color.h"
#include "arrowhead.h"
#include "trianglearrowhead.h"
#include "diamondarrowhead.h"

namespace douml
{
static SelectNodeItem selectNodeItem;
/*---------------------------------------------------------- */
class ObjectNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~ObjectNodeItem();
};
ObjectNodeItem::~ObjectNodeItem()
{

}
void ObjectNodeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int w =TOOL_HEIGHT - 2*3;
    du_int h =TOOL_HEIGHT - 2*8;
    
    du_int x0 = x+3;
    du_int y0 = y+8;

    r->SetColor(Color(255,255,255));
    r->MoveTo(x0,y0);
    r->LineTo(x0+w,y0);
    r->LineTo(x0+w,y0+h);
    r->LineTo(x0,y0+h);
    r->LineTo(x0,y0);
    r->Fill();

    r->SetColor(Color(214,214,214));
    r->MoveTo(x0,y0);

    r->LineTo(x0+w,y0);

    r->LineTo(x0+w,y0+h);
    r->LineTo(x0,y0+h);
    r->LineTo(x0,y0);

    r->Stroke();

}
ToolItem* ObjectNodeItem::Clone()
{
    ObjectNodeItem* item = new ObjectNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static ObjectNodeItem objectNodeItem;
/*---------------------------------------------------------- */
class FieldNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~FieldNodeItem();
};
FieldNodeItem::~FieldNodeItem()
{

}
void FieldNodeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int w =TOOL_HEIGHT - 2*3;
    du_int h =TOOL_HEIGHT/2;
    
    du_int x0 = x+3;
    du_int y0 = y+h;

    r->SetColor(Color(85,88,92));
    r->MoveTo(x0,y0);
    r->LineTo(x0+w,y0);

    r->Stroke();

}
ToolItem* FieldNodeItem::Clone()
{
    FieldNodeItem* item = new FieldNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static FieldNodeItem fieldNodeItem;
/*---------------------------------------------------------- */
static NoteNodeItem noteNodeItem;
/*---------------------------------------------------------- */
class ReferenceObjectItem : public ToolItem 
{
public:
    ReferenceObjectItem();
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~ReferenceObjectItem();
private:
    TriangleArrowHead* m_arrowHead;
};
ReferenceObjectItem::ReferenceObjectItem()
{
    m_arrowHead = new TriangleArrowHead;
    m_arrowHead->SetArrowLength(5);
    m_arrowHead->SetBorderColor(Color(0,0,0));
    m_arrowHead->SetFillColor(Color(0,0,0));
}
ReferenceObjectItem::~ReferenceObjectItem()
{
    delete m_arrowHead;
}
void ReferenceObjectItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int w =TOOL_HEIGHT - 2*3;
    du_int h =TOOL_HEIGHT - 2*8;
    
    du_int x0 = x+3;
    du_int y0 = y+8;

    r->SetColor(Color(85,88,92));
    //r->MoveTo(x0,y0);
    //r->LineTo(x0+w/2,y0);

    //r->Stroke();
    r->MoveTo(x0,y0);
    //r->CurveTo(x0+w/2,y0,x0+w,y0+h/2,x0+w/2,y0+h);
    r->CurveTo(x0+w,y0,x0+w,y0+h/2,x0+w/2,y0+h);
    r->Stroke();

    /*arrowhead */
    m_arrowHead->Draw(r,Point(x0+w,y0),Point(x0+w/2,y0+h));

}
ToolItem* ReferenceObjectItem::Clone()
{
	ReferenceObjectItem* item = new ReferenceObjectItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static ReferenceObjectItem referenceObjectItem;
/*---------------------------------------------------------- */
class AssociateObjectItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~AssociateObjectItem();
};
AssociateObjectItem::~AssociateObjectItem()
{

}
void AssociateObjectItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();
    
    r->SetColor(Color(0,0,0));
    r->SetLineWidth(1.5);
    r->SetDash(false);
    r->MoveTo(x+8,y+8);
    r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
    r->Stroke();

}
ToolItem* AssociateObjectItem::Clone()
{
	AssociateObjectItem* item = new AssociateObjectItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static AssociateObjectItem associateObjectItem;
/*---------------------------------------------------------------- */
static NoteEdgeItem noteEdgeItem;
/*---------------------------------------------------------------- */
ObjectGraph::~ObjectGraph()
{

}
void ObjectGraph::CreateToolItems(std::vector<ToolItem*>&items)
{
	selectNodeItem.SetName("Select");
    selectNodeItem.SetBackgroundColor(Color(255,225,155));
    selectNodeItem.SetBorderColor(Color(247,154,24));
    selectNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(selectNodeItem.Clone());


    objectNodeItem.SetName("Object");
    objectNodeItem.SetBackgroundColor(Color(255,225,155));
    objectNodeItem.SetBorderColor(Color(247,154,24));
    objectNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(objectNodeItem.Clone());

    fieldNodeItem.SetName("Field");
    fieldNodeItem.SetBackgroundColor(Color(255,225,155));
    fieldNodeItem.SetBorderColor(Color(247,154,24));
    fieldNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(fieldNodeItem.Clone());

    noteNodeItem.SetName("Note");
    noteNodeItem.SetBackgroundColor(Color(255,225,155));
    noteNodeItem.SetBorderColor(Color(247,154,24));
    noteNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(noteNodeItem.Clone());

    referenceObjectItem.SetName("Object reference (from field)");
    referenceObjectItem.SetBackgroundColor(Color(255,225,155));
    referenceObjectItem.SetBorderColor(Color(247,154,24));
    referenceObjectItem.SetTextColor(Color(0,0,0));
    items.push_back(referenceObjectItem.Clone());

    associateObjectItem.SetName("Association between objects");
    associateObjectItem.SetBackgroundColor(Color(255,225,155));
    associateObjectItem.SetBorderColor(Color(247,154,24));
    associateObjectItem.SetTextColor(Color(0,0,0));
    items.push_back(associateObjectItem.Clone());

    noteEdgeItem.SetName("Note connector");
    noteEdgeItem.SetBackgroundColor(Color(255,225,155));
    noteEdgeItem.SetBorderColor(Color(247,154,24));
	noteEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(noteEdgeItem.Clone());

}

}