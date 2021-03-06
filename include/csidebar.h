/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "sidebar.h"

namespace douml
{
	class CWorkspace;
	class Render;
class CSideBar: public CWnd, public SideBar
{
public:
    CSideBar();/*should not used */
    CSideBar(CWorkspace* ws);
	void Rend(Render* r);
private:
	void RenderStandardMenu(Render* r);
	void RenderGraphMenu(Render* r);
	CPoint m_ClickPoint;
	void HandleLButtonClick(CPoint& point);
protected:
    //afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcDestroy();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};

}