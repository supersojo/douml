/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_LINE_H
#define DU_LINE_H
#include "douml.h"

/*Line with direction from A->B */
namespace douml
{
    class Point;
class DU_API Line 
{
public:
    Line();
    Point GetStart();
    Point GetEnd();
    void SetStart(Point& p);
    void SetEnd(Point& p);
    ~Line();
private:
    Point* m_start;
    Point* m_end;
};

}
#endif
