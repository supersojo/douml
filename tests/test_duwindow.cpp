#include <afxwin.h>
#include <afxvisualmanager.h>
#include "duwindow.h"
#include "workspace.h"

class CMyWinApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};
CMyWinApp theApp;
#if 0
class CMyFrameWnd:public CFrameWnd
{
public:
    virtual void Render(douml::Render* r);
protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
void CMyFrameWnd::Render(douml::Render* r)
{
    douml::DiamondArrowHead ah;
    ah.SetBorderColor(douml::Color(255,0,0));
    ah.SetFillColor(douml::Color(255,0,0));

    r->SetColor(douml::Color(255,0,0));
    r->MoveTo(100,200);
    r->LineTo(200,500);
    r->Stroke();
    ah.Draw(r, douml::Point(100, 200), douml::Point(200, 500));

    douml::TriangleArrowHead ah1;
    ah1.SetBorderColor(douml::Color(255,0,0));
    ah1.SetFillColor(douml::Color(255,0,0));

    r->SetColor(douml::Color(255,0,0));
    r->MoveTo(400,100);
    r->LineTo(200,500);
    r->Stroke();
    ah1.Draw(r, douml::Point(400, 100), douml::Point(200, 500));

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
    COLORREF crl = RGB(253,246,227);
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
BOOL CMyFrameWnd::OnEraseBkgnd(CDC* pDC)
{
    /*must be true for good display */
	return TRUE;
}
#endif

BOOL CMyWinApp::InitInstance()
{

    douml::Workspace* workspace = new douml::Workspace;
    douml::DuWindow* w = workspace->GetWindow();

	m_pMainWnd = w;
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    w->ShowWindow();

    return TRUE;
}
int CMyWinApp::ExitInstance()
{
    CMFCVisualManager::DestroyInstance( TRUE );
	//delete m_pMainWnd;
    return CWinApp::ExitInstance();
}
