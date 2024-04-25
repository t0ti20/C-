#include <iostream>
#include "Math.hpp"
class Custom 
{
public:
    Custom(std::string b):m_b{b}{}
    operator float() const { return std::stof(m_b);}
private:
    std::string m_b;
};
int main()
{
    // Test Factorial function
    Custom Number {"5"};
    Math::Calculator calculator;
    std::cout << "Factorial of \"5\" is: " << calculator.Factorial(Number) << std::endl;
    // Test Maximum function
    std::cout << "Maximum value is: " << calculator.Maximum(4,Number,2) << std::endl;
}