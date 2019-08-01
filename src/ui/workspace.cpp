/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "workspace.h"
#include "editorpart.h"
#include "sidebar.h"
#include "graph.h"
namespace douml
{
Workspace::Workspace()
{
	m_editorPart = nullptr;
	m_sideBar = nullptr;
	m_graphs = new std::vector<Graph*>;
}
Workspace::~Workspace()
{

	ClearGraphs();
}
void Workspace::ClearGraphs()
{
	std::vector<Graph*>::iterator i;
	for (i = m_graphs->begin(); i != m_graphs->end(); i++)
	{
		delete (*i);
	}
	m_graphs->clear();
	delete m_graphs;
}
void Workspace::CreateWorkspace()
{

}
void Workspace::OnXXXX()
{
    
}
Graph* Workspace::GetActiveGraph()
{
	return nullptr;
}
void Workspace::SetEditorPart(EditorPart* ep)
{
	m_editorPart = ep;
}
void Workspace::SetSideBar(SideBar* sb)
{
	m_sideBar = sb;
}
EditorPart* Workspace::GetEditorPart()
{
	return m_editorPart;
}
SideBar* Workspace::GetSideBar()
{
	return m_sideBar;
}



}