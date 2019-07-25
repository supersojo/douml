/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_RECT_H
#define DU_RECT_H
#include "douml.h"
namespace douml
{
class DU_API Rect
{
public:
    Rect();
    Rect& operator=( Rect& r);
    void SetX(du_int x);
    void SetY(du_int y);
    void SetW(du_int w);
    void SetH(du_int h);
    du_int GetX();
    du_int GetY();
    du_int GetW();
    du_int GetH();
private:
    du_int m_x;
    du_int m_y;
    du_int m_w;
    du_int m_h;
};

} // namespace douml
#endif