#include <iostream>
#include "tree.hh"

std::vector<CharWithRate> alphabet = {{'a', 20}, {'b', 30}, {'c', 10}, {'d', 5}, {'e', 35}};
Tree tree;

void init()
{
  tree = Tree(alphabet);
}

int main(int argc, char* argv[])
{
  init();
  return 0;
}