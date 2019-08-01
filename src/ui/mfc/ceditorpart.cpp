/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "ceditorpart.h"
#include "cworkspace.h"
//#include <windows.h>
namespace douml
{

CEditorPart::CEditorPart()
{

}
CEditorPart::CEditorPart(CWorkspace* ws):EditorPart(ws)
{
    RECT rect;
    Create(L"static",NULL,WS_CHILD|WS_HSCROLL|WS_VSCROLL|WS_THICKFRAME,rect,ws,-1,NULL);
}
BEGIN_MESSAGE_MAP(CEditorPart,CWnd)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()

void CEditorPart::OnSize(UINT nType, int cx, int cy)
{

}
void CEditorPart::OnNcDestroy()
{
	CWnd::OnNcDestroy();/*must call Base class OnNCDestroy */
	delete this;
}

}