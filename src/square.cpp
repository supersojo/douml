/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "square.h"
#include "render.h"
#include "node.h"
#include "point.h"
#include "color.h"

namespace douml
{

Square::Square()
{
    m_z = 0;
}
Square::Square(du_int z)
{
    m_z = z;
}
void Square::DrawBackground(Node* n)
{
    Point p = n->GetLocationOnGraph();
	Render* r = n->GetRender();
	r->MoveTo(p.GetX(), p.GetY());

	r->LineTo(p.GetX()+m_z, p.GetY()+0);
	r->LineTo(p.GetX()+m_z, p.GetY()+m_z);
	r->LineTo(p.GetX()+0, p.GetY()+m_z);
	r->LineTo(p.GetX()+0,p.GetY()+0);

	/*set color */
	Color c = n->GetBackgroundColor();
	r->SetColor(c);
	r->Fill();

}
void Square::DrawBorder(Node* n)
{
	Point p = n->GetLocationOnGraph();
	Render* r = n->GetRender();
	r->MoveTo(p.GetX(), p.GetY());

	r->LineTo(p.GetX()+m_z, p.GetY()+0);
	r->LineTo(p.GetX()+m_z, p.GetY()+m_z);
	r->LineTo(p.GetX()+0, p.GetY()+m_z);
	r->LineTo(p.GetX()+0,p.GetY()+0);

	/*set color */
	Color c = n->GetBorderColor();
	r->SetColor(c);

	r->Stroke();
}

} // namespace douml