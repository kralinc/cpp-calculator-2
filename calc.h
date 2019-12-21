#if !defined(CALC_H)
#define CALC_H

#include <string>

class Calculator{
    template<typename T>
    std::string calc(T n1, char op, T n2); //Calculate the operation and return the result.
    public: bool isNum(char c); //Determines if the character is a numeral or not.
    std::string operate(std::string s); //Splits the section into 3 parts, calculates the result, and returns it.
    std::string evaluate(std::string s); //Splits the string into sections evaluated by other functions, then compiles and returns the result
    std::string parentheses(std::string s, int start); //Evaluates the statements in parentheses first
    public: std::string result(std::string s); //strips the string, plugs into evaluate(), and returns the result
    
};

#endif
