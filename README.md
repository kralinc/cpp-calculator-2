# cpp-calculator-2
A calculator in C++ that can evaluate all arithmetic user input, and follows the order of operations. Created May, 2019

I created this project as a way of improving my C++ skills with a program that was fairly straightforward at the outset but was still outside of the scope of what I've tried to do before. This marked the first time I'd used generics, and one of the only times I'd used recursion outside of a classroom programming exercise.

I wanted the program to output the results as cleanly and accurately as possible, so within Calculator::operate() in calc.cpp, I analyzed the output and, if necessary, would change the datatype to more closely match the needed output. For example, if division produced a result ending in .0, it would be returned as an integer. Additionally, if the result would result in integer overflow, it would be returned as a long. The disadvantage of this approach is that math is performed differently on different datatypes. If I were to redo this, I would find a way to convert to scientific notation rather than using long.

Parentheses were handled using recursion, and the order of operations were stored in a list. The program would iterate through the entire string, applying operations to numbers wherever they are found, in order. I learned recently in a programming class that this same effect can be achieved more efficiently with a stack, which I will implement in my next attempt.
