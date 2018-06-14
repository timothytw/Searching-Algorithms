#include <iostream>
#include "breadth_first_search.hpp"

const BFS::BFSPairResult BFS::breadth_first_search(const Node& root, const Node& target) {
    // Nodes we have finished investigating
    BFS::DequeOfNodePtr visited;
    // For easy lookup if a node is in visisted
    BFS::SetOfNodePtr visitedKeys;

    // target is the root
    if (&root == &target) {
        visited.push_back(&root);
        return {0, visited};
    }
    // The nodes that we have discovered and will visit FIFO style
    BFS::Frontier frontier;
    // Root is first discovered initially with weight of 0
    frontier.push_front({&root, 0});
    // For easy lookup if a node is in frontier
    BFS::SetOfNodePtr frontierKeys;
    frontierKeys.insert(&root);

    while (frontier.size() != 0) {
        // Select node from frontier to visit
        const Node* current = frontier.front().first;
        const int costToGetToCurrent = frontier.front().second;
        // Remove from frontier and add it to visited.
        frontier.pop_front();
        frontierKeys.erase(current);
        visited.push_back(current);
        visitedKeys.insert(current);
        // Get all the nodes that current has paths to
        const NodeUtility::Paths currentPaths = current->getPaths();
        /*
             Loop each path and determine if that path leads to the target node
             If leads to path, provide the total weight and end the search
             Otherwise, update total weight to get to that node and add to frontier (discovered but not visited)
         
             Paths being discovered is not guaranteed to be in the order they were added (see Node class)
             Therefore, the shortest path may not be found but the shortest depth is still guaranteed
           */
        for (auto itr = currentPaths.begin(); itr != currentPaths.end(); itr++) {
            const Node* discovered = itr->first;
            bool neverVisited = ( visitedKeys.find(discovered) == visitedKeys.end() );
            bool notInFrontier = ( frontierKeys.find(discovered) == frontierKeys.end() );
            if (neverVisited && notInFrontier) {
                // Calculate new cost to get to this discovered node
                int newWeight = current->getPathWeight(*discovered) + costToGetToCurrent;
                // Found target
                if (discovered == &target) {
                    visited.push_back(&target);
                    return {newWeight, visited};
                }
                // Not the target, update to new cost and add to frontier
                frontier.push_back({discovered, newWeight});
                frontierKeys.insert(discovered);
            }
        }
    }
    // Failed: There are no more paths and still have not found the target node
    // empty the path we visited since none can reach target
    visited.clear();
    return {-1, visited};
}

void BFS::printBFSResult(const BFS::BFSPairResult& result) {
    if (result.first == -1) {
        std::cout << "No paths found\n";
        return;
    }
    std::cout << "Cost: " << result.first << std::endl;
    std::cout << "Depth: " << result.second.size() - 1 << std::endl;
    std::cout << "==== Begin ====\n";
    for (auto itr = result.second.begin(); itr != result.second.end(); itr++) {
        std::cout << (*itr)->getName() << std::endl;
    }
    std::cout << "==== End ====\n";
}

