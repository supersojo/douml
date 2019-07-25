/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef DU_COLOR_H
#define DU_COLOR_H

#include "douml.h"
#include <string>

namespace douml
{

class DU_API Color
{
public:
    Color();
    Color(du_int r, du_int g, du_int b);
    du_int GetR();
    du_int GetG();
    du_int GetB();
    void SetR(du_int r);
    void SetG(du_int g);
    void SetB(du_int b);
    void Set(Color &c);
    std::string ToString();

private:
    du_int m_r;
    du_int m_g;
    du_int m_b;
};

} // namespace douml

#endif
