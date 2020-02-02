#ifndef TREE_HH
#define TREE_HH

#include <vector>
#include <algorithm>
#include <string>

struct CharWithRate
{
  char c;
  int r;
};

class Node
{
public:
  Node* node0;
  Node* node1;
  int rate;
  std::string value;
  bool visited = false;

  Node() { }
  Node(Node* node0, Node* node1, int rate, std::string value = "\0")
  {
    this->node0 = node0;
    this->node1 = node1;
    this->rate = rate;
    this->value = value;
  }

  std::vector<int> visit(std::string val)
  {
    std::vector<int> returnVec;
    if(this->node0 == nullptr || this->node1 == nullptr)
    {
      printf("[I] Node %s returned 2, has no child nodes\n", this->value.c_str());
      returnVec.push_back(2);
      return returnVec;
    }

    printf("[I] Finding substring %s in Node0 %s %d\n", val.c_str(), this->node0->value.c_str(), this->node0->value.find(val, 0));
    if(this->node0->value.find(val, 0) != std::string::npos)
    {
      printf("[I] Node %s returned 0, child node is %s\n", this->value.c_str(), this->node0->value.c_str());
      returnVec = this->node0->visit(val);
      returnVec.push_back(0);
      return returnVec;
    }

    printf("[I] Finding substring %s in Node1 %s %d\n", val.c_str(), this->node1->value.c_str(), this->node1->value.find(val, 0));
    if(this->node1->value.find(val, 0) != std::string::npos)
    {
      printf("[I] Node %s returned 1, child node is %s\n", this->value.c_str(), this->node1->value.c_str());
      returnVec = this->node1->visit(val);
      returnVec.push_back(1);
      return returnVec;
    }

    printf("[E] Failed to find Path for %s\n", val.c_str());
    returnVec.push_back(-1);
    return returnVec;
  }
};

bool compareByRate(const Node &a, const Node &b)
{
  if(a.visited) return false;
  if(b.visited) return true;
  else return a.rate < b.rate;
}

class Tree
{
public:
  std::vector<Node> nodes;
  bool stop = false;

  void createChildNode()
  {
    nodes.push_back(Node(&nodes[0], &nodes[1], nodes[0].rate + nodes[1].rate, nodes[0].value + nodes[1].value));
    nodes[0].visited = true;
    nodes[1].visited = true;

    printf("[I] New node %s %d connected to: %s %d, %c %d\n", nodes[nodes.size() - 1].value.c_str(), nodes[nodes.size() - 1].rate, nodes[nodes.size() - 1].node0->value.c_str(), nodes[nodes.size() - 1].node0->rate, nodes[nodes.size() - 1].node1->value.c_str(), nodes[nodes.size() - 1].node1->rate);
    if(nodes[nodes.size() - 1].rate >= 100) stop = true;

    std::sort(nodes.begin(), nodes.end(), compareByRate);
  }

  Tree() { };
  Tree(std::vector<CharWithRate> alphabet)
  {
    for(int i = 0; i < alphabet.size(); i++) nodes.push_back(Node(nullptr, nullptr, alphabet[i].r, std::string(1, alphabet[i].c)));
    std::sort(nodes.begin(), nodes.end(), compareByRate);

    while(!stop) { createChildNode(); }

    printf("[I] Printing sorted Nodes:\n");
    for(int i = 0; i < nodes.size(); i++)
    {
      printf("-> [%d] %s %d: node0 %s %d, node1 %s %d\n", i, nodes[i].value.c_str(), nodes[i].rate, nodes[i].node0->value.c_str(), nodes[i].node0->rate, nodes[i].node1->value.c_str(), nodes[i].node1->rate);
    }
  }

  std::vector<int> encode(std::string text)
  {
    std::vector<int> values;
    for(int i = 0; i < text.length(); i++)
    {
      printf("[I] Encoding \"%c\", starting at node %s\n", text[i], nodes[0].value.c_str());
      values = (nodes[0].visit(std::string(1, text[i])));
    }

    return values;
  }

  std::string decode(std::vector<int> values)
  {
    return "";
  }
};

#endif // TREE_HH