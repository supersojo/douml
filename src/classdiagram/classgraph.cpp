/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "classgraph.h"
#include "toolitem.h"
#include "render.h"
#include "point.h"
#include "color.h"
#include "arrowhead.h"
#include "trianglearrowhead.h"
#include "diamondarrowhead.h"

namespace douml
{
#if 0
class SelectNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~SelectNodeItem();
private:
    void FillRect(Render* r,du_int x,du_int y);
};
SelectNodeItem::~SelectNodeItem()
{

}
void SelectNodeItem::FillRect(Render* r,du_int x,du_int y)
{
    r->SetColor(Color(179,102,179));
    r->MoveTo(x,y);
    r->LineTo(x+4,y);
    r->LineTo(x+4,y+4);
    r->LineTo(x,y+4);
    r->LineTo(x,y);
    r->Fill();

}
void SelectNodeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int delta_x = ToolItem::TOOL_HEIGHT - 4 - 2*3;
    du_int delta_y = ToolItem::TOOL_HEIGHT - 4 - 2*3;

    FillRect(r,x+3,y+3);
    FillRect(r,x+3+delta_x,y+3);
    FillRect(r,x+3+delta_x,y+3+delta_y);
    FillRect(r,x+3,y+3+delta_y);
}
ToolItem* SelectNodeItem::Clone()
{
    SelectNodeItem* item = new SelectNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
#endif
static SelectNodeItem selectNodeItem;
/*---------------------------------------------------------- */
class ClassNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~ClassNodeItem();
};
ClassNodeItem::~ClassNodeItem()
{

}
void ClassNodeItem::DrawIcon(Render* r)
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
ToolItem* ClassNodeItem::Clone()
{
    ClassNodeItem* item = new ClassNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static ClassNodeItem classNodeItem;
/*---------------------------------------------------------- */
class InterfaceNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~InterfaceNodeItem();
};
InterfaceNodeItem::~InterfaceNodeItem()
{

}
void InterfaceNodeItem::DrawIcon(Render* r)
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

    du_int delta_x = 3+4;
    du_int delta_y = ToolItem::TOOL_HEIGHT/2;
    r->SetColor(Color(0,0,0));
    r->MoveTo(x+delta_x,y+delta_y);
    r->SetFontSize(3.0);
    r->ShowText("interface");
    r->SetFontSize(12.0);

}
ToolItem* InterfaceNodeItem::Clone()
{
    InterfaceNodeItem* item = new InterfaceNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static InterfaceNodeItem interfaceNodeItem;
/*---------------------------------------------------------- */
class PackageNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~PackageNodeItem();
private:
    void FillRect(Render* r,du_int x,du_int y,du_int w,du_int h);
    void DrawRect(Render* r,du_int x,du_int y,du_int w,du_int h);
};
PackageNodeItem::~PackageNodeItem()
{

}
void PackageNodeItem::FillRect(Render* r,du_int x,du_int y,du_int w,du_int h)
{
    r->SetColor(Color(255,255,255));
    r->MoveTo(x,y);
    r->LineTo(x+w,y);
    r->LineTo(x+w,y+h);
    r->LineTo(x,y+h);
    r->LineTo(x,y);
    r->Fill();
}
void PackageNodeItem::DrawRect(Render* r,du_int x,du_int y,du_int w,du_int h)
{
    r->SetColor(Color(214,214,214));
    r->MoveTo(x,y);
    r->LineTo(x+w,y);
    r->LineTo(x+w,y+h);
    r->LineTo(x,y+h);
    r->LineTo(x,y);
    r->Stroke();
}
void PackageNodeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int w =TOOL_HEIGHT - 2*3;
    du_int h =TOOL_HEIGHT - 2*3;
    

    FillRect(r,x+3,y+3,w/2,4);
    DrawRect(r,x+3,y+3,w/2,4);

    FillRect(r,x+3,y+7,w,h-4);
    DrawRect(r,x+3,y+7,w,h-4);

}
ToolItem* PackageNodeItem::Clone()
{
    PackageNodeItem* item = new PackageNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static PackageNodeItem packageNodeItem;
/*---------------------------------------------------------- */
#if 0
class NoteNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~NoteNodeItem();
};
NoteNodeItem::~NoteNodeItem()
{

}
void NoteNodeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    du_int w =TOOL_HEIGHT - 2*3;
    du_int h =TOOL_HEIGHT - 2*6;//4

    du_int x0 = x+3;
    du_int y0 = y+6;

    r->SetColor(Color(255,228,181));
    r->MoveTo(x0,y0);
    r->LineTo(x0+w-4,y0);
    r->LineTo(x0+w,y0+4);
    r->LineTo(x0+w,y0+h);
    r->LineTo(x0,y0+h);
    r->LineTo(x0,y0);
    r->Fill();

    r->SetColor(Color(182,177,166));
    r->MoveTo(x0,y0);
    r->LineTo(x0+w-4,y0);
    r->LineTo(x0+w,y0+4);
    r->LineTo(x0+w,y0+h);
    r->LineTo(x0,y0+h);
    r->LineTo(x0,y0);
    r->Stroke();

    r->SetColor(Color(255,255,255));
    r->MoveTo(x0+w-4,y0);
    r->LineTo(x0+w,y0+4);
    r->LineTo(x0+w-4,y0+4);
    r->LineTo(x0+w-4,y0);
    r->Fill();

    r->SetColor(Color(182,177,166));
    r->MoveTo(x0+w-4,y0);
    r->LineTo(x0+w,y0+4);
    r->LineTo(x0+w-4,y0+4);
    r->LineTo(x0+w-4,y0);
    r->Stroke();
    


}
ToolItem* NoteNodeItem::Clone()
{
	NoteNodeItem* item = new NoteNodeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
#endif
static NoteNodeItem noteNodeItem;
/*------------------------------------------------------------ */
class DependEdgeItem : public ToolItem 
{
public:
    DependEdgeItem();
    virtual ~DependEdgeItem();
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
private:
    ArrowHead* m_arrowHead;
};
DependEdgeItem::DependEdgeItem()
{
    m_arrowHead = new ArrowHead;
}
DependEdgeItem::~DependEdgeItem()
{
    delete m_arrowHead;
}
void DependEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();
    m_arrowHead->SetBorderColor(Color(0,0,0));
    
    r->SetColor(Color(0,0,0));
    r->SetLineWidth(1.5);
    r->SetDash(true);
    r->MoveTo(x+8,y+8);
    r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
    r->Stroke();

    r->SetLineWidth(1.5);
    r->SetDash(false);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* DependEdgeItem::Clone()
{
    DependEdgeItem* item = new DependEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static DependEdgeItem dependEdgeItem;
/*------------------------------------------------------------ */
class InheritEdgeItem : public ToolItem 
{
public:
    InheritEdgeItem();
    virtual ~InheritEdgeItem();
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
private:
    ArrowHead* m_arrowHead;
};
InheritEdgeItem::InheritEdgeItem()
{
    m_arrowHead = new TriangleArrowHead;
}
InheritEdgeItem::~InheritEdgeItem()
{
    delete m_arrowHead;
}
void InheritEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    m_arrowHead->SetBorderColor(Color(0,0,0));
    m_arrowHead->SetFillColor(Color(255,255,255));

    r->SetColor(Color(0,0,0));
    r->SetLineWidth(1.5);
    r->SetDash(false);
    r->MoveTo(x+8,y+8);
    r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
    r->Stroke();

    r->SetLineWidth(1.5);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* InheritEdgeItem::Clone()
{
    InheritEdgeItem* item = new InheritEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());
    

    return item;
}
static InheritEdgeItem inheritEdgeItem;
/*------------------------------------------------------------ */
class ImplementEdgeItem : public ToolItem 
{
public:
    ImplementEdgeItem();
    virtual ~ImplementEdgeItem();
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
private:
    ArrowHead* m_arrowHead;
};
ImplementEdgeItem::ImplementEdgeItem()
{
    m_arrowHead = new TriangleArrowHead;
}
ImplementEdgeItem::~ImplementEdgeItem()
{
    delete m_arrowHead;
}
void ImplementEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    m_arrowHead->SetBorderColor(Color(0,0,0));
    m_arrowHead->SetFillColor(Color(255,255,255));

    r->SetColor(Color(0,0,0));
    r->SetLineWidth(1.5);
    r->SetDash(true);
    r->MoveTo(x+8,y+8);
    r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
    r->Stroke();

    r->SetLineWidth(1.5);
    r->SetDash(false);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* ImplementEdgeItem::Clone()
{
    ImplementEdgeItem* item = new ImplementEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());
    

    return item;
}
static ImplementEdgeItem implementEdgeItem;
/*------------------------------------------------------------ */
class AssociateEdgeItem : public ToolItem
{
public:
	AssociateEdgeItem();
	virtual ~AssociateEdgeItem();
    virtual ToolItem* Clone();
	virtual void DrawIcon(Render* r);
private:
	ArrowHead* m_arrowHead;
};
AssociateEdgeItem::AssociateEdgeItem()
{
	m_arrowHead = new ArrowHead;
}
AssociateEdgeItem::~AssociateEdgeItem()
{
	delete m_arrowHead;
}
void AssociateEdgeItem::DrawIcon(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();
	m_arrowHead->SetBorderColor(Color(0, 0, 0));

	r->SetColor(Color(0, 0, 0));
	r->SetLineWidth(1.5);
	r->SetDash(false);
	r->MoveTo(x + 8, y + 8);
	r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
	r->Stroke();

	r->SetLineWidth(1.5);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* AssociateEdgeItem::Clone()
{
	AssociateEdgeItem* item = new AssociateEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());


    return item;
}
static AssociateEdgeItem associateEdgeItem;
/*------------------------------------------------------------ */
class AggregateEdgeItem : public ToolItem 
{
public:
    AggregateEdgeItem();
    virtual ~AggregateEdgeItem();
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
private:
    ArrowHead* m_arrowHead;
};
AggregateEdgeItem::AggregateEdgeItem()
{
    m_arrowHead = new DiamondArrowHead;
}
AggregateEdgeItem::~AggregateEdgeItem()
{
    delete m_arrowHead;
}
void AggregateEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    m_arrowHead->SetBorderColor(Color(0,0,0));
    m_arrowHead->SetFillColor(Color(255,255,255));

    r->SetLineWidth(1.5);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* AggregateEdgeItem::Clone()
{
    AggregateEdgeItem* item = new AggregateEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static AggregateEdgeItem aggregateEdgeItem;
/*------------------------------------------------------------ */
class ComposeEdgeItem : public ToolItem 
{
public:
    ComposeEdgeItem();
    virtual ~ComposeEdgeItem();
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
private:
    ArrowHead* m_arrowHead;
};
ComposeEdgeItem::ComposeEdgeItem()
{
    m_arrowHead = new DiamondArrowHead;
}
ComposeEdgeItem::~ComposeEdgeItem()
{
    delete m_arrowHead;
}
void ComposeEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();

    m_arrowHead->SetBorderColor(Color(0,0,0));
    m_arrowHead->SetFillColor(Color(0,0,0));

    r->SetLineWidth(1.5);
	m_arrowHead->Draw(r, Point(x + 8, y + 8), Point(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8));
}
ToolItem* ComposeEdgeItem::Clone()
{
    ComposeEdgeItem* item = new ComposeEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
static ComposeEdgeItem composeEdgeItem;
/*------------------------------------------------------------ */
#if 0
class NoteEdgeItem : public ToolItem 
{
public:
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
    virtual ~NoteEdgeItem();

};
NoteEdgeItem::~NoteEdgeItem()
{
    
}
void NoteEdgeItem::DrawIcon(Render* r)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();
    
    r->SetColor(Color(0,0,0));
    r->SetLineWidth(1.5);
    r->SetDash(true);
    r->MoveTo(x+8,y+8);
    r->LineTo(x + ToolItem::TOOL_HEIGHT - 8, y + ToolItem::TOOL_HEIGHT - 8);
    r->Stroke();

    r->SetDash(false);
}
ToolItem* NoteEdgeItem::Clone()
{
    NoteEdgeItem* item = new NoteEdgeItem;

    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());

    return item;
}
#endif
static NoteEdgeItem noteEdgeItem;
/*---------------------------------------------------------------- */
ClassGraph::~ClassGraph()
{

}
void ClassGraph::CreateToolItems(std::vector<ToolItem*>&items)
{
	selectNodeItem.SetName("Select");
    selectNodeItem.SetBackgroundColor(Color(255,225,155));
    selectNodeItem.SetBorderColor(Color(247,154,24));
    selectNodeItem.SetTextColor(Color(0,0,0));
    
    items.push_back(selectNodeItem.Clone());


    classNodeItem.SetName("Class");
    classNodeItem.SetBackgroundColor(Color(255,225,155));
    classNodeItem.SetBorderColor(Color(247,154,24));
    classNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(classNodeItem.Clone());

    interfaceNodeItem.SetName("Interface");
    interfaceNodeItem.SetBackgroundColor(Color(255,225,155));
    interfaceNodeItem.SetBorderColor(Color(247,154,24));
    interfaceNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(interfaceNodeItem.Clone());

    packageNodeItem.SetName("Package");
    packageNodeItem.SetBackgroundColor(Color(255,225,155));
    packageNodeItem.SetBorderColor(Color(247,154,24));
	packageNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(packageNodeItem.Clone());

    noteNodeItem.SetName("Note");
    noteNodeItem.SetBackgroundColor(Color(255,225,155));
    noteNodeItem.SetBorderColor(Color(247,154,24));
	noteNodeItem.SetTextColor(Color(0,0,0));
    items.push_back(noteNodeItem.Clone());

    dependEdgeItem.SetName("Depends on");
    dependEdgeItem.SetBackgroundColor(Color(255,225,155));
    dependEdgeItem.SetBorderColor(Color(247,154,24));
	dependEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(dependEdgeItem.Clone());

    inheritEdgeItem.SetName("Inherits from");
    inheritEdgeItem.SetBackgroundColor(Color(255,225,155));
    inheritEdgeItem.SetBorderColor(Color(247,154,24));
	inheritEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(inheritEdgeItem.Clone());

    implementEdgeItem.SetName("Implements interface");
    implementEdgeItem.SetBackgroundColor(Color(255,225,155));
    implementEdgeItem.SetBorderColor(Color(247,154,24));
	implementEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(implementEdgeItem.Clone());

    associateEdgeItem.SetName("Is associated with");
    associateEdgeItem.SetBackgroundColor(Color(255,225,155));
    associateEdgeItem.SetBorderColor(Color(247,154,24));
	associateEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(associateEdgeItem.Clone());

    aggregateEdgeItem.SetName("Is an aggregate of");
    aggregateEdgeItem.SetBackgroundColor(Color(255,225,155));
    aggregateEdgeItem.SetBorderColor(Color(247,154,24));
	aggregateEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(aggregateEdgeItem.Clone());

    composeEdgeItem.SetName("Is composed of");
    composeEdgeItem.SetBackgroundColor(Color(255,225,155));
    composeEdgeItem.SetBorderColor(Color(247,154,24));
	composeEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(composeEdgeItem.Clone());

    noteEdgeItem.SetName("Note connector");
    noteEdgeItem.SetBackgroundColor(Color(255,225,155));
    noteEdgeItem.SetBorderColor(Color(247,154,24));
	noteEdgeItem.SetTextColor(Color(0,0,0));
    items.push_back(noteEdgeItem.Clone());

}

}