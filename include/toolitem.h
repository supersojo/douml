/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_TOOLITEM_H
#define DU_TOOLITEM_H
#include "douml.h"
namespace douml
{
    class Color;
    class Render;
    class Point;
class DU_API ToolItem
{
public:
    ToolItem();
    ToolItem(du_char* n);
    virtual ~ToolItem();

    virtual ToolItem* Clone();

    Color GetBackgroundColor();
    Color GetBorderColor();
    Color GetTextColor();
    void SetBackgroundColor(Color&c);
    void SetBorderColor(Color&c);
    void SetTextColor(Color&c);

    du_char* GetName();
    void SetName(du_char* n);

    bool Contains(Point& t);

    bool GetSelected();
    void SetSelected(bool s);

    Point GetLocation();
    void SetLocation(Point&t);

    virtual void Draw(Render* r);
    virtual void DrawIcon(Render* r);
    

    static du_int TOOL_WIDTH;
    static du_int TOOL_HEIGHT;
private:
    Color* m_backgroundColor;
    Color* m_textColor;
    Color* m_borderColor;
    du_char* m_name;
    bool m_selected;
    Point* m_location;
};
/*---------------------------------------------------- */
class DU_API SelectNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~SelectNodeItem();
private:
    void FillRect(Render* r,du_int x,du_int y);
};
/*----------------------------------------------------- */
class DU_API NoteNodeItem : public ToolItem 
{
public:
    virtual void DrawIcon(Render* r);
    virtual ToolItem* Clone();
    virtual ~NoteNodeItem();
};
/*------------------------------------------------------ */
class DU_API NoteEdgeItem : public ToolItem 
{
public:
    virtual ToolItem* Clone();
    virtual void DrawIcon(Render* r);
    virtual ~NoteEdgeItem();

};
/*-------------------------------------------------------- */
}
#endif
