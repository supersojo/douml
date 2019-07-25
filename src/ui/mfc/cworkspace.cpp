/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "cworkspace.h"

namespace douml
{

CWorkspace::CWorkspace()
{

}
BEGIN_MESSAGE_MAP(CWorkspace,CWnd)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


}