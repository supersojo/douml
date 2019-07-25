/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "platform/cairorender.h"
#include "color.h"

namespace douml
{

CairoRender::CairoRender()
{
    m_surface = nullptr;
    m_cr = nullptr;
    m_hdc = 0;
}
CairoRender::~CairoRender()
{

}

void CairoRender::Init()
{
    m_surface = cairo_win32_surface_create(m_hdc);
    m_cr = cairo_create(m_surface);
}
HDC CairoRender::GetHDC()
{
    return m_hdc;
}
void CairoRender::SetHDC(HDC hdc)
{
    m_hdc = hdc;
}
void CairoRender::MoveTo(du_int x, du_int y)
{
    cairo_move_to(m_cr, x, y);
}
void CairoRender::LineTo(du_int x, du_int y)
{
    cairo_line_to(m_cr, x, y);
}
void CairoRender::CurveTo(du_int x1,du_int y1,du_int x2,du_int y2,du_int x3,du_int y3)
{
    cairo_curve_to(m_cr,x1,y1,x2,y2,x3,y3);
}
void CairoRender::Stroke()
{
    cairo_stroke(m_cr);
}
void CairoRender::Fill()
{
    cairo_fill(m_cr);
}
void CairoRender::SetColor(Color& c)
{
    cairo_set_source_rgba(m_cr,c.GetR()/256.0,c.GetG()/256.0,c.GetB()/256.0,/*alpha*/1.0);
}
void CairoRender::SetDash(bool dash)
{
    static const du_float dashed[] = { 4.0, 1.0};
    static du_int len = sizeof (dashed) / sizeof (dashed[0]);
    if(dash)
        cairo_set_dash (m_cr, dashed, len, 0);
    else
        cairo_set_dash (m_cr, dashed, 0, 0);
}
void CairoRender::SetLineWidth(du_float w)
{
    cairo_set_line_width(m_cr,w);
}
void CairoRender::SetFont(du_char* family)
{
    cairo_select_font_face(m_cr, family, CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_NORMAL);
}
void CairoRender::SetFontSize(du_float size)
{
    cairo_set_font_size(m_cr,size);
}
void CairoRender::ShowText(du_char* t)
{
    /* 
    cairo_select_font_face(m_cr, "Microsoft YaHei UI", CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
    */
    cairo_show_text(m_cr,t);
}
void CairoRender::TextBoxSize(du_char* t,du_int& w,du_int& h,du_int& x_bearing,du_int& y_bearing)
{
    cairo_text_extents_t te;

    cairo_text_extents (m_cr, t, &te);
	cairo_text_extents(m_cr, t, &te);
    //w = (du_int)te.x_advance;
    w = (du_int)te.width;
    h = (du_int)te.height;
	x_bearing = (du_int)te.x_bearing;
	y_bearing = (du_int)te.y_bearing;
}
void CairoRender::Exit()
{
    cairo_destroy(m_cr);
    cairo_surface_destroy(m_surface);
    cairo_debug_reset_static_data();/*free context in debug mode*/
}

}