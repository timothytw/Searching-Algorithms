//  node.cpp

#include <unordered_map>
#include "node.hpp"

Node::Node(const std::string _name) : name(_name) {
}

const std::string& Node::getName() const {
    return name;
}

const int Node::getPathWeight(Node* const child) const {
    std::unordered_map<Node*, int>::const_iterator itr = paths.find(child);
    // Did not find child in paths
    if (paths.end() == itr) {
        return -1;
    }
    return itr->second;
}

void Node::addPath(Node* const dest, const int weight) {
    // Adding a path to itself means the path is redundant
    if (this == dest) return;
    // If the path exists, it will be overwritten or create a new key-value pair
    paths[dest] = weight;
}

const std::unordered_map<Node*, int>& Node::getPaths() const {
    return paths;
}
