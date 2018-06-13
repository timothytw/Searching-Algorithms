#include <iostream>
#include "breadth_first_search.hpp"

const BFS::BFSPairResult BFS::breadth_first_search(Node *root, Node *target) {
    // Nodes we have finished investigating
    BFS::DequeNodePtr visited;
    BFS::SetNodePtr visitedKeys;
    if (root == nullptr || target == nullptr) return {-1, visited};
    if (root == target) return {0, visited};
    // The nodes that we have discovered and will investigate FIFO style
    BFS::Frontier frontier;
    // Root is first discovered initially with weight of 0
    frontier.push_front({root,0});
    // Used to determine if node is in frontier quickly and easily
    BFS::SetNodePtr frontierKeys;
    frontierKeys.insert(root);
    
    while (frontier.size() != 0) {
        // Get the oldest node discovered
        Node *current = frontier.front().first;
        const int costToGetToCurrent = frontier.front().second;
        
        // Remove from frontier and add it to visited
        frontier.pop_front();
        frontierKeys.erase(current);
        visited.push_back(current);
        visitedKeys.insert(current);
        
        // Get all the nodes that the current node has a path to
        const BFS::Paths currentPaths = current->getPaths();
        /*
         Loop each path and determine if that path leads to the target node
         If leads to path, provide the weight and end the search
         Otherwise, update the weight to get to that node using that path and add to frontier (discovered)
         */
        for (auto itr = currentPaths.begin(); itr != currentPaths.end(); itr++) {
            bool neverVisited = ( visitedKeys.find(itr->first) == visitedKeys.end() );
            bool notInFrontier = ( frontierKeys.find(itr->first) == frontierKeys.end() );
            if (neverVisited || notInFrontier) {
                int newWeight = current->getPathWeight(itr->first) + costToGetToCurrent;
                if (itr->first == target) {
                    return {newWeight, visited};
                }
                // Not the target, update cost
                frontier.push_back({itr->first,newWeight});
                frontierKeys.insert(itr->first);
            }
        }
    }
    // Failed: There is no more paths and still have not found the target node
    return {-1, visited};
}

void BFS::printBFSPath(const BFS::BFSPairResult& result) {
    if (result.first == -1) {
        std::cout << "No paths found\n";
        return;
    }
    std::cout << "==== Begin ====\n";
    for (auto itr = result.second.begin(); itr != result.second.end(); itr++) {
        std::cout << (*itr)->getName() << std::endl;
    }
    std::cout << "==== End ====\n";
}

