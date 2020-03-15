#include "arrayseq.hh"
#include "command.hh"
#include "seq.hh"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <utility>

using TestType = int;

bool fileExists(const char *fileName){
  std::ifstream ifile(fileName);
  if(!ifile){
    std::cout << "Cannot read " << fileName << std::endl;
    std::cout << "No such file or directory" << std::endl;
    return false;
  }
  return true;
}

void outputFile(const char *fileName){
  if(fileExists(fileName)){
    std::ifstream in(fileName);
    while(in.good()){
      std::string w;
      in >> w;
      std::cout << w << std::endl;
    }
  }
}

int main(int argc, char* argv[]){
  if(argc == 1){
    std::cout << "usage ./nums [-a] INTS_FILE_PATH" << std::endl;
    std::exit(1);
  }
  else if(argc == 2){
    outputFile(argv[1]);
  }
  else if(argc == 3){
    if(argv[1][0] == '-' && argv[1][1] == 'a'){
      //use array seq
      outputFile(argv[2]);
    }
    else{
      std::cout << "invalid input for [-a]" << std::endl; 
    }
  }
}
