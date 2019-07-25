/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "workspace.h"

namespace douml
{
/*single derivation */
class CWorkspaceBase : public workspace
{

};
class CWorkspace : public CWnd
{
public:
    CWorkspace();
protected:
    //afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    //afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};

}