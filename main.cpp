#include <string>
#include <iostream>
#include "calc.h"

int main(){
	
	Calculator c;
    std::string input;
    std::string oldInput = "";
    std::string function = "";
    std::string r;
    
    while (true){
		std::getline(std::cin, input);
		
		if (input.substr(0,4).compare("quit") == 0 || input.substr(0,4).compare("exit") == 0){
			break;
		}else if (!(oldInput.compare("") == 0) && input.substr(0,3).compare("ans") == 0){
			input.replace(0, 3, oldInput);
		}else if (input.substr(0,5).compare("func ") == 0){
			function.assign(input.substr(4, input.size()-1));
			input = "";
		}else if (input.substr(0,5).compare("eval ") == 0){
			
			input.erase(0,5);
			std::string variable = input;
			if (variable.compare("ans") == 0){
				variable.assign(oldInput);
			}
			input.assign(function);
			
			int varSize = variable.size();
			for (int i = 0; i < input.size(); ++i){
				if (input[i] == 'x'){
					input.replace(i, varSize, variable);
				}
			}
			
		}
		
		
		try{
			r = c.result(input);
			std::cout << "Result: " << r << std::endl;
		}catch(std::exception& e){
			std::cout << "Invalid Input: " << e.what() << std::endl;
		}
		
		oldInput.assign(r);
	}
	
    return 0;
}
