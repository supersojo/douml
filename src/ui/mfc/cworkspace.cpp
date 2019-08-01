/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "cworkspace.h"
#include "ceditorpart.h"
#include "csidebar.h"
namespace douml
{

CWorkspace::CWorkspace()
{
	Create(NULL, L"douml");

	CEditorPart* ep = new CEditorPart(this);
	CSideBar* sb = new CSideBar(this);
	SetEditorPart(ep);
	SetSideBar(sb);
	ep->ShowWindow(SW_NORMAL);
	sb->ShowWindow(SW_NORMAL);
}
BEGIN_MESSAGE_MAP(CWorkspace,CWnd)
    ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CWorkspace::OnSize(UINT nType, int cx, int cy)
{
	CRect rect;
	CRect subRect;
	GetClientRect(&rect);


	CEditorPart* ep;
	CSideBar* sb;

	ep = dynamic_cast<CEditorPart*>(GetEditorPart());
	sb = dynamic_cast<CSideBar*>(GetSideBar());

	subRect.left = 0;
	subRect.right = rect.right - 300;// 300 for sidebar
	subRect.top = 0;
	subRect.bottom = rect.bottom;

	ep->MoveWindow(&subRect);

	subRect.left = rect.right - 300;
	subRect.right = rect.right;

	sb->MoveWindow(&subRect);

}
void CWorkspace::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 300;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

}