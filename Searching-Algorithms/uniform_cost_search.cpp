#include "uniform_cost_search.hpp"

const BFS::childToParentPaths BFS::uniform_cost_search(const Node& root, const Node& target) {
    // Nodes we have finished investigating
    BFS::DequeOfNodePtr visited;
    // For easy lookup if a node is in visited
    BFS::SetOfNodePtr visitedKeys;
    
    // Keep track of the paths [Child Node]->[Parent Node, Weight to Child]
    BFS::childToParentPaths rememberedPaths;
    // The parent node to get to root is nullptr, no other parent or child can be a nullptr
    rememberedPaths[&root] = {nullptr, 0};
    // target is the root
    if (&root == &target) {
        visited.push_back(&root);
        return rememberedPaths;
    }
    // The nodes that we have discovered and will visit FIFO style
    BFS::Frontier frontier;
    // root is first discovered initially with weight of 0
    frontier.push_front({&root, 0});
    // For easy lookup if a node is in frontier
    BFS::SetOfNodePtr frontierKeys;
    frontierKeys.insert(&root);
    
    while (frontier.size() != 0) {
        // Select node from frontier to visit
        const Node* current = frontier.front().first;
        const int costToGetToCurrent = frontier.front().second;
        
        // Found target
        if (current == &target) {
            return rememberedPaths;
        }
        // Remove from frontier and add it to visited
        frontier.pop_front();
        frontierKeys.erase(current);
        visited.push_back(current);
        visitedKeys.insert(current);
        
        // Get all the nodes that current has paths to
        const NodeUtility::Paths currentPaths = current->getPaths();
    
         // Loop until target is placed in visited
        for (auto itr = currentPaths.begin(); itr != currentPaths.end(); itr++) {
            const Node* discovered = itr->first;
            bool neverVisited = ( visitedKeys.find(discovered) == visitedKeys.end() );
            bool notInFrontier = ( frontierKeys.find(discovered) == frontierKeys.end() );

            // Calculate new cost to get to this discovered node
            int newWeightToDiscovered = current->getPathWeight(*discovered) + costToGetToCurrent;
            if (neverVisited && notInFrontier) {
                // Not the target, update to new cost and add to frontier
                frontier.push_back({discovered, newWeightToDiscovered});
                frontierKeys.insert(discovered);
                rememberedPaths[discovered] = {current, newWeightToDiscovered};
            } else if ( !notInFrontier ) {
                int currentWeightToDiscovered = rememberedPaths[discovered].second;
                // If new weight is less than current weight, replace to the new path
                if (newWeightToDiscovered < currentWeightToDiscovered) {
                    rememberedPaths[discovered] = {current, newWeightToDiscovered};
                }
            }
        }
    }
    // Failed: There are no more paths and still have not found the target node
    // empty the paths we visited since none can reach target
    rememberedPaths.clear();
    return rememberedPaths;
}
