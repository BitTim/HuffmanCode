#include <iostream>
#include <fstream>
#include "tree.hh"

std::vector<NodeData> alphabet;
Tree tree;

std::ifstream infile;
std::ofstream outfile;

bool oInFile = false;
bool oOutFile = false;

std::string inputText;

void print_help()
{
  printf("Huffman Code help:\n");
  printf("Usage: huffman [MODE] [INFILE] [OUTFILE]\n\n");
  printf("MODE can be either '-e' for encoding or '-d' for decoding.\n");
  printf("INFILE and OUTFILE can either be filepaths or can be replaced\n");
  printf("with -o to override with user input in the console\n\n");
}

int checkArgs(int argc, char* argv[])
{
  if(argc != 4)
  {
    printf("[E] Too few arguments specified!\n\n");
    print_help();
    return 1;
  }

  if(argv[1][0] != '-' && (argv[1][1] != 'd' && argv[1][1] != 'e'))
  {
    printf("[E] Invalid option %s\n\n", argv[1]);
    print_help();
    return 2;
  }

  return 0;
}

int main(int argc, char* argv[])
{
  checkArgs(argc, argv);

  //Check if INFILE is overriden and/or open the infile
  if(argv[2][0] != '-' && argv[2][1] != 'o')
  {
    infile.open(argv[2]);
    if(infile.fail())
    {
      printf("[E] Failed to open file %s\n", argv[2]);
      return -1;
    }
  }
  else
  {
    bool oInFile = true;
    printf("Please enter your input text:\n");
    std::cin >> inputText;
  }

  //Check if OUTFILE is overriden and/or open the outfile
  if(argv[3][0] != '-' && argv[3][1] != 'o')
  {
    infile.open(argv[3], std::ifstream::binary);
    if(infile.fail())
    {
      printf("[E] Failed to open file %s\n", argv[3]);
      return -1;
    }
  }
  else bool oOutFile = true;

  //Calculate the rates of the letters
  if(!oInFile)
  {
    bool broken = false;
    while(std::getline(infile, inputText))
    {
      for(char c : inputText)
      {
        if(alphabet.size() != 0)
        {
          broken = false;
          for(int i = 0; i < alphabet.size(); i++)
          {
            if(alphabet[i].value == std::string(c, 1)) alphabet[i].rate += 1;
            broken = true;
            break;
          }

          NodeData nd = {std::string(c, 1), 1};
          if(!broken) alphabet.push_back(nd);
        }
      }
    }
  }

  tree = Tree(alphabet);
  std::vector<int> tmp = tree.encode("bedcab");

  printf("\n");
  for(int i = 0; i < tmp.size(); i++) printf("%d ", tmp[i]);
  printf("\n");

  std::string tmp_str = tree.decode(tmp);
  printf("%s\n", tmp_str.c_str());

  return 0;
}

/*
huffman -e <INFILE> <OUTFILE>
huffman -d <INFILE> <OUTFILE>

Files can be replaced with -o to override
Console only application:
huffman -e -o -o
huffman -d -o -o
*/