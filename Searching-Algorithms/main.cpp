/*
 Test search algorithms and analyze results
 */

#include <iostream>
#include "breadth_first_search.hpp"
#include "node.hpp"

void testBFS() {
    Node root{"root"};
    Node a{"a"};
    Node b{"b"};
    // add a path to itself, BFS will ignore because it has visited it already
    root.addPath(root, -999);
    
    // Switching the order does not gurantee a path over the other
    root.addPath(b, 5);
    root.addPath(a, 3);

    // Not connected to anything, you can alter the target of BFS to this node and will return an empty path
    Node c{"c"};

    Node d{"d"};
    // Create multiple paths to get to d
    // Shortest path to d: root->b->d (cost: 6, depth: 2)
    b.addPath(d, 1);
    // Ignored because visited
    b.addPath(root, 0);
    // Another path to d: root->a->d (cost: 10, depth: 2)
    a.addPath(d, 7);

    // Start BFS test
    // It is possible that the path found is root->b->d or root->a->d, what matters is the depth amount (3)
    BFS::BFSPairResult result = BFS::breadth_first_search(root, d);
    BFS::printBFSResult(result);
    // End BFS test
}

int main(int argc, const char * argv[]) {
    testBFS();
    return 0;
}
