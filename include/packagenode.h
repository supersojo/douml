/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_PACKAGENODE_H
#define DU_PACKAGENODE_H
#include "douml.h"
#include "node.h"

namespace douml
{
class DU_API PackageNode : public Node 
{
public:
    PackageNode();
    virtual ~PackageNode();
    du_char* GetName();
    void SetName(du_char* n);
    std::vector<du_char*>* GetContent();
    void SetContent(std::vector<du_char*>& content);
    virtual void NotifyCallback();
    bool GetChanged();
    void SetChanged(bool c);
    Rect GetNameRect();
    Rect GetContentRect();
    static du_int GAP_X;
    static du_int GAP_Y;
    static du_int TOP_X;
    static du_int TOP_Y;
private:
    bool m_changed;
    du_char* m_name;
    std::vector<du_char*>* m_content;


    void  UpdateMinRects();

    Rect *m_nameRect;
    Rect *m_contentRect;

};
}
#endif
