/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_SIDEBAR_H
#define DU_SIDEBAR_H
#include "douml.h"

namespace douml 
{
    class ToolItem;
    class Workspace;
class DU_API SideBar {
public:
    SideBar();
	~SideBar();
    SideBar(Workspace* ws);
    virtual void CreateSideBar();
    virtual void OnXXXX();
    virtual void OnToolItemClicked(ToolItem *item);
private:
    Workspace* m_workspace;
};
}
#endif