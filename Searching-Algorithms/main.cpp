/*
Create a graph to test searching algorithms and compare results
*/

#include <iostream>
#include "breadth_first_search.hpp"
#include "node.hpp"

int main(int argc, const char * argv[]) {
    /*
     Create grapth where shortest path from root to d is root->b->d (cost: 6, depth: 2)
     Purposely add other paths that lead root to d
     */
    Node root{"root"};
    Node a{"a"};
    Node b{"b"};
    // ignored
    root.addPath(&root, 99);
    // If initialized this way, shortest path and smallest depth is achieved (BFS)
    root.addPath(&b, 5);
    root.addPath(&a, 3);
    
    // If initialized this way, because BFS uses FIFO, the shortest path is not achieved but smallest depth is achieved
    // root.addPath(&a, 3);
    // root.addPath(&b, 5);
    
    // Not connected to anything
    // Node c{"c"};
    Node d{"d"};
    // Create multiple paths to get to d
    b.addPath(&d, 1);
    a.addPath(&d, 7);
    
    // Start BFS test
    BFS::BFSPairResult result = BFS::breadth_first_search(&root, &d);
    std::cout << "Cost: " << result.first << std::endl;
    std::cout << "Depth: " << result.second.size() << std::endl;
    BFS::printBFSPath(result);
    // End BFS test
    return 0;
}
