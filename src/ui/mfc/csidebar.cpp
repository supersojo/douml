/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "csidebar.h"
#include "cworkspace.h"
//#include <windows.h>
namespace douml
{

CSideBar::CSideBar()
{

}
CSideBar::CSideBar(CWorkspace* ws):SideBar(ws)
{
    RECT rect;
    Create(L"static",NULL,WS_CHILD|WS_VSCROLL|WS_THICKFRAME,rect,ws,-1,NULL);
}
BEGIN_MESSAGE_MAP(CSideBar,CWnd)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()

void CSideBar::OnSize(UINT nType, int cx, int cy)
{

}
void CSideBar::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}

}