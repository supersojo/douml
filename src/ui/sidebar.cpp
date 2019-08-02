/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "sidebar.h"
#include "workspace.h"
#include "toolitem.h"
#include "graph.h"
#include "rect.h"
#include "render.h"
#include "color.h"
#include "point.h"
namespace douml
{
class UndoToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void UndoToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
UndoToolItem undoToolItem;
/*----------------------------------------*/
class ZoomInToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void ZoomInToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
ZoomInToolItem zoomInToolItem;
/*----------------------------------------*/
class ZoomOutToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void ZoomOutToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
ZoomOutToolItem zoomOutToolItem;
/*------------------------------*/
class DeleteToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void DeleteToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
DeleteToolItem deleteToolItem;
/*------------------------------*/
class RedoToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void RedoToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
RedoToolItem redoToolItem;
/*------------------------------*/
class CutToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void CutToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
CutToolItem cutToolItem;
/*------------------------------*/
class CopyToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void CopyToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
CopyToolItem copyToolItem;
/*------------------------------*/
class PasteToolItem : public ToolItem
{
public:
	virtual void Draw(Render* r);
};
void PasteToolItem::Draw(Render* r)
{
	du_int x = GetLocation().GetX();
	du_int y = GetLocation().GetY();

	du_int w = TOOL_HEIGHT - 2 * 3;
	du_int h = TOOL_HEIGHT - 2 * 8;

	du_int x0 = x + 3;
	du_int y0 = y + 8;

	r->SetColor(Color(255, 255, 255));
	r->MoveTo(x0, y0);
	r->LineTo(x0 + w, y0);
	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);
	r->Fill();

	r->SetColor(Color(214, 214, 214));
	r->MoveTo(x0, y0);

	r->LineTo(x0 + w, y0);

	r->LineTo(x0 + w, y0 + h);
	r->LineTo(x0, y0 + h);
	r->LineTo(x0, y0);

	r->Stroke();

}
PasteToolItem pasteToolItem;
/*-------------------------------------------------------*/
du_int SideBar::MENU_TITLE_HEIGHT = 30;
du_int SideBar::MENU_TITLE_WIDTH = 280-30;// subtract 30

SideBar::SideBar()
{
    m_workspace = nullptr;
}
SideBar::SideBar(Workspace* ws)
{
    m_workspace = ws;
	ws->SetSideBar(this);
	m_standardMenuRect = new Rect;
	m_graphMenuRect = new Rect;

	m_standardMenuToggled = false;
	m_graphMenuToggled = false;

	m_toolItems = new std::vector<ToolItem*>;

	m_standardMenuRect->SetX(10);
	m_standardMenuRect->SetY(10);
	m_standardMenuRect->SetW(MENU_TITLE_WIDTH);
	m_standardMenuRect->SetH(GetCurrentStandardMenuRect().GetH());

	m_graphMenuRect->SetX(10);
	m_graphMenuRect->SetY(m_standardMenuRect->GetY()+ m_standardMenuRect->GetH()+10);/*10 is the gap*/
	m_graphMenuRect->SetW(MENU_TITLE_WIDTH);
	m_graphMenuRect->SetH(GetCurrentGraphMenuRect().GetH());
}
SideBar::~SideBar()
{
	delete m_standardMenuRect;
	delete m_graphMenuRect;

	delete m_toolItems;
}
void SideBar::CreateSideBar()
{

}
Workspace* SideBar::GetWorkspace()
{
	return m_workspace;
}
bool SideBar::IsStandardMenuToggled()
{
	return m_standardMenuToggled;
}
bool SideBar::IsGraphMenuToggled()
{
	return m_graphMenuToggled;
}
void SideBar::SetStandardMenuToggled(bool s)
{
	m_standardMenuToggled = s;
}
void SideBar::SetGraphMenuToggled(bool s)
{
	m_graphMenuToggled = s;
}
Rect SideBar::GetCurrentStandardMenuRect()
{
	std::vector<ToolItem*> tools;
	Rect r;
	r = *m_standardMenuRect;
	if (IsStandardMenuToggled()) {
		r.SetH(MENU_TITLE_HEIGHT);// only title
	}
	else {
		GetStandardToolItems(tools);
		du_int rows;
		rows = tools.size() / 4;
		r.SetH(MENU_TITLE_HEIGHT + rows * MENU_TITLE_HEIGHT + (rows+1)*10);
	}
	return r;
}
Rect SideBar::GetCurrentGraphMenuRect()
{
	std::vector<ToolItem*> tools;
	Rect r;
	r = *m_graphMenuRect;
	if (IsGraphMenuToggled()) {
		r.SetH(MENU_TITLE_HEIGHT);// only title
	}
	Graph* g = m_workspace->GetActiveGraph();
	if (g) {
		g->GetToolItems(tools);
		r.SetH(MENU_TITLE_HEIGHT + (tools.size() * MENU_TITLE_HEIGHT) + 20);
	}
	else {
		r.SetH(MENU_TITLE_HEIGHT);// only title
	}
	return r;
}
void SideBar::CreateStandardToolItems(std::vector<ToolItem*>& tools)
{
	undoToolItem.SetName("Undo");
	tools.push_back(&undoToolItem);

	zoomInToolItem.SetName("Zoom In");
	tools.push_back(&zoomInToolItem);

	zoomOutToolItem.SetName("Zoom Out");
	tools.push_back(&zoomOutToolItem);

	deleteToolItem.SetName("Delete");
	tools.push_back(&deleteToolItem);

	redoToolItem.SetName("Redo");
	tools.push_back(&redoToolItem);

	cutToolItem.SetName("Cut");
	tools.push_back(&cutToolItem);

	copyToolItem.SetName("Copy");
	tools.push_back(&copyToolItem);

	pasteToolItem.SetName("Paste");
	tools.push_back(&pasteToolItem);

}
void SideBar::GetStandardToolItems(std::vector<ToolItem*>& tools)
{
	tools.clear();
	if (m_toolItems->size() == 0)
	{
		/*first create tool items */
		CreateStandardToolItems(*m_toolItems);
	}
	std::vector<ToolItem*>::iterator i;
	for (i = m_toolItems->begin(); i != m_toolItems->end(); i++)
		tools.push_back(*i);
}
ToolItem* SideBar::GetActiveStandardToolItem()
{
	if (m_toolItems->size() == 0)
		return nullptr;

	std::vector<ToolItem*>::iterator i;
	for (i = m_toolItems->begin(); i != m_toolItems->end(); i++)
	{
		if ((*i)->GetSelected())
			return (*i);
	}
	return nullptr;
}
void SideBar::OnXXXX()
{
    
}
void SideBar::OnGraphToolItemClicked(ToolItem *item)
{


}
void SideBar::OnStandardItemClicked(ToolItem *item)
{

}

}