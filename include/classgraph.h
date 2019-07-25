/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_CLASSGRAPH_H
#define DU_CLASSGRAPH_H
#include "douml.h"
#include "graph.h"
#include <vector>

namespace douml
{
    class ToolItem;
class DU_API ClassGraph : public Graph 
{
public:
    virtual void CreateToolItems(std::vector<ToolItem*>& items);
    virtual ~ClassGraph();
};

}
#endif
