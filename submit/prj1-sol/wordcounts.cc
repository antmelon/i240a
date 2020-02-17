#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstring>

typedef std::pair<std::string, int> WordCount;

//comparator function
bool wordCountCompare(const WordCount &a, const WordCount &b){
  if(std::get<1>(a) == std::get<1>(b)){
    return(std::get<0>(b) > std::get<0>(a));
  }
  else{
    return(std::get<1>(b) < std::get<1>(a));
  }
}

bool fileExists(const char *fileName){
  std::ifstream ifile(fileName);
  if(!ifile){return false;}
  return true;
}

bool legal_int(char *str){
  for (size_t i = 0; i < strlen(str); i++){
    if(isdigit(str[i]) == false){
      return false;
    }
  }
  return true;
}


int main(int argc, char *argv[]){
  //validate inputs and set values
  if(argc == 1){
    std::cout << "usage: ./wordcounts MAX_N_OUT MIN_WORD_LEN MAC_WORD_LEN FILE..." << std::endl;
    return 0;
  }
  if(argc < 5){
    std::cout << "Invalid number of arguments" << std::endl;
    return(0);
  }
  if(!legal_int(argv[1])){
      std::cout << "bad integer value " << argv[1] << " for MAX_N_OUT" << std::endl;
      return(0);
  }

  
  if(!legal_int(argv[2])){
      std::cout << "bad integer value " << argv[2] << " for MIN_WORD_LEN" << std::endl;
      return(0);
  }
  
  if(!legal_int(argv[3])){
      std::cout << "bad integer value " << argv[3] << " for MAX_WORD_LEN" << std::endl;
      return(0);
  }
	
  size_t MAX_N_OUT = std::stoi(argv[1]);
  size_t MIN_WORD_LEN = std::stoi(argv[2]);
  size_t MAX_WORD_LEN = std::stoi(argv[3]);

  if(MIN_WORD_LEN > MAX_WORD_LEN){
    std::cout << "MIN_WORD_LEN " << MIN_WORD_LEN << " is greater than MAX_WORD_LEN " << MAX_WORD_LEN << std::endl;
    return 0;
  }
  std::unordered_map<std::string, int> wordmap;
  
  //iterate through files
  for(int i = 4; i < argc; i ++){
    if(fileExists(argv[i])){
      std::ifstream in(argv[i]);
      while (in.good()){
        std::string w;
        in >> w;
        std::string formatted_w;
        //reformat word
        for(std::string::size_type letter = 0; letter< w.size(); letter++){
	  if(std::isalpha(w[letter])){
	    formatted_w += std::tolower(w[letter]);
	  }
        }
        //add word to map if in parameters
        if(formatted_w.length()>=MIN_WORD_LEN && formatted_w.length()<=MAX_WORD_LEN){
	  wordmap[formatted_w] += 1; 
        }
      }
    }
    else{
      std::cout << "cannot read " << argv[i] << std::endl;
      std::cout << "No such file or directory" << std::endl;
      return 0; 
    }
  }
  //convert to vector and sort
  auto wordCounts = std::vector<WordCount>(wordmap.begin(), wordmap.end());
  sort(wordCounts.begin(), wordCounts.end(), wordCountCompare);
  //print vector items until MAX_N_OUT
  for(size_t i = 0; i < MAX_N_OUT; i++){
    std::cout << wordCounts[i].first << ": " << wordCounts[i].second << std::endl;
  }
}
