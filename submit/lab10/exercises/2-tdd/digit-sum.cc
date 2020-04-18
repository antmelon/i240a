#include <cctype>

#include "digit-sum.hh"

int
digitSum(const char* str)
{
    bool wantsDigit = true;
    int acc = 0;
    for(const char * p = str; p; ++p){
	int c = *p;
        if (isdigit(c)) {
	    if(wantsDigit){
                acc += (*p - '0');
		wantsDigit = false;
	    }
	    else{
	        break;
	    }
	}
	else if (c == '+'){
	    if (wantsDigit) break;
	    wantsDigit = true;
	}
	else if (isspace(c)) {
            continue;
	}
	else{
            break;
	}
    }
    return acc;
}
