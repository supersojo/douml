/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "sidebar.h"
#include "workspace.h"
#include "toolitem.h"
#include "graph.h"
namespace douml
{
SideBar::SideBar()
{
    m_workspace = nullptr;
}
SideBar::SideBar(Workspace* ws)
{
    m_workspace = ws;
	ws->SetSideBar(this);
}
SideBar::~SideBar()
{
}
void SideBar::CreateSideBar()
{

}
void SideBar::OnXXXX()
{
    
}
void SideBar::OnToolItemClicked(ToolItem *item)
{


}

}