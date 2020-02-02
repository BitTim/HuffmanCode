#ifndef TREE_HH
#define TREE_HH

#include <string>
#include <vector>
#include <algorithm>

struct NodeData
{
  std::string value;
  int rate;
};

class Node
{
public:
  Node* node0 = nullptr;
  Node* node1 = nullptr;
  std::string value = "";
  int rate = 0;
  bool visited = false;

  Node() { }
  Node(Node* nNode0, Node* nNode1, std::string nValue, int nRate)
  {
    node0 = nNode0;
    node1 = nNode1;
    value = nValue;
    rate = nRate;
  }

  std::vector<int> visitEncode(char in)
  {
    std::vector<int> returnVec;

    if(node0->value.find(std::string(1, in), 0) != std::string::npos)
    {
      if(node0->node0 != nullptr && node0->node1 != nullptr) returnVec = node0->visitEncode(in);
      returnVec.push_back(0);
      return returnVec;
    }

    if(node1->value.find(std::string(1, in), 0) != std::string::npos)
    {
      if(node1->node0 != nullptr && node1->node1 != nullptr) returnVec = node1->visitEncode(in);
      returnVec.push_back(1);
      return returnVec;
    }

    returnVec.push_back(-1);
    return returnVec;
  }

  NodeData visitDecode(std::vector<int> in, int index) //Repurposing NodeData Structure
  {
    NodeData returnVec;
    if(node0 == nullptr || node1 == nullptr)
    {
      returnVec.value = value;
      returnVec.rate = index;
      return returnVec;
    }

    if(in[index] == 0) return node0->visitDecode(in, index + 1);
    if(in[index] == 1) return node1->visitDecode(in, index + 1);

    returnVec.value = "ERROR";
    returnVec.rate = -1;
    return returnVec;
  }
};

bool sortSmallestRate(Node *a, Node *b)
{
  if(a->visited) return false;
  if(b->visited) return true;
  else return a->rate < b->rate;
}

bool sortHighestRate(Node *a, Node *b)
{
  if(a->visited) return false;
  if(b->visited) return true;
  else return a->rate > b->rate;
}

class Tree
{
private:
  std::vector<Node*> nodes;

public:
  Node* root = nullptr;

  Tree() { }
  Tree(std::vector<NodeData> alphabet)
  {
    //Create initial Nodes
    for(NodeData nd : alphabet) nodes.push_back((new Node(nullptr, nullptr, nd.value, nd.rate)));
    std::sort(nodes.begin(), nodes.end(), sortSmallestRate);

    //Create the temporary nodes needed for the tree
    while(nodes[0]->rate < 100)
    {
      nodes.push_back(new Node(nodes[0], nodes[1], nodes[0]->value + nodes[1]->value, nodes[0]->rate + nodes[1]->rate));
      nodes[0]->visited = true;
      nodes[1]->visited = true;
      std::sort(nodes.begin(), nodes.end(), sortSmallestRate);
    }

    //Sort the temporary Nodes from highest to lowest and assign root Node
    for(int i = 0; i < nodes.size(); i++) nodes[i]->visited = false;
    std::sort(nodes.begin(), nodes.end(), sortHighestRate);
    root = nodes[0];

    //Print out the sorted nodes
    for(int i = 0; i < nodes.size(); i++) if(nodes[i]->node0 != nullptr && nodes[i]->node1 != nullptr) printf("%s %d% -> node0: %s %d%, node1: %s %d%\n", nodes[i]->value.c_str(), nodes[i]->rate, nodes[i]->node0->value.c_str(), nodes[i]->node0->rate, nodes[i]->node1->value.c_str(), nodes[i]->node1->rate);
  }

  std::vector<int> encode(std::string in)
  {
    std::vector<int> returnVec;
    std::vector<std::vector<int>> returnVals;

    for(char c : in) returnVals.push_back(root->visitEncode(c));
    for(std::vector<int> v : returnVals)
    {
      std::reverse(v.begin(), v.end());
      returnVec.insert(returnVec.end(), v.begin(), v.end());
    }

    return returnVec;
  }

  std::string decode(std::vector<int> in)
  {
    std::string returnString;
    NodeData tmp;
    int index = 0;

    while(index < in.size())
    {
      tmp = root->visitDecode(in, index);
      index = tmp.rate;
      returnString.append(tmp.value);
    }

    return returnString;
  }
};

#endif // TREE_HH