/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_BENTSTYLE_H
#define DU_BENTSTYLE_H
#include "douml.h"
#include <vector>

namespace douml
{
	class Point;
class DU_API BentStyle
{
public:
    BentStyle();
    BentStyle(du_char* n);
    BentStyle* Clone();
    du_char* GetName();
    void SetName(du_char* n);
    void GetStraightPath(std::vector<Point> &path, Point &s, Point &e);
    void GetFreePath(std::vector<Point> &path, std::vector<Point> &src);
    void GetHVPath(std::vector<Point> &path, Point &s, Point &e);
    void GetVHPath(std::vector<Point> &path, Point &s, Point &e);
    void GetHVHPath(std::vector<Point> &path, Point &s, Point &e);
    void GetVHVPath(std::vector<Point> &path, Point &s, Point &e);
    static BentStyle STRAIGHT;
    static BentStyle FREE;
    static BentStyle HV;
    static BentStyle VH;
    static BentStyle HVH;
    static BentStyle VHV;

    static const int MIN_SEGMENT = 15;
    static const int SELF_WIDTH = 30;
    static const int SELF_HEIGHT = 25;

private:
    du_char* m_name;
};
} // namespace douml

#endif
