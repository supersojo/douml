/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_NOTENODE_H
#define DU_NOTENODE_H

#include "douml.h"
#include "node.h"
#include <vector>
namespace douml
{
    class Rect;
class DU_API NoteNode:public Node 
{
public:
    NoteNode();
    virtual ~NoteNode();

    du_char* GetText();
    void SetText(du_char* t);

    std::vector<du_char*>* GetContent();
    void SetContent(std::vector<du_char*>& content);

    virtual void NotifyCallback();
    bool GetChanged();
    void SetChanged(bool c);

    static du_int GAP_X;
    static du_int GAP_Y;

    Rect GetContentRect();

private:
    bool m_changed;
    du_char* m_text;
    std::vector<du_char*>* m_content;

    Rect *m_contentRect;

    void  UpdateMinRects();
};

}

#endif