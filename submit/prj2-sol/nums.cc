#include "arrayseq.hh"
#include "command.hh"
#include "seq.hh"
#include "dlinkseq.hh"
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

static void outputFile(const char *fileName, Seq<TestType>* seq_ptr){
  if(fileExists(fileName)){
    std::ifstream in(fileName);
    Seq<TestType>& seq = *seq_ptr;
    while(in.good() && !(in.eof())){
      TestType w;
      in >> w;
      seq.push(w);
    }
  }
}

int main(int argc, char* argv[]){
  SeqPtr<TestType> seq;
  if(argc == 1){
    std::cout << "usage ./nums [-a] INTS_FILE_PATH" << std::endl;
    std::exit(1);
  }
  else if(argc == 2){
    seq = DLinkSeq<TestType>::make();
    outputFile(argv[1], seq.get());
    auto begin = seq -> cbegin();
    auto end = seq -> cend();
    auto &p = *begin;
    auto &q = *end;
    --q;
    while(p && q){
      std::cout << *p << std::endl;
      std::cout << *q << std::endl;
      ++p;
      --q;
    }
  }
  else if(argc == 3){
    if(argv[1][0] == '-' && argv[1][1] == 'a'){
      //use array seq
      seq = ArraySeq<TestType>::make();
      outputFile(argv[2], seq.get());
    }
    else{
      std::cout << "invalid input for [-a]" << std::endl; 
    }
  

    auto begin = seq -> cbegin();
    auto end = seq -> cend();
    auto &p = *begin;
    auto &q = *end;
    --q;
    while(p && q){
      std::cout << *p << std::endl;
      std::cout << *q << std::endl;
      ++p;
      --q;
    }

    return 0;
  }

}
