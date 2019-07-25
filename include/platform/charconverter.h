/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_CHARCONVERTER_H
#define DU_CHARCONVERTER_H

#include "douml.h"

namespace douml {

class DU_API CharConverter {
public:
    du_char* UnicodeToUtf8(du_unicode* u);
    #if 0
    du_unicode *Utf8ToUnicode(du_char *c);
    #endif
    bool IsUtf8(du_char* c);
};

}


#endif
