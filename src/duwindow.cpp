/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "duwindow.h"

namespace douml
{

LPCTSTR DuWindow::g_duwindow_class = nullptr;

DuWindow::DuWindow() 
{
	CRect r;
    if(g_duwindow_class==nullptr){
        g_duwindow_class = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW),0,0);
    }
    
    r.left = CW_USEDEFAULT;
    r.top = CW_USEDEFAULT;
    r.bottom = CW_USEDEFAULT;
    r.right = CW_USEDEFAULT;

	CreateEx(0, g_duwindow_class,/*window name */0,/*window style */WS_OVERLAPPEDWINDOW,/*rect */CFrameWnd::rectDefault,/*parent */0,/*id */0,/*context */0);
	
}
DuWindow::DuWindow(DuWindow* parent) 
{
	CRect r;
    if(g_duwindow_class==nullptr){
        g_duwindow_class = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,(HCURSOR)IDC_ARROW,0,0);
    }
    
    Create(g_duwindow_class,/*window name */0,/*window style */WS_CHILD,/*rect */r,/*parent */parent,/*id */0,/*context */0);
}
DuWindow::DuWindow(CWnd* parent)
{
	CRect r;
	if (g_duwindow_class == nullptr) {
		g_duwindow_class = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, (HCURSOR)IDC_ARROW, 0, 0);
	}

	Create(g_duwindow_class,/*window name */0,/*window style */WS_CHILD,/*rect */r,/*parent */parent,/*id */0,/*context */0);
}
void DuWindow::PostNcDestroy()
{
    delete this;
}
void DuWindow::ShowWindow()
{
    CWnd::ShowWindow(SW_SHOW);
    CWnd::UpdateWindow();
}
void DuWindow::ShowWindow(bool show)
{
    if(show){
        CWnd::ShowWindow(SW_SHOW);
        CWnd::UpdateWindow();
    }else
    {
        CWnd::ShowWindow(SW_HIDE);
    }
    
}
DuWindow::~DuWindow()
{

}

}
