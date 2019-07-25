/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_WORKSPACE_H
#define DU_WORKSPACE_H
#include "douml.h"
#include "duwindow.h"

#include <afxwin.h>
#include <afxole.h>
#include <afxtabctrl.h>
#include <vector>

namespace douml
{
class EditorPart;
class SideBar;
class WorkspacePanel;
class GreetingPanel;
class EditorPartPanel;
class SideBarPanel;
class Render;
class Graph;
class TitleButton;
class Node;
class Point;

class DU_API CDuTabCtrl : public CMFCTabCtrl
{
public:
    void SetEditorPart(EditorPart* ep);
protected:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
private:
    EditorPart* m_editorPart;
};
class DU_API Workspace
{
public:
    Workspace();
    ~Workspace();
    EditorPart *GetEditorPart();
    SideBar *GetSideBar();
    DuWindow *GetWindow();
    void GetGraphs(std::vector<Graph*>& graphs);
    void OnNewGraph(Graph* g);
    void OnRemoveGraph(Graph* g);
    GreetingPanel* GetGreeting();
    Graph* GetActiveGraph();
private:
    EditorPart *m_editorPart;
    SideBar *m_sideBar;
    WorkspacePanel *m_window;
    std::vector<Graph*> *m_graphs;
    GreetingPanel* m_greeting;
};
class DU_API EditorPart
{
public:
    EditorPart();
    EditorPart(DuWindow *parent);
    DuWindow *GetWindow();
    void OnNewGraph(Graph* g);
    void SetWorkspace(Workspace* ws);
    Workspace* GetWorkspace();
    Graph* GetActiveGraph();
private:
    EditorPartPanel *m_window;
    Workspace* m_workspace;
};
class DU_API SideBar
{
public:
    SideBar();
    SideBar(DuWindow *parent);
    DuWindow *GetWindow();
    void SetWorkspace(Workspace* ws);
    Workspace* GetWorkspace();
private:
    SideBarPanel *m_window;
    Workspace* m_workspace;
};
class DU_API WorkspacePanel : public DuWindow
{
public:
    WorkspacePanel();
    void SetWorkspace(Workspace *w);
    Workspace *GetWorkspace();
    virtual void PostNcDestroy();

protected:
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
private:
    Workspace *m_workspace;
};
class DU_API CanvasWindow : public DuWindow 
{
public:
    CanvasWindow();
    virtual ~CanvasWindow();
    CanvasWindow(DuWindow *parent);
    CanvasWindow(CWnd *parent);
    void SetGraph(Graph* g);
    Graph* GetGraph();
    void Render(Render *r);
    virtual void PostNcDestroy();
    void DrawGridSticker(douml::Render*r);
protected:
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_MESSAGE_MAP()
private:
    Graph* m_graph;

	/*for node select operation*/
	Node* m_selectNode;
	/*for edge add operation*/
	Node* m_startNode;
	Node* m_endNode;
	Point* m_startPoint;
	Point* m_endPoint;
	Point* m_origin;
};
class DU_API GreetingPanel : public DuWindow 
{
public:
    GreetingPanel();
    GreetingPanel(DuWindow *parent);
    void SetWorkspace(Workspace* ws);
protected:
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
private:
    Workspace* m_workspace;
};
class DU_API EditorPartPanel : public DuWindow
{
public:
    EditorPartPanel();
    EditorPartPanel(DuWindow *parent);
    void SetEditorPart(EditorPart *e);
    EditorPart *GetEditorPart();
    void Render(Render *r);
    void InitGraphForTest(Graph *g);
    virtual void PostNcDestroy();
    void OnNewGraph(Graph* g);
    Graph* GetActiveGraph();
protected:
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
private:
    EditorPart *m_editorPart;
	//CMFCTabCtrl *m_tabs;
    CDuTabCtrl* m_tabs;
};
class DU_API SideBarPanel : public DuWindow
{
public:
    SideBarPanel();
    SideBarPanel(DuWindow *parent);
    void SetSideBar(SideBar *s);
    SideBar *GetSideBar();
    void Render(Render* r);
    virtual void PostNcDestroy();
protected:
    afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    DECLARE_MESSAGE_MAP()
private:
    SideBar *m_sideBar;
    Graph* m_graph;
    TitleButton* m_titleButton;
    /*for scroll */
    CScrollBar* m_scrollBar;
};

class TitleButton : public CButton 
{
public:
    TitleButton();
    TitleButton(DuWindow* parent);
    TitleButton(CWnd* parent);
    void Render(Render* r,LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void  OnMouseMove(UINT   nFlags, CPoint   point);
	afx_msg void  OnMouseHover(UINT   nFlags, CPoint   point);
    afx_msg void  OnMouseLeave();
    bool GetToggled();
    DECLARE_MESSAGE_MAP()
private:
    bool m_toggled;
    bool m_tracking;
};
#if 0
class DU_API ToolPanel : public DuWindow
{
public:
    ToolPanel();
private:
    bool m_toggled;
    CWnd* m_titleButton;
};
#endif
} // namespace douml

#endif
