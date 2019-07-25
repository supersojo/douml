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
#include "classnode.h"
#include "interfacenode.h"
#include "packagenode.h"
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
        m_selected_node = nullptr;
        m_start_node = nullptr;
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
    douml::Node *m_start_node;




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

    if(m_selected_node)
        m_selected_node->SetSelected(false);
        
    n = g_graph.FindNode(t);
    if(n) {
        m_selected_node = n;
        n->SetSelected(true);
        m_start_node = n;
        //dynamic_cast<douml::ClassNode*>(m_start_node)->SetName("ksjdfksdjfsdjf");
    }
    else {
        douml::ClassNode* cn = new douml::ClassNode;
        cn->SetBackgroundColor(douml::Color(253, 246, 227));
        cn->SetBorderColor(douml::Color(253, 0, 0));
        cn->SetSelected(true);
        m_selected_node = cn;
        g_graph.AddNode(cn,&douml::Point(point.x,point.y));
    }
}
void CMyFrameWnd::OnMouseMove(UINT nFlags,CPoint point)
{

}

void CMyFrameWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    douml::Point t;
    douml::Node *n;

    t.SetX(point.x);
    t.SetY(point.y);
    n = g_graph.FindNode(t);
    if(m_start_node)
    {
        if(n)
        {
            douml::Edge* e = new douml::Edge;
            e->SetStartNode(m_start_node);
            e->SetEndNode(n);
            douml::Point t1 = m_start_node->GetConnectionPoint(e);
            douml::Point t2 = n->GetConnectionPoint(e);
            g_graph.Connect(e,m_start_node,t1,n,t2,nullptr,0);
        }
        m_start_node = nullptr;
    }
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
    r.SetLineWidth(0.5);
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

    douml::PackageNode *n1;


    n1 = new douml::PackageNode();


    n1->SetBackgroundColor(douml::Color(253, 246, 227));
    n1->SetBorderColor(douml::Color(253, 0, 0));
    //n1->SetName("Hello");

    std::vector<du_char*> v;
    v.push_back("public void a()");
    v.push_back("public void bar()"); 
    v.push_back("sdfsdfsdfsdlflsdfjsdjfsdjlfjsdkljfsjflkjlfjl"); 
    //n1->SetContent(v);

    g.AddNode(n1, &douml::Point(100, 100));

    //e->SetBentStyle(&douml::BentStyle::VHV);
}
BOOL CMyWinApp::InitInstance()
{
    
    InitGraphForTest();
    CFrameWnd *pWnd = new CMyFrameWnd;
    pWnd->Create(NULL, "douml");
    m_pMainWnd = pWnd;
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}
