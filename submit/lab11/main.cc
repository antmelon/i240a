#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstring>

class Stack{
    public:
	std::array<int,16> stk;
	int stkIndex = 0;

	void push(std::size_t in){
            if(stkIndex == 15){
		std::cout << "Can not add to stack. Stack is full" << std::endl;
		std::exit(1);
	    }
	    else{
	        stk[stkIndex] = in;
		stkIndex++;
	    }
	}

	int pop(){
	    if(stkIndex != 0){    
                int temp = stkIndex;
       	        stkIndex--;
	        return stk[temp];
	    }
	    else{
                std::cout << "Cannot pop. Stack is empty" << std::endl;
		std::exit(1);
	    }
	}

        int size(){
            return stkIndex + 1;
	}

};

struct DelimMap {
    int delim;
    int encoding;
};

int getDelim(int c){
	DelimMap delimEncodings[] {
        {'(', 1},
	{')', -1},
	{'[', 2},
	{']', -2},
	{'<', 3},
	{'>', -3},
	{'{', 4},
	{'}', -4}
    };

    for(std::size_t i = 0; i < sizeof(delimEncodings)/sizeof(DelimMap); i++){
        if(c == delimEncodings[i].delim){
            return delimEncodings[i].encoding;
	}
    }
    return 0;
}

int main(int argc, const char * argv[]){
    Stack s;
    if(argc < 3){
        std::cerr << "Invalid Number of Args" << std::endl;
	std::exit(1);
    }
    try{
        for(std::size_t i = 1; i < sizeof(argv)/sizeof(argv[0]); i++){
            if(strlen(argv[i]) == 1 && getDelim(argv[i][0]) != 0){
                int currDelim = getDelim(argv[i][0]);
		if(currDelim > 0){
	     	    s.push(currDelim);
	        }
	        else{
                    if(s.stk.size() == 0){
                        std::exit(1);
		    }
		    else{
                        int popval = s.pop();
		        if(popval != currDelim/-1){
			    std::exit(1);
			}	
		    }
		}
	    }
	}
	if(s.size()-1 == 0 ){
            std::exit(0);
	}
	else{
            std::exit(1);
	}
    }
    catch(const std::logic_error& e){
        std::cerr << "usage: " << std::endl;
	std::cout << "Invalid argument(s) detected " << e.what() << std::endl;
    }
}
