/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_ARROWHEAD_H
#define DU_ARROWHEAD_H

#include "douml.h"

namespace douml
{
class Point;
class Color;
class Render;

class DU_API ArrowHead
{
public:
    ArrowHead();
    virtual void Draw(Render* r,Point& p,Point& q);
    Color& GetBorderColor();
    Color& GetFillColor();
    void SetBorderColor(Color&c);
    void SetFillColor(Color&c);
	virtual ~ArrowHead();
    du_int GetArroweLength();
    void SetArrowLength(du_int l);
    static du_float ARROW_ANGLE;
    static du_float ARROW_LENGTH;
protected:
    du_float CalculateAngle(Point &p, Point &q);
    void Transform(Point& p,du_float angle);
private:
    Color* m_border;
    Color* m_fill;
    du_int m_arrowLength;
};

} // namespace douml

#endif
