#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main(int argc, char *argv[]){
  //validate inputs and set values
  if(argc < 4){
    std::cout << "Invalid number of arguments" << std::endl;
    return(0);
  }
  /*for(int i = 0; i < sizeof(argv[1])-1; i++){
    std::cout << argv[1][i] << std::endl;
    if(std::isdigit(argv[1][i]) == false){
      std::cout << "bad integer value " << argv[1] << " for MAX_N_OUT" << std::endl;
      return(0);
    }
  }

  for(int i = 0; i < sizeof(argv[2])-1; i++){
    if(std::isdigit(argv[2][i]) == false){
      std::cout << "bad integer value " << argv[2] << " for MIN_WORD_LEN" << std::endl;
      return(0);
    }
  }
  
  for(int i = 0; i < sizeof(argv[3])-1; i++){
    if(std::isdigit(argv[3][i]) == false){
      std::cout << "bad integer value " << argv[3] << " for MAX_WORD_LEN" << std::endl;
      return(0);
    }
  }*/
	
  int MAX_N_OUT = std::stoi(argv[1]);
  int MIN_WORD_LEN = std::stoi(argv[2]);
  int MAX_WORD_LEN = std::stoi(argv[3]);
  std::unordered_map<std::string, int> wordmap;
  for(int i = 4; i < argc; i ++){
    std::ifstream in(argv[i]);
    while (in.good()){
      std::string w;
      in >> w;
      std::string formatted_w;
      for(std::string::size_type letter = 0; letter< w.size(); letter++){
	if(std::isalpha(w[letter])){
	  formatted_w += std::tolower(w[letter]);
	}
      }
      //put thing here
      if(formatted_w.length()>=MIN_WORD_LEN && formatted_w.length()<=MAX_WORD_LEN){
	std::cout << formatted_w << std::endl;
	wordmap[formatted_w] += 1; 
	std::cout << wordmap[formatted_w] << std::endl;
      }
    }
  }
}
