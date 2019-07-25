/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "toolitem.h"
#include "color.h"
#include "point.h"
#include "render.h"
#include <cmath>
namespace douml
{

du_int ToolItem::TOOL_WIDTH = 180+15;
du_int ToolItem::TOOL_HEIGHT = 30;

ToolItem::ToolItem()
{
    m_backgroundColor = new Color;
    m_textColor = new Color;
    m_borderColor = new Color;
    m_name = nullptr;
    m_selected = false;
    m_location = new Point;
}
ToolItem::ToolItem(du_char* n)
{
    m_backgroundColor = new Color;
    m_textColor = new Color;
    m_borderColor = new Color;
    m_name = n;
    m_selected = false;
    m_location = new Point;
}
ToolItem::~ToolItem()
{
    delete m_backgroundColor;
    delete m_textColor;
    delete m_borderColor;
	delete m_location;
}
Color ToolItem::GetBackgroundColor()
{
    return *m_backgroundColor;
}
Color ToolItem::GetBorderColor()
{
    return *m_borderColor;
}
Color ToolItem::GetTextColor()
{
    return *m_textColor;
}
void ToolItem::SetBackgroundColor(Color&c)
{
    m_backgroundColor->Set(c);
}
void ToolItem::SetBorderColor(Color&c)
{
    m_borderColor->Set(c);
}
void ToolItem::SetTextColor(Color&c)
{
    m_textColor->Set(c);
}
Point ToolItem::GetLocation()
{
    return *m_location;
}
void ToolItem::SetLocation(Point&t)
{
    m_location->Set(t);
}
bool ToolItem::GetSelected()
{
    return m_selected;
}
void ToolItem::SetSelected(bool s)
{
    m_selected = s;
}
bool ToolItem::Contains(Point&t)
{
    du_int x = GetLocation().GetX();
    du_int y = GetLocation().GetY();
    bool x_ok = (t.GetX()>x) && (t.GetX()<(x+ToolItem::TOOL_WIDTH));
    bool y_ok = (t.GetY()>y) && (t.GetY()<(y+ToolItem::TOOL_HEIGHT));
   
    return x_ok&&y_ok;
}
ToolItem* ToolItem::Clone()
{
    ToolItem* item = new ToolItem;
    item->SetName(GetName());
    item->SetBackgroundColor(GetBackgroundColor());
    item->SetBorderColor(GetBorderColor());
    item->SetTextColor(GetTextColor());
    item->SetLocation(GetLocation());
    item->SetSelected(GetSelected());
    return item;
}
du_char* ToolItem::GetName()
{
    return m_name;
}
void ToolItem::SetName(du_char* n)
{
    m_name = n;
}
void ToolItem::DrawIcon(Render* r)
{

}
void ToolItem::Draw(Render* r)
{
    du_int x,y;
    x = m_location->GetX();
    y = m_location->GetY();
    if(m_selected){
        /*draw background */
        r->SetColor(GetBackgroundColor());
        r->MoveTo(x,y);
        r->LineTo(x+ToolItem::TOOL_WIDTH,y);
        r->LineTo(x+ToolItem::TOOL_WIDTH,y+ToolItem::TOOL_HEIGHT);
        r->LineTo(x,y+ToolItem::TOOL_HEIGHT);
        r->LineTo(x,y);
        r->Fill();

        /*draw border */
        r->SetColor(GetBorderColor());
        r->MoveTo(x,y);
        r->LineTo(x+ToolItem::TOOL_WIDTH,y);
        r->LineTo(x+ToolItem::TOOL_WIDTH,y+ToolItem::TOOL_HEIGHT);
        r->LineTo(x,y+ToolItem::TOOL_HEIGHT);
        r->LineTo(x,y);
        r->Stroke();
    }else{
        /*restore */
        //???
    }
    
    /*draw icon */
    DrawIcon(r);

    /*draw string */
    if(m_name)
    {
        
        du_int w,h,x_bearing,y_bearing;
        r->TextBoxSize(m_name,w,h,x_bearing,y_bearing);
        /*assert height>h */
        du_int delta_x = ToolItem::TOOL_HEIGHT + 3/*gap between icon and text */;
        du_int delta_y = (ToolItem::TOOL_HEIGHT-h)/2 + abs(y_bearing);
        r->SetFontSize(12.0);
        r->SetColor(GetTextColor());
        r->MoveTo(x+delta_x,y+delta_y);
        r->ShowText(m_name);
        
    }
}
/*--------------------------------------------------------------------------- */
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
/*-------------------------------------------------------------------------------- */
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
/*------------------------------------------------------------------------------ */
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
/*------------------------------------------------------------------------------------ */
}