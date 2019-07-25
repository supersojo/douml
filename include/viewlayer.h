/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_VIEWLAYER_H
#define DU_VIEWLAYER_H

#include "douml.h"

namespace douml
{
class Node;
class Rect;
class Shape;
}

namespace douml
{
class DU_API ViewLayer
{
public:
    ViewLayer();
	virtual ~ViewLayer();
    ViewLayer(du_int w, du_int h, du_int minw, du_int minh);
    du_int GetW();
    du_int GetH();
    du_int GetMinW();
    du_int GetMinH();
    virtual void Draw(Node* n);
    ViewLayer *GetParent();
    void SetParent(ViewLayer &p);
    ViewLayer *GetChild();
    void SetChild(ViewLayer &c);
    void SetW(du_int w);
    void SetH(du_int h);
    void SetMinW(du_int minw);
    void SetMinH(du_int minh);
    virtual Rect GetBounds();
    virtual void Refresh();
    virtual void RefreshUp();
    virtual void RefreshDown();
private:
    du_int m_w;
    du_int m_h;
    du_int m_minw;
    du_int m_minh;
    ViewLayer *m_parent;
    ViewLayer *m_child;
};
class DU_API BackgroundLayer : public ViewLayer 
{
public:
    BackgroundLayer();
    virtual void Draw(douml::Node *n);
    virtual void RefreshUp();
    virtual void RefreshDown();
    virtual Rect GetBounds();
    virtual ~BackgroundLayer();
    Shape* GetShape();
    void SetShape(Shape* s);
private:
    Shape* m_shape;
};
class BorderLayer : public ViewLayer
{
public:
    BorderLayer();
	virtual ~BorderLayer();
    virtual void Draw(douml::Node *n);
    virtual void RefreshUp();
    virtual void RefreshDown();
    virtual Rect GetBounds();
    Shape* GetShape();
    void SetShape(Shape* s);
private:
    Shape *m_shape;
};

} // namespace douml

#endif
