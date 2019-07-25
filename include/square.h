/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_SQUARE_H
#define DU_SQUARE_H

#include "douml.h"
#include "shape.h"
namespace douml {
class DU_API Square : public Shape {
public:
    Square();
    Square(du_int z); 
    virtual void DrawBackground(Node* n);
    virtual void DrawBorder(Node* n);
private:
    du_int m_z;
};
}
#endif
