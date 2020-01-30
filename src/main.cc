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
  std::vector<int> values = tree.encode("abc");
  printf("[I] Finished encoding. Result:\n");

  for(int i = 0; i < values.size(); i++)
  {
    printf("-> [%d] %d\n", i, values[i]);
  }

  return 0;
}