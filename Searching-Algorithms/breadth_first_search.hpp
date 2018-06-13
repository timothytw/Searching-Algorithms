#ifndef breadth_first_search_h
#define breadth_first_search_h

/*
 Breadth First Search (BFS)
 
 Can be used on a Tree or Graph using the Node class
 BFS does not always find the shortest path but finds the smallest depth to get to the target
 
 */

#include <deque>
#include <set>
#include <unordered_map>
#include <utility> // pair
#include "node.hpp"

namespace BFS {
    // Queue of <Node, currentWeight>
    using Frontier = std::deque<std::pair<Node*, int>>;
    // Unordered map of <Node, distance from current node to this node>
    using Paths = std::unordered_map<Node*, int>;
    using DequeNodePtr = std::deque<Node*>;
    using SetNodePtr = std::set<Node*>;
    using BFSPairResult = std::pair<int, DequeNodePtr>;

    const BFSPairResult breadth_first_search(Node *root, Node *target);
    void printBFSPath(const BFSPairResult& result);
}
#endif /* breadth_first_search_h */
