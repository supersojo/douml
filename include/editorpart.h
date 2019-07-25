/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_EDITORPART_H
#define DU_EDITORPART_H
#include "douml.h"

namespace douml 
{
    class Workspace;
    class Point;
    class Node;
    class Edge;

class DU_API EditorPart {
public:
	virtual void CreateEditorPart();
    virtual void OnXXXX();
    virtual void OnNewNode(Point& p,Node* n);
    virtual void OnNewEdge(Node* start,Node* end,Edge* e);
    virtual void OnSelectNode(Node* n);
    virtual void OnSelectEdge(Edge* e);
private:
    Workspace* m_workspace;
};

}
#endif
