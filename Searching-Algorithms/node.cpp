#include "node.hpp"
#include <iostream>

Node::Node(const std::string _name) : name(_name) {
}

const std::string& Node::getName() const {
    return name;
}

const int Node::getPathWeight(const Node& child) const {
    NodeUtility::Paths::const_iterator itr = paths.find(&child);
    // Did not find child in paths
    if (paths.end() == itr) {
        return -1;
    }
    return itr->second;
}

// A node can add a path to itself
void Node::addPath(const Node& dest, const int weight) {
    // If the path exists, it will be overwritten or create a new key-value pair
    paths[&dest] = weight;
    
}

const NodeUtility::Paths& Node::getPaths() const {
    return paths;
}
