/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_RENDER_H
#define DU_RENDER_H

#include "douml.h"

namespace douml
{
	class Color;
class DU_API Render
{
public:
    virtual void Init();
    virtual void MoveTo(du_int x,du_int y);
    virtual void LineTo(du_int x,du_int y);
    virtual void CurveTo(du_int x1,du_int y1,du_int x2,du_int y2,du_int x3,du_int y3);
    virtual void Stroke();
    virtual void SetColor(Color& c);
    virtual void SetDash(bool dash);/*for dotted line */
    virtual void SetLineWidth(du_float w);
    virtual void SetFont(du_char* family);
    virtual void SetFontSize(du_float size);
    virtual void ShowText(du_char* t);
    virtual void TextBoxSize(du_char* t,du_int& w,du_int& h,du_int& x_bearing,du_int& y_bearing);
    virtual void Fill();
    virtual void FillRect(du_int x,du_int y,du_int w,du_int h);
    virtual void Exit();
};

} // namespace douml
#endif
