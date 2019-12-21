#include <string>
#include <iostream> //remove after debugging
#include "calc.h"

template<typename T>
std::string Calculator::calc(T n1, char op, T n2){
	int p = n1;
	bool negative = false;
    switch (op){
        case '^':
            if (n2 == 0){
                return "1";
            }
            if (n2 < 0){
				n2 *= -1;
				negative = true;
			}
            for (int i = 0; i < n2-1; ++i){
                n1 *= p;
            }
            if (negative){
				n1 = 1/n1;
			}
            return std::to_string(n1);
        case '*':
            return std::to_string((n1 * n2));
        case '/':
            return std::to_string((n1 / n2));
        case '%':
			return std::to_string(((int)n1 % (int)n2));
        case '+':
            return std::to_string((n1 + n2));
        case '-':
            return std::to_string((n1 - n2));
        default:
            throw std::exception();
    }
}

bool Calculator::isNum(char c){
    return (((int)c > 47 && (int)c < 58) || c == '.');
}

//The string received is formatted like "123*456"
std::string Calculator::operate(std::string s){

    int ss = s.size();

    std::string n1;
    char op;
    std::string n2;

    for (int i = 1; i < ss; ++i){
        if (!isNum(s[i])){
            n1 = s.substr(0,i);
            op = s[i];
            n2 = s.substr(i+1, ss-i);
            //std::cout << n1 << " " << op << " " << n2 << std::endl;//debug
            break;
        }
    }
    
    //These bits convert the data to the correct datatype to prevent overflows and get the most accurate answer.
    if ((n1.size() >= 10 || n2.size() >= 10) && (op == '+' || op == '*')){
        return calc(std::stol(n1), op, std::stol(n2));
    }
    
    if ((n1.size() >= 4  || std::stoi(n2) >= 30) && op == '^'){
		return calc(std::stol(n1), op, std::stol(n2));
	}

    if (op == '/'){
        return calc(std::stod(n1), op, std::stod(n2));
    }

    return calc(std::stof(n1), op, std::stof(n2));

}

//This receives the entire command, just with spaces removed, and splits them into 2 operand chunks, following PEMDAS.
std::string Calculator::evaluate(std::string s){

	char operands[] = {'^', '*', '/', '%', '+', '-'};
	int strSize = s.size();
	//6 is the number of valid operations
    for (int i = 0; i < 6; ++i){
		for (int j = 1; j < strSize; ++j){
			if (s[j] == operands[i]){
				
				int back = j-1;
				while (back >= 0 && isNum(s[back-1])){
					--back;
				}
				if ((back>1 && !isNum(s[back-2])) || back==1){
					--back;
				}
				
				
				int forward = j+1;
				while (forward < strSize-1 && isNum(s[forward+1])){
					++forward;
				}
				
				forward -= (back-1);
				
				//std::cout << s.substr(back, forward) << std::endl;//debug
				std::string thisOperation = operate(s.substr(back, forward));
				//std::cout << thisOperation << std::endl;//debug
				s.replace(back, forward, thisOperation);
				//std::cout << s << std::endl;//debug
				strSize = s.size();
				j = 1;
			}
		}
	}

    return s;
}

std::string Calculator::parentheses(std::string s, int start){
			if (start-1 >= 0 && isNum(s[start-1])){
				s[start] = '*';
				++start;
			}else{
				s.erase(start,1);
			}
			int back = start;
			int forward = start+1;
			while (forward < s.size() && s[forward] != ')'){
				++forward;
				if (s[forward] == '('){
					s = parentheses(s, forward);
				}
			}
			s.erase(forward,1);
			s.replace(back, forward, evaluate(s.substr(back, forward-1)));
	
	return s;
}

std::string Calculator::result(std::string s){
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == ' '){
			s.erase(i,1);
			--i;
		}
	}
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == '('){
			s = parentheses(s, i);
		}
	}
	s = evaluate(s);
	return s;
}
