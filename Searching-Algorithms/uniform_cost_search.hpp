#ifndef uniform_cost_search_h
#define uniform_cost_search_h

#include "breadth_first_search.hpp"

/*
   Similar to BFS but after discovering the target, it does not conclude its search but
   keeps looking for a shorter path
 
    Use BFS namespace since uniform cost search is derived from BFS
 */

namespace BFS {
    const BFS::childToParentPaths uniform_cost_search(const Node& root, const Node& target);
}
#endif /* uniform_cost_search_h */
