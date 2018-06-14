#ifndef breadth_first_search_h
#define breadth_first_search_h

/*
 Breadth First Search (BFS)
 
 Can be used on a Tree or Graph using the Node class
 BFS does not always find the shortest path but finds the shallowest depth to get to the target
 
 breadth_first_search returns a pair <total weight, path taken (deque)>
 
 The weight is -1 if cannot find the target but the Node class allows negative weight so to check if -1 is
 a valid weight, check the size of path taken. If it is 0, there is no valid path.
 Size of path is the number of nodes in it
 
 The (size of path - 1) is the depth of the valid path
 
 BFS is supposed to use queues but this implementation returns the path as well, so deque is used to allow users
 to loop the path easily and without modifying it (queue would require popping and re-adding)
 
 Deque has no quick lookup so the algorithm uses SetNodePtr (a set data structure)
 Therefore, the tradeoff is faster lookup but uses more space
 */

#include <deque>
#include <set>
#include <utility> // pair
#include "node.hpp"

namespace BFS {   
    // Queue of <Node, currentWeight>
    using Frontier = std::deque<std::pair<const Node*, int>>;
    using DequeOfNodePtr = std::deque<const Node*>;
    // Faster lookup: To determine if a node is in DequeNodePtr or Frontier
    using SetOfNodePtr = std::set<const Node*>;
    using BFSPairResult = std::pair<int, DequeOfNodePtr>;
    using childToParentPaths = std::unordered_map<const Node*, std::pair<const Node*, int>>;

    const childToParentPaths breadth_first_search(const Node& root, const Node& target);
    void printBFSResult(const Node& start, const Node& end, const BFS::childToParentPaths& result);
}
#endif /* breadth_first_search_h */
