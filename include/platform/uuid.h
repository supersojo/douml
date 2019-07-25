/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef DU_UUID_H
#define DU_UUID_H

#include <string>
#include "douml.h"

namespace douml
{

class DU_API UUID
{
public:
    std::string Gen();
};

} // namespace douml

#endif
