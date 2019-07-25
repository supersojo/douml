/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_INTERFACENODE_H
#define DU_INTERFACENODE_H
#include "douml.h"
#include "node.h"

namespace douml
{
    class Rect;
class DU_API InterfaceNode : public Node
{
public:
    InterfaceNode();
    virtual ~InterfaceNode();
    du_char* GetName();
    void SetName(du_char* n);
    std::vector<du_char*>* GetMethods();
    void SetMethods(std::vector<du_char*>& methods);
    virtual void NotifyCallback();
    bool GetChanged();
    void SetChanged(bool c);
    Rect GetNameRect();
    Rect GetMethodsRect();
    static du_int GAP_X;
    static du_int GAP_Y;
private:
    bool m_changed;
    du_char* m_name;
    std::vector<du_char*>* m_methods;

    void  UpdateMinRects();

    Rect *m_nameRect;
    Rect *m_methodsRect;
};

} // namespace douml

#endif
