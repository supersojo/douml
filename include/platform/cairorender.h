/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_CAIRORENDER_H
#define DU_CAIRORENDER_H

#include "douml.h"
#include "render.h"

#ifdef _MSC_VER
#include <windows.h>
#endif

#ifdef _MSC_VER
#include "cairo-win32.h"
#endif

namespace douml
{
	class Color;
class DU_API CairoRender : public Render
{
public:
    CairoRender();
    virtual ~CairoRender();
    virtual void Init();
    virtual void MoveTo(du_int x,du_int y);
    virtual void LineTo(du_int x,du_int y);
    virtual void CurveTo(du_int x1,du_int y1,du_int x2,du_int y2,du_int x3,du_int y3);
    virtual void Stroke();
    virtual void SetColor(Color& c);
    virtual void SetDash(bool dash);
    virtual void SetLineWidth(du_float w);
    virtual void SetFont(du_char* family);
    virtual void SetFontSize(du_float size); 
    virtual void ShowText(du_char* t);
    virtual void TextBoxSize(du_char* t,du_int& w,du_int& h,du_int& x_bearing,du_int& y_bearing);
    virtual void Fill();
    virtual void Exit();
#ifdef _MSC_VER
    HDC GetHDC();
    void SetHDC(HDC hdc);
#endif
private:
    cairo_surface_t *m_surface;
    cairo_t *m_cr;
#ifdef _MSC_VER
    HDC m_hdc;
#endif
};

} // namespace douml
#endif
