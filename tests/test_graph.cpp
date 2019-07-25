#include <afxwin.h>
#include "node.h"
#include "square.h"
#include "viewlayer.h"
#include "platform/cairorender.h"
#include "platform/charconverter.h"
#include <iostream>
#include "point.h"
#include "color.h"
#include "graph.h"
#include "notenode.h"
#include "edge.h"
#include "bentstyle.h"

/*global graph for test */
douml::Graph g_graph;

class CMyWinApp : public CWinApp
{
public:
    void InitGraphForTest();
    virtual BOOL InitInstance();
};
CMyWinApp theApp;

class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd() {
	}
    virtual void Render(douml::Render *r);

protected:
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags,CPoint point);
    DECLARE_MESSAGE_MAP()
private:
    douml::Node *m_selected_node;


};

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
ON_WM_PAINT()
ON_WM_ERASEBKGND()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CMyFrameWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    douml::Point t;
    douml::Node *n;

    t.SetX(point.x);
    t.SetY(point.y);

    n = g_graph.FindNode(t);

    if(!n) {
        douml::Node* tmp = new douml::NoteNode;
        tmp->SetBackgroundColor(douml::Color(255,0,0));
        g_graph.AddNode(tmp,&douml::Point(point.x,point.y));
    }
    m_selected_node = n;

}
void CMyFrameWnd::OnMouseMove(UINT nFlags,CPoint point)
{
    if(nFlags&MK_LBUTTON)
    {
        if(m_selected_node)
        {   
			m_selected_node->SetLocation(douml::Point(point.x, point.y));
			g_graph.SetUpdateEdges(true);
        }
    }
}

void CMyFrameWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_selected_node = nullptr;
}
void CMyFrameWnd::Render(douml::Render *r)
{
    g_graph.Draw(r);
}
void CMyFrameWnd::OnPaint()
{
    CDC memdc;
    CBitmap bitmap;
    CRect rect;

    CClientDC dc(this);

    GetClientRect(&rect);
    /*create memdc related 'dc'*/
    memdc.CreateCompatibleDC(&dc);
    /*create btimap dc */
    bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    ::SelectObject(memdc.GetSafeHdc(), bitmap);
    ReleaseDC(&memdc);

    /*fill background */
    COLORREF crl = RGB(253, 246, 227);
    memdc.FillSolidRect(rect, crl);

    HDC hdc = memdc.GetSafeHdc();

    /*init render */
    douml::CairoRender r;
    r.SetHDC(hdc);
    r.Init();

    /* your render code here */
    Render(&r);

    /* clear render*/
    r.Exit();

    /*show */
    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

    ReleaseDC(&memdc);
}
BOOL CMyFrameWnd::OnEraseBkgnd(CDC *pDC)
{
    /*must be true for good display */
    return TRUE;
}
void CMyWinApp::InitGraphForTest()
{
    douml::Graph &g = g_graph;

    douml::NoteNode *n1, *n2, *n3;

    n1 = new douml::NoteNode;
    n2 = new douml::NoteNode;
    n3 = new douml::NoteNode;

    n1->SetBackgroundColor(douml::Color(255, 0, 0));
    n1->SetText("");

    n2->SetBackgroundColor(douml::Color(0, 255, 0));
    n2->SetText("wewe");

    n3->SetBackgroundColor(douml::Color(0, 0, 255));
    n3->SetText("ilil");

    g.AddNode(n1, &douml::Point(100, 100));
    g.AddNode(n2, &douml::Point(200, 300));
    g.AddNode(n3, &douml::Point(50, 250));

    //douml::Edge *e = new douml::Edge;
    //e->SetStartNode(n1);
    //e->SetEndNode(n2);

    douml::Edge *e1 = new douml::Edge;
    e1->SetStartNode(n1);
    e1->SetEndNode(n3);

    //douml::Point t = n1->GetConnectionPoint(e);
    //douml::Point t1 = n2->GetConnectionPoint(e);

    //g.Connect(e, n1, t, n2, t1, nullptr, 0);

    douml::Point t2 = n1->GetConnectionPoint(e1);
    douml::Point t3 = n3->GetConnectionPoint(e1);

    g.Connect(e1, n1, t2, n3, t3, nullptr, 0);

    douml::Edge *e2 = new douml::Edge;
    e2->SetStartNode(n2);
    e2->SetEndNode(n3);
    douml::Point t4 = n2->GetConnectionPoint(e2);
    douml::Point t5 = n3->GetConnectionPoint(e2);

    g.Connect(e2, n2, t4, n3, t5, nullptr, 0);

    //e->SetBentStyle(&douml::BentStyle::VHV);
}
BOOL CMyWinApp::InitInstance()
{
    
    InitGraphForTest();
    CFrameWnd *pWnd = new CMyFrameWnd;
    pWnd->Create(NULL, L"douml");
    m_pMainWnd = pWnd;
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}
