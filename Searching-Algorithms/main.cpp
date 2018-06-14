/*
 Test search algorithms and analyze results
 */

#include <iostream>
#include "breadth_first_search.hpp"
#include "node.hpp"

void testBFS() {
    Node a{"a"};
    Node b{"b"};
    Node c{"c"};
    Node d{"d"};
    Node e{"e"};
    Node f{"f"};
    // Unconnected, altering the target of BFS to this node will return an empty path
    Node g{"unconnected"};
    a.addPath(b, 2);
    a.addPath(e, 5);
    // add a path to itself, BFS will ignore because it has visited it already so cycles are not a problem
    a.addPath(a, 0);
    a.addPath(d, 1);
    b.addPath(c, 8);
    // Uncommenting this may cause BFS to choose this path instead because BFS only finds the shallowest depth
    // b.addPath(f, 9999);
    b.addPath(e, 1);
    c.addPath(f, 1);
    e.addPath(d, 1);
    d.addPath(f, 5);
    BFS::childToParentPaths result = BFS::breadth_first_search(a, f);
    BFS::printBFSResult(a,f, result);
}

int main(int argc, const char * argv[]) {
    testBFS();
    return 0;
}
