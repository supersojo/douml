/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "notenode.h"
#include "viewlayer.h"
#include "node.h"
#include "nodeview.h"
#include "shape.h"
#include "point.h"
#include "render.h"
#include "rect.h"
#include "color.h"
namespace douml
{

class NoteShape : public Shape
{
public:
    NoteShape();
	virtual ~NoteShape();
    virtual void DrawBackground(Node *n);
    virtual void DrawBorder(Node *n);

    static du_int MIN_WIDTH;
    static du_int MIN_HEIGHT;
    static du_int GAP_SIZE;

};

du_int NoteShape::MIN_WIDTH = 80;
du_int NoteShape::MIN_HEIGHT = 48;
du_int NoteShape::GAP_SIZE = 8;

NoteShape::NoteShape()
{
    SetWidth(MIN_WIDTH);
    SetHeight(MIN_HEIGHT);
}
NoteShape::~NoteShape()
{

}
void NoteShape::DrawBackground(Node *n)
{
    Render* r = n->GetRender();
    Point t = n->GetLocationOnGraph();
    
    

    du_int x = t.GetX();
    du_int y = t.GetY();

	r->SetColor(Color(255, 228, 181));
    r->MoveTo(x,y);
    r->LineTo(x+GetWidth()-GAP_SIZE,y);
    r->LineTo(x+GetWidth(),y+GAP_SIZE);
    r->LineTo(x+GetWidth(),y+GetHeight());
    r->LineTo(x,y+GetHeight());
    r->LineTo(x,y);
    r->Fill();

	r->SetColor(Color(255, 255, 255));
    r->MoveTo(x+GetWidth()-GAP_SIZE,y);
    r->LineTo(x+GetWidth(),y+GAP_SIZE);
    r->LineTo(x+GetWidth()-GAP_SIZE,y+GAP_SIZE);
    r->LineTo(x+GetWidth()-GAP_SIZE,y);
    r->Fill();

}
void NoteShape::DrawBorder(Node *n)
{
	Render* r = n->GetRender();
	Point t = n->GetLocationOnGraph();



	du_int x = t.GetX();
	du_int y = t.GetY();

	r->SetColor(Color(0, 0, 0));
	r->MoveTo(x, y);
	r->LineTo(x + GetWidth() - GAP_SIZE, y);
	r->LineTo(x + GetWidth(), y + GAP_SIZE);
	r->LineTo(x + GetWidth(), y + GetHeight());
	r->LineTo(x, y + GetHeight());
	r->LineTo(x, y);
	r->Stroke();

	r->SetColor(Color(0, 0, 0));
	r->MoveTo(x + GetWidth() - GAP_SIZE, y);
	r->LineTo(x + GetWidth(), y + GAP_SIZE);
	r->LineTo(x + GetWidth() - GAP_SIZE, y + GAP_SIZE);
	r->LineTo(x + GetWidth() - GAP_SIZE, y);
	r->Stroke();
}
class ContentLayer : public ViewLayer
{
public:
    ContentLayer();
	virtual ~ContentLayer();
    ContentLayer(NoteNode* n);
    virtual void Draw(douml::Node* n);
private:
    NoteNode* m_node;
};
ContentLayer::ContentLayer()
{
    m_node = nullptr;
}
ContentLayer::~ContentLayer()
{

}
ContentLayer::ContentLayer(NoteNode* n)
{
    m_node = n;
}
void ContentLayer::Draw(douml::Node* n)
{
#if 0
    /*assert n==m_node */

    Point t = n->GetLocationOnGraph();
    Render* r = n->GetRender();
    r->SetColor(n->GetTextColor());
    r->MoveTo(t.GetX()+20,t.GetY()+20);
    r->ShowText(m_node->GetText());
#endif
	du_int x_bearing;
	du_int y_bearing;
    du_int delta_x = 0;
    du_int delta_y = 0;
    du_int pos = 0;
    du_int w0 = 0, h0 = 0;
	
	Render* r = n->GetRender();

    Rect rect;
    std::vector<du_char*>::iterator i;
    rect = m_node->GetContentRect();
    if(rect.GetH()<NoteShape::MIN_HEIGHT)
    {
        delta_y = (NoteShape::MIN_HEIGHT - rect.GetH())/2;
    }
    rect.SetY(rect.GetY()+delta_y);

    pos = 0;
    for(i=m_node->GetContent()->begin();i!=m_node->GetContent()->end();i++)
    {
        r->TextBoxSize((*i),w0,h0, x_bearing, y_bearing);
        r->SetColor(n->GetTextColor());
        r->MoveTo(rect.GetX() + NoteNode::GAP_X, rect.GetY() + pos + NoteNode::GAP_Y+abs(y_bearing));
        r->ShowText(*i);
        pos = pos + h0 + NoteNode::GAP_Y;
    }

}
/*-------------------------------------------------------- */
du_int NoteNode::GAP_X = 4;
du_int NoteNode::GAP_Y = 4;

NoteNode::NoteNode()
{
	BackgroundLayer* background = new BackgroundLayer;
	background->SetShape(new NoteShape);

	BorderLayer* border = new BorderLayer;
	border->SetShape(new NoteShape);

    SetViewLayers(background,border,new ContentLayer(this));

    m_text = nullptr;
    m_content = new std::vector<du_char*>;
    m_changed = false;
    m_contentRect = new Rect;
}
std::vector<du_char*>* NoteNode::GetContent()
{
    return m_content;
}
void NoteNode::SetContent(std::vector<du_char*>& content)
{
    m_content->clear();

    std::vector<du_char *>::iterator i;
    for (i = content.begin(); i != content.end(); i++)
    {
        m_content->push_back(*i);
    }
    SetChanged(true);
}
NoteNode::~NoteNode()
{
    delete m_content;
    delete m_contentRect;
}
Rect NoteNode::GetContentRect()
{
    return *m_contentRect;
}
du_char* NoteNode::GetText()
{
    return m_text;
}
bool NoteNode::GetChanged()
{
    return m_changed;
}
void NoteNode::SetChanged(bool c)
{
    m_changed = c;
}
void NoteNode::UpdateMinRects()
{
	du_int x_bearing;
	du_int y_bearing;

    du_int x,y;

    Render *r = GetRender();
    du_int rows1 = 0;
    du_int w0, h0;
    du_int w, h;
    w = 0;
    h = 0;

    x = GetLocationOnGraph().GetX();
    y = GetLocationOnGraph().GetY();
    
    std::vector<du_char *>::iterator i;
    for (i = m_content->begin(); i != m_content->end(); i++)
    {
        if (*i)
        {
            r->TextBoxSize((*i), w0, h0, x_bearing, y_bearing);
            w = w0 > w ? w0 : w;
            h += h0;
            rows1 += h0 + GAP_Y;
        }
    }

    if(rows1>0)
        rows1 += GAP_Y;
    
    m_contentRect->SetW(w+2*GAP_X);
    m_contentRect->SetH(rows1);
    m_contentRect->SetX(x);
    m_contentRect->SetY(y);

}
void NoteNode::NotifyCallback()
{
    if (!GetChanged())
        return;

	//GetRender()->SetFont("Microsoft YaHei UI");

    ViewLayer *v;

    v = GetView()->GetContentLayer();

    UpdateMinRects();

    /*tell viewlayer size changed */
    v->SetMinW(m_contentRect->GetW());
    v->SetMinH(m_contentRect->GetH());

    SetChanged(false);
}
void NoteNode::SetText(du_char* t)
{
    m_text = t;

    SetChanged(true);
	
}

} // namespace douml