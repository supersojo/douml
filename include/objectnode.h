/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_OBJECTNODE_H
#define DU_OBJECTNODE_H
#include "douml.h"
#include <vector>
#include "node.h"
namespace douml
{
    class Rect;
class DU_API ObjectNode : public Node 
{
public:
    ObjectNode();
    ~ObjectNode();

    du_char* GetName();
    void SetName(du_char* n);

    std::vector<du_char*>* GetFields();

    void AddField(du_int preIndex,du_char* n);
    void RemoveField(du_int index);

    bool GetNodeSelected();
    void SetNodeSelected(bool s);

    du_int GetFieldSelectedIndex();
    void SetFieldSelectedIndex(du_int index);

    bool GetFieldSelected();
    void SetFieldSelected(bool s);
    
	bool GetChanged();
	void SetChanged(bool c);

    virtual void NotifyCallback();

	Rect GetNameRect();
	Rect GetFieldsRect();

    static du_int GAP_X;
    static du_int GAP_Y;
private:
    bool m_changed;
    bool m_nodeSelected;
    bool m_fieldSelected;
    du_int m_fieldSelectedIndex;

    du_char* m_name;
    std::vector<du_char*>* m_fields;

    void  UpdateMinRects();

    Rect* m_nameRect;
    Rect* m_fieldsRect;
};

}
#endif
