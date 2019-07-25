/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "platform/uuid.h"

#include <afxwin.h>

namespace douml
{

std::string UUID::Gen()
{
    GUID guid = {0};
    char buf[64] = {0};
    CoCreateGuid(&guid);
    _snprintf_s(buf, sizeof(buf),
                "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                guid.Data1, guid.Data2, guid.Data3,
                guid.Data4[0], guid.Data4[1],
                guid.Data4[2], guid.Data4[3],
                guid.Data4[4], guid.Data4[5],
                guid.Data4[6], guid.Data4[7]);
    return std::string(buf);
}

} // namespace douml