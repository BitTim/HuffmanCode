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

  long int checkVal(std::string val)
  {
    long int returnVal;
    if(this->node0 == nullptr || this->node1 == nullptr) return 2;

    if(this->node0->value.find(val, 0) != std::string::npos)
    {
      printf("[I] Found value %s in node0 off Node %s", val.c_str(), this->value.c_str());
      returnVal = this->node0->checkVal(val);

      returnVal << 1;
      returnVal += (0 & 0x01);

      return returnVal;
    }

    if(this->node1->value.find(val, 0) != std::string::npos)
    {
      printf("[I] Found value %s in node1 off Node %s", val.c_str(), this->value.c_str());
      returnVal = this->node1->checkVal(val);
      
      returnVal << 1;
      returnVal += (1 & 0x01);

      return returnVal;
    }

    printf("[E] Error while tracing path in tree of the value \"%s\"", val.c_str());
    return -1;
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

  std::vector<long int> encode(std::string text)
  {
    std::vector<long int> values;
    for(int i = 0; i < text.length(); i++)
    {
      values.push_back(nodes[nodes.size() - 1].checkVal(std::string(1, text[i])));
    }

    return values;
  }

  std::string decode(std::vector<int> values)
  {

  }
};

#endif // TREE_HH