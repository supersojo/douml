/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_SIDEBAR_H
#define DU_SIDEBAR_H
#include "douml.h"
#include <vector>
namespace douml 
{
	class Rect;
    class ToolItem;
    class Workspace;
class DU_API SideBar {
public:
    SideBar();
	~SideBar();
    SideBar(Workspace* ws);
	Workspace* GetWorkspace();
    virtual void CreateSideBar();
    virtual void OnXXXX();
    virtual void OnGraphToolItemClicked(ToolItem *item);
	virtual void OnStandardItemClicked(ToolItem *item);
	bool IsStandardMenuToggled();
	bool IsGraphMenuToggled();
	void SetStandardMenuToggled(bool s);
	void SetGraphMenuToggled(bool s);
	Rect GetCurrentStandardMenuRect();
	Rect GetCurrentGraphMenuRect();
	void GetStandardToolItems(std::vector<ToolItem*>& tools);
	ToolItem* GetActiveStandardToolItem();
	virtual void CreateStandardToolItems(std::vector<ToolItem*>& tools);
	enum {
		TOOL_UNDO,
		TOOL_ZOOM_IN,
		TOOL_ZOOM_OUT,
		TOOL_DELETE,
		TOOL_REDO,
		TOOL_CUT,
		TOOL_COPY,
		TOOL_PASTE
	};
	static du_int MENU_TITLE_HEIGHT;
	static du_int MENU_TITLE_WIDTH;

private:
    Workspace* m_workspace;
	bool m_standardMenuToggled;// true for fold, false for unfold
	bool m_graphMenuToggled;// true for fold, false for unfold
	Rect *m_standardMenuRect;
	Rect *m_graphMenuRect;
	std::vector<ToolItem*>* m_toolItems;// standard tool items
};
}
#endif