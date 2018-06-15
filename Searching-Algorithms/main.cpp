/*
 Test search algorithms and analyze results
 */

#include <iostream>
#include "breadth_first_search.hpp"
#include "uniform_cost_search.hpp"

void testBFS(const Node& start, const Node& end) {
    std::cout << "BFS:\n";
    BFS::childToParentPaths result = BFS::breadth_first_search(start, end);
    BFS::printResult(start, end, result);
    std::cout << "======\n";
}

void testUniformCostSearch(const Node& start, const Node& end) {
    std::cout << "Uniform cost search:\n";
    BFS::childToParentPaths result2 = BFS::uniform_cost_search(start, end);
    BFS::printResult(start, end, result2);
    std::cout << "======\n";
}

int main(int argc, const char * argv[]) {
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
    // add a path to itself, BFS and uniform cost search will ignore because it has visited it already so cycles are not a problem
    a.addPath(a, 0);
    a.addPath(d, 1);
    b.addPath(c, 1);
    // Uncommenting this may cause BFS to choose this path instead because BFS only finds the shallowest depth
    // b.addPath(f, 9999);
    b.addPath(e, 1);
    c.addPath(f, 1);
    e.addPath(d, 1);
    d.addPath(f, 5);
    testBFS(a, f);
    testUniformCostSearch(a, f);
    return 0;
}
