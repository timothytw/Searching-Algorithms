#include <iostream>
#include "breadth_first_search.hpp"

const BFS::childToParentPaths BFS::breadth_first_search(const Node& root, const Node& target) {
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
        // Remove from frontier and add it to visited
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
             Therefore, the shortest path may not be found but the shallowest depth is still guaranteed
           */
        for (auto itr = currentPaths.begin(); itr != currentPaths.end(); itr++) {
            const Node* discovered = itr->first;
            bool neverVisited = ( visitedKeys.find(discovered) == visitedKeys.end() );
            bool notInFrontier = ( frontierKeys.find(discovered) == frontierKeys.end() );
            if (neverVisited && notInFrontier) {
                // Calculate new cost to get to this discovered node
                int newWeightToDiscovered = current->getPathWeight(*discovered) + costToGetToCurrent;
                // Remember new path
                rememberedPaths[discovered] = {current, newWeightToDiscovered};
                // Found target
                if (discovered == &target) {
                    // visited.push_back(&target);
                    return rememberedPaths;
                }
                // Not the target, update to new cost and add to frontier
                frontier.push_back({discovered, newWeightToDiscovered});
                frontierKeys.insert(discovered);
            }
        }
    }
    // Failed: There are no more paths and still have not found the target node
    // empty the paths we visited since none can reach target
    rememberedPaths.clear();
    return rememberedPaths;
}

/*
 Prints the path and costs backwards so it will refer to child->parent->grandparent->grandgrandparent->...
 There is a start and end parameter because result does not give the starting and ending nodes easily
 */
void BFS::printResult(const Node& start, const Node& end, const BFS::childToParentPaths& result) {
    // Size does not mean the number of nodes in the path, but if theres no path,
    // all paths are cleared so size is 0
    if (result.size() == 0) {
        std::cout << "No paths found\n";
        return;
    }
    std::cout << "==== End ====\n";
    int numNodes = 1;
    int costToGetToCurrent;
    // Start from end
    const Node* currentChild = &end;
    const Node* parentOfCurrentChild = result.at(currentChild).first;
    // Keep going backwards until we reach start, its parent is a nullptr
    while (parentOfCurrentChild != nullptr) {
        costToGetToCurrent = result.at(currentChild).second;
        std::cout << currentChild->getName() << " (Cost to get here: " <<
            costToGetToCurrent << ")" << std::endl;
        // Move backwards from path
        currentChild = parentOfCurrentChild;
        parentOfCurrentChild = result.at(currentChild).first;
        // We count the actual number of nodes in correct path
        numNodes++;
    }
    std::cout << start.getName() << std::endl;
    std::cout << "==== Start ====\n";
    std::cout << "Cost: " << result.at(&end).second << std::endl;
    std::cout << "Depth: " << numNodes - 1 << std::endl;
}

