#include <iostream>

int main(int argc, char *argv[]){
	if(argc < 4){
		std::cout << "Invalid number of arguments" << std::endl;
		return(0);
	}
	int MAX_N_OUT = argv[1];
	int MIN_WORD_LEN = argv[2];
	int MAX_WORD_LEN = argv[3];
	

	//validate inputs
	if(MAX_N_OUT != int(MAX_N_OUT)){
		std::cout << "bad integer value " << MAX_N_OUT << " for MAX_N_OUT" << endl;
		return(0);
	}
	else if(MIN_WORD_LEN != int(MIN_WORD_LEN)){
		std::cout << "bad integer value " << MIN_WORD_LEN << " for MIN_WORD_LEN" << endl;
		return(0);
	}
	else if(MAX_WORD_LEN != int(MAX_WORD_LEN)){
		std::cout << "bad integer value " << MAX_WORD_LEN << " for MAX_WORD_LEN" << endl;
	}

}
