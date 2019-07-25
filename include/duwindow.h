/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_DUWINDOW_H
#define DU_DUWINDOW_H

#include "douml.h"

#ifdef _MSC_VER
#include <afxwin.h>
#endif

namespace douml
{

#ifdef _MSC_VER
class DU_API DuWindow : public CWnd
{

public:
    DuWindow();
    DuWindow(DuWindow* parent);
    DuWindow(CWnd* parent);
    virtual ~DuWindow();
    void ShowWindow();
    void ShowWindow(bool show);
    virtual void PostNcDestroy();

    static LPCTSTR g_duwindow_class; 

};


#endif

}

#endif
