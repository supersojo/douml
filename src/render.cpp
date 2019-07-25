/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "render.h"

namespace douml
{

void Render::Init()
{
}
void Render::Exit()
{
}
void Render::Stroke()
{
}
void Render::Fill()
{
}
void Render::FillRect(du_int x,du_int y,du_int w,du_int h)
{
    MoveTo(x,y);
    LineTo(x+w,y);
    LineTo(x+w,y+h);
    LineTo(x,y+h);
	LineTo(x, y);
    Fill();
}
void Render::SetColor(Color& c)
{

}
void Render::SetDash(bool dash)
{

}
void Render::SetLineWidth(du_float w)
{
    
}
void Render::MoveTo(du_int x, du_int y)
{
}
void Render::LineTo(du_int x, du_int y)
{
}
void Render::CurveTo(du_int x1,du_int y1,du_int x2,du_int y2,du_int x3,du_int y3)
{

}
void Render::SetFont(du_char* family)
{

}
void Render::SetFontSize(du_float size)
{

}
void Render::ShowText(du_char* t)
{

}
void Render::TextBoxSize(du_char* t,du_int& w,du_int& h,du_int& x_bearing,du_int& y_bearing)
{

}

} // namespace douml