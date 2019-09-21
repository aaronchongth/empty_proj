#pragma once

// STL
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <priority_queue>
#include <chrono>

// Implementation notes:
- try to be environment agnostic
- pull in function pointers for environment
  - bool get_neighbor_nodes(const Node& _node, std::vector<Node>& _neighbours)
  - double get_cost(node, node)
- a struct to hold node pointer and its parent, or general next or something

class Node
{
  
};

class DjikstraPlanner
{
private:
  std::priority_queue<std::pair<double, close_>> open_;
  std::unordered_set<Node> close_;

public:
  DjikstraPlanner();

  ~DjikstraPlanner();

  Node get_next_node();
};
