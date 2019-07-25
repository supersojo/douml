/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_WORKSPACE_H
#define DU_WORKSPACE_H
#include "douml.h"
#include <vector>
namespace douml 
{
    class EditorPart;
    class SideBar;
	class Graph;

class DU_API Workspace {
public:
    virtual void CreateWorkspace();
    virtual void OnXXXX();
    Graph* GetActiveGraph();
private:
	EditorPart* m_editorPart;
    SideBar* m_sideBar;
    du_int m_activeGraphIndex;
    std::vector<Graph*>* m_graphs;
};

}
#endif
