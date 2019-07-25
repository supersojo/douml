/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_SHAPE_H
#define DU_SHAPE_H
#include "douml.h"

namespace douml
{
    class Node;
}
namespace douml
{
class DU_API Shape
{
public:
    virtual void DrawBackground(Node* n);
    virtual void DrawBorder(Node* n);
    du_int GetWidth();
    du_int GetHeight();
    void SetWidth(du_int w);
    void SetHeight(du_int h);
private:
    du_int m_width;
    du_int m_height;
};
} // namespace douml
#endif
