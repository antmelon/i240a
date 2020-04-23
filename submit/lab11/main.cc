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
       	        stkIndex--;
	        return stk[stkIndex];
	    }
	    else{
                std::cout << "Cannot pop. Stack is empty" << std::endl;
		std::exit(1);
	    }
	}

        int size(){
            return stkIndex;
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
        for(int i = 1; i < argc; i++){
            if(strlen(argv[i]) == 1){
		if(getDelim(argv[i][0])== 0){
                    std::cout << "invalid delimeter " << argv[i][0] << std::endl;
		    std::exit(1);
		}
		if(getDelim(argv[i][0]) > 0){
		    s.push(getDelim(argv[i][0]));
		}
		if(getDelim(argv[i][0]) < 0){
                    if(s.size()==0){
			    std::cout << "unbalanced at argument" << i << std::endl;
			    std::exit(1);
		    }
		    else{
                        int popVal = s.pop();
			if(popVal != getDelim(argv[i][0])*-1){
			    std::cout << "unbalanced at argument " << i << std::endl;
			}
	            }
		    
		}
	    }
	    else{
                std::cout << "Multiple character argument: " << argv[i][0] << std::endl;
		std::exit(1);
	    }
	}
        if(s.size()==0){
            std::exit(0);
	}
	else{
            std::cout << "Unbalanced at argument " << argc-1 << std::endl;
	    std::exit(1);
	}
    }
    catch(const std::logic_error& e){
        std::cerr << "usage: " << std::endl;
	std::cout << "Invalid argument(s) detected " << e.what() << std::endl;
    }
}
