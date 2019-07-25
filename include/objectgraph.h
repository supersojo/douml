/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef DU_OBJECTGRAPH_H
#define DU_OBJECTGRAPH_H
#include "douml.h"
#include "graph.h"
#include <vector>
namespace douml 
{
    class ToolItem;
class DU_API ObjectGraph : public Graph 
{
public:
    virtual void CreateToolItems(std::vector<ToolItem*>& items);
    virtual ~ObjectGraph();
};
}
#endif
