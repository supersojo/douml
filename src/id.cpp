/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "id.h"
#include "platform/uuid.h"

namespace douml
{

Id::Id()
{
	m_id = new std::string;
    // initialize m_id with uuid string
    UUID uuid;
    *m_id = uuid.Gen();
}
Id::~Id()
{
    delete m_id;
}
bool Id::Equals(Id& id) {
    if (this == &id)
        return true;
	return m_id->compare(id.GetValue()) == 0;
}
std::string &Id::GetValue()
{
    return *m_id;
}

} // namespace douml