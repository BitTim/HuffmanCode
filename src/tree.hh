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

    printf("New node %s %d connected to: %s %d, %c %d\n", nodes[nodes.size() - 1].value.c_str(), nodes[nodes.size() - 1].rate, nodes[nodes.size() - 1].node0->value.c_str(), nodes[nodes.size() - 1].node0->rate, nodes[nodes.size() - 1].node1->value.c_str(), nodes[nodes.size() - 1].node1->rate);
    if(nodes[nodes.size() - 1].rate >= 100) stop = true;

    std::sort(nodes.begin(), nodes.end(), compareByRate);
  }

  Tree() { };
  Tree(std::vector<CharWithRate> alphabet)
  {
    for(int i = 0; i < alphabet.size(); i++) nodes.push_back(Node(nullptr, nullptr, alphabet[i].r, std::string(1, alphabet[i].c)));
    std::sort(nodes.begin(), nodes.end(), compareByRate);

    for(int i = 0; i < nodes.size(); i++) printf("%s %d%\n", nodes[i].value.c_str(), nodes[i].rate);

    while(!stop) { createChildNode(); }
  }
};

#endif // TREE_HH