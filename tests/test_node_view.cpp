#include <afxwin.h>
#include "node.h"
#include "notenode.h"
#include "square.h"
#include "viewlayer.h"
#include "platform/cairorender.h"
#include "platform/charconverter.h"
#include <iostream>
#include "point.h"
#include "color.h"

class MyNode : public douml::Node
{
public:
    MyNode();
};

class MyLayer : public douml::ViewLayer
{
public:
    MyLayer();
    virtual void Draw(douml::Node* n);
private:
    douml::Shape* m_shape;
};
MyLayer::MyLayer()
{
    m_shape = new douml::Square(100);
}
void MyLayer::Draw(douml::Node* n)
{
    m_shape->DrawBackground(n);
}
/*------------ */
class MyLayer1 : public douml::ViewLayer
{
public:
    MyLayer1();
    virtual void Draw(douml::Node* n);
private:
    douml::Shape* m_shape;
};
MyLayer1::MyLayer1()
{
    m_shape = new douml::Square(100);
}
void MyLayer1::Draw(douml::Node* n)
{
    m_shape->DrawBorder(n);
}
/*----------- */
class MyLayer2 : public douml::ViewLayer
{
public:
    MyLayer2();
    virtual void Draw(douml::Node* n);
};
MyLayer2::MyLayer2()
{
}
void MyLayer2::Draw(douml::Node* n)
{
    douml::Render* r = n->GetRender();
    r->SetColor(n->GetTextColor());
    douml::Point t = n->GetLocationOnGraph();
    r->MoveTo(t.GetX(),t.GetY());
    r->ShowText("中文sfsdf");
    
}
/*----------- */
MyNode::MyNode()
{
    SetLocation(douml::Point(100,100));
    SetBackgroundColor(douml::Color(175,107,51));
    SetBorderColor(douml::Color(175,107,51));
    SetTextColor(douml::Color(255,0,0));
    SetViewLayers(new MyLayer,new MyLayer1,new MyLayer2);
}


class CMyWinApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};
CMyWinApp theApp;

class CMyFrameWnd:public CFrameWnd
{
protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
void CMyFrameWnd::OnPaint()
{
    CDC memdc;
    CBitmap bitmap;
    CRect rect;
    

    douml::NoteNode node1;
    douml::NoteNode* node2=new douml::NoteNode;

    CClientDC dc(this);
    
	GetClientRect(&rect);

    memdc.CreateCompatibleDC(&dc);

    bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    ::SelectObject(memdc.GetSafeHdc(), bitmap);
    ReleaseDC(&memdc);



    COLORREF crl = RGB(253,246,227);
    memdc.FillSolidRect(rect, crl);

    

    HDC hdc = memdc.GetSafeHdc();

    douml::CairoRender r;
    r.SetHDC(hdc);
    r.Init();

    node1.SetLocation(douml::Point(100,100));
    node2->SetLocation(douml::Point(50,100));
    node1.SetBackgroundColor(douml::Color(255,0,0));
    node1.SetRender(&r);
    node2->SetBackgroundColor(douml::Color(0,255,0));
    node2->SetTextColor(douml::Color(0,0,255));
    node2->SetRender(&r);
    node2->SetText("world");
    node2->SetParent(&node1);
    //node1.Draw();
    //node2.Draw();

	node1.SetText("hello");
	node1.Draw();

    /**
    r.MoveTo(10,10);
    r.LineTo(100,100);
    */
   /* cairorender need stroke before show */
    r.Exit();

    

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

    ReleaseDC(&memdc);
}
BOOL CMyFrameWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
BOOL CMyWinApp::InitInstance()
{
    CFrameWnd *pWnd = new CMyFrameWnd;
    pWnd->Create(NULL, "StatusBar");
    m_pMainWnd = pWnd;
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}
