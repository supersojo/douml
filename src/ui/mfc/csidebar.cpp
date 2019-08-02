/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "csidebar.h"
#include "cworkspace.h"
#include "platform/cairorender.h"
#include "rect.h"
#include "color.h"
#include "graph.h"
#include "toolitem.h"
#include "point.h"
namespace douml
{

CSideBar::CSideBar()
{

}
CSideBar::CSideBar(CWorkspace* ws):SideBar(ws)
{
    RECT rect;
    Create(AfxRegisterWndClass(NULL),NULL,WS_CHILD|WS_VSCROLL|WS_THICKFRAME,rect,ws,-1,NULL);
}
BEGIN_MESSAGE_MAP(CSideBar,CWnd)
    ON_WM_SIZE()
	ON_WM_PAINT()
    ON_WM_ERASEBKGND()
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CSideBar::OnSize(UINT nType, int cx, int cy)
{

}
void CSideBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ClickPoint.x = point.x;
	m_ClickPoint.y = point.y;
	CWnd::OnLButtonDown(nFlags,point);
}
void CSideBar::HandleLButtonClick(CPoint& point)
{
	du_int index = 0;

	du_int x = GetCurrentStandardMenuRect().GetX();
	du_int y = GetCurrentStandardMenuRect().GetY();
	du_int w = GetCurrentStandardMenuRect().GetW();
	du_int h = GetCurrentStandardMenuRect().GetH();

	//standard tools area check
	bool x_ok = (point.x > x) && (point.x < x + MENU_TITLE_WIDTH);
	bool y_ok = (point.y > y) && (point.y < y + MENU_TITLE_HEIGHT);
	if (x_ok&&y_ok)
	{
		// standard title click
		SetStandardMenuToggled(!IsStandardMenuToggled());
		Invalidate();
		return;
	}
	else
	{
		if (!IsStandardMenuToggled())
		{
			// check standard tool item click
			y += MENU_TITLE_HEIGHT;
			h -= MENU_TITLE_HEIGHT;
			x_ok = (point.x > x) && (point.x < x + MENU_TITLE_WIDTH);
			y_ok = (point.y > y) && (point.y < y + h);
			if (x_ok&&y_ok)
			{
				std::vector<ToolItem*> tools;
				std::vector<ToolItem*>::iterator i;
				GetStandardToolItems(tools);

				
				du_int row = 0, col = 0;
				for (index = 0,i = tools.begin(); i != tools.end(); i++, index++)
				{
					du_int x0, y0;
					row = index / 4;
					col = index % 4;
					x0 = x + 5 + col * 70;
					y0 = y + 10 + row * 40;
					if ((point.x > x0 && point.x<(x0 + MENU_TITLE_HEIGHT)) &&
						(point.y>y0 && point.y < (y0 + MENU_TITLE_HEIGHT))) {
						OnStandardItemClicked(*i);
						return;
						
					}
				}
			}
		}
	}
	
	//graph tools area check
	x = GetCurrentGraphMenuRect().GetX();
	y = GetCurrentGraphMenuRect().GetY();
	w = GetCurrentGraphMenuRect().GetW();
	h = GetCurrentGraphMenuRect().GetH();
	if (IsStandardMenuToggled()) {
		y = GetCurrentStandardMenuRect().GetY() + GetCurrentStandardMenuRect().GetH() + 10;/*10 is thr gap*/
	}
	x_ok = (point.x > x) && (point.x < x + MENU_TITLE_WIDTH);
	y_ok = (point.y > y) && (point.y < y + MENU_TITLE_HEIGHT);
	if (x_ok&&y_ok)
	{
		// graph title click
		SetGraphMenuToggled(!IsGraphMenuToggled());
		Invalidate();
		return;
	}
	else
	{
		if (!IsGraphMenuToggled())
		{
			// check graph tool item click
			y += MENU_TITLE_HEIGHT;
			h -= MENU_TITLE_HEIGHT;
			
			x_ok = (point.x > x) && (point.x < x + MENU_TITLE_WIDTH);
			y_ok = (point.y > y) && (point.y < y + h);
			if (x_ok&&y_ok)
			{
				index = (point.y - y) / MENU_TITLE_HEIGHT;
				Graph* g = GetWorkspace()->GetActiveGraph();
				std::vector<ToolItem*> tools;
				g->GetToolItems(tools);
				ToolItem* prev;
				prev = g->GetActiveToolItem();
				if (prev) {
					prev->SetSelected(false);
				}
				tools.at(index)->SetSelected(true);
				prev = tools.at(index);//update selected item
				Invalidate();
				return;
			}
		}
	}
}
void CSideBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_ClickPoint.x==point.x && m_ClickPoint.y==point.y)
	{
		HandleLButtonClick(point);
	}
	CWnd::OnLButtonUp(nFlags, point);
}
void CSideBar::RenderStandardMenu(Render* r)
{
	du_int x, y;
	du_int w, h;
	Rect rect = this->GetCurrentStandardMenuRect();
	x = rect.GetX();
	y = rect.GetY();
	w = rect.GetW();
	h = rect.GetH();

	/*title*/
	r->SetColor(Color(51, 72, 101));
	r->MoveTo(x,y);
	r->LineTo(x+w,y);
	r->LineTo(x+w,y+ MENU_TITLE_HEIGHT);
	r->LineTo(x,y+ MENU_TITLE_HEIGHT);
	r->LineTo(x,y);
	r->Fill();

	du_int w0, h0, x_bearing, y_bearing;
	r->TextBoxSize("Standard Tools",w0,h0,x_bearing,y_bearing);
	du_int delta_x = (MENU_TITLE_WIDTH-w0)/2;
	du_int delta_y = (MENU_TITLE_HEIGHT - h0) / 2 + abs(y_bearing);
	r->MoveTo(x+delta_x,y+delta_y);
	r->SetColor(Color(255, 255, 255));
	r->ShowText("Standard Tools");

	/*tool items*/
	if (IsStandardMenuToggled())
		return;

	y += MENU_TITLE_HEIGHT;
	h -= MENU_TITLE_HEIGHT;
	r->SetColor(Color(224, 231, 242));
	r->MoveTo(x, y);
	r->LineTo(x + w, y);
	r->LineTo(x + w, y + h);
	r->LineTo(x, y + h);
	r->LineTo(x, y);
	r->Fill();

	std::vector<ToolItem*> tools;
	std::vector<ToolItem*>::iterator i;
	GetStandardToolItems(tools);
	du_int index = 0;
	du_int row = 0;
	du_int col = 0;
	for (i = tools.begin(); i != tools.end(); i++,index++)
	{
		ToolItem* tool;
		tool = *i;
		row = index / 4;// 4 items per row
		col = index % 4;
		tool->SetLocation(Point(x+5+col*70,y+10+row*40));
		tool->Draw(r);
	}
}
void CSideBar::RenderGraphMenu(Render* r)
{
	du_int x, y;
	du_int w, h;
	Rect rect = this->GetCurrentGraphMenuRect();
	x = rect.GetX();
	y = rect.GetY();
	w = rect.GetW();
	h = rect.GetH();
	/*
	x,y may be adjusted according standard menu toggle flag
	*/
	if (IsStandardMenuToggled()) {
		y = GetCurrentStandardMenuRect().GetY() + GetCurrentStandardMenuRect().GetH() + 10;/*10 is thr gap*/
	}

	/*title*/
	r->SetColor(Color(51, 72, 101));
	r->MoveTo(x, y);
	r->LineTo(x + w, y);
	r->LineTo(x + w, y + MENU_TITLE_HEIGHT);
	r->LineTo(x, y + MENU_TITLE_HEIGHT);
	r->LineTo(x, y);
	r->Fill();

	du_int w0, h0, x_bearing, y_bearing;
	r->TextBoxSize("Graph Tools", w0, h0, x_bearing, y_bearing);
	du_int delta_x = (MENU_TITLE_WIDTH - w0) / 2;
	du_int delta_y = (MENU_TITLE_HEIGHT - h0) / 2 + abs(y_bearing);
	r->MoveTo(x + delta_x, y + delta_y);
	r->SetColor(Color(255, 255, 255));
	r->ShowText("Graph Tools");


	/*tool items*/
	if (IsGraphMenuToggled())
		return;

	y += MENU_TITLE_HEIGHT;
	h -= MENU_TITLE_HEIGHT;
	r->SetColor(Color(224, 231, 242));
	r->MoveTo(x, y);
	r->LineTo(x + w, y);
	r->LineTo(x + w, y + h);
	r->LineTo(x, y + h);
	r->LineTo(x, y);
	r->Fill();

	// with some gap to the title line
	x += 10;
	y += 10;
	std::vector<ToolItem*> tools;
	Graph* g = GetWorkspace()->GetActiveGraph();
	g->GetToolItems(tools);
	std::vector<ToolItem*>::iterator i;
	ToolItem *tool;
	int index = 0;
	for (i = tools.begin(); i != tools.end(); i++,index++)
	{
		tool = *i;
		tool->SetLocation(Point(x,y+index*MENU_TITLE_HEIGHT));
		//tool->SetSelected(true);
		tool->Draw(r);
	}
	
}
void CSideBar::Rend(Render* r)
{
	RenderStandardMenu(r);
	RenderGraphMenu(r);
}
void CSideBar::OnPaint()
{
	
	CDC memdc;
	CBitmap bitmap;
	CRect rect;


	/*
	BeginPaint and EndPaint auto called in CPaintDC but CClientDC doest not do it
	So use CPaintDC instead
	*/
	//CClientDC dc(this);
	CPaintDC dc(this);

	GetClientRect(&rect);
	/*create memdc related 'dc'*/
	memdc.CreateCompatibleDC(&dc);
	/*create btimap dc */
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//::SelectObject(memdc.GetSafeHdc(), bitmap);
	memdc.SelectObject(bitmap);
	//ReleaseDC(&memdc);


	/*fill background */
	COLORREF crl = RGB(104, 134, 178);
	//COLORREF crl = RGB(255, 0, 0);
	memdc.FillSolidRect(rect, crl);



	HDC hdc = memdc.GetSafeHdc();

	/*init render */
	douml::CairoRender r;
	r.SetHDC(hdc);
	r.Init();

	/* your render code here */
	Rend(&r);


	/* clear render*/
	r.Exit();

	/*show */
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

	ReleaseDC(&memdc);
}
void CSideBar::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}

}