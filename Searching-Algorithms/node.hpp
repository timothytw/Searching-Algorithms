#ifndef node_hpp
#define node_hpp

#include <unordered_map>
#include <string>

/*
 A path can have negative weight
 The order of paths added does not mean search algorithms will access paths in that order (i.e BFS uses FIFO)
 */

class Node;
namespace NodeUtility {
    using Paths = std::unordered_map<const Node*, int>;
}

class Node {
public:
    Node(const std::string _name);
    const int getPathWeight(const Node& child) const;
    void addPath(const Node& dest, int weight);
    const std::unordered_map<const Node*, int>& getPaths() const;
    const std::string& getName() const;
private:
    NodeUtility::Paths paths;
    std::string name;
};



#endif /* node_hpp */
