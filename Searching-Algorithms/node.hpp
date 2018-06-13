//  Tree.cpp

#ifndef node_hpp
#define node_hpp

#include <unordered_map>
#include <string>

class Node {
public:
    Node(const std::string _name);
    const int getPathWeight(Node* const child) const;
    void addPath(Node *dest, int weight);
    const std::unordered_map<Node*, int>& getPaths() const;
    const std::string& getName() const;
    
private:
    std::unordered_map<Node*, int> paths;
    std::string name;
};

#endif /* node_hpp */
