/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Math.hpp
 *  Date: January 02, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: math
 *  (C) 2024 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _MATH_HPP_
#define _MATH_HPP_
/******************************************************************/
/*****************************************
------------    Includes     -------------
*****************************************/
#include <type_traits>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Math
{
class Calculator
{
private:
/****************************************************************************************************
* Function Name     : Maximum
* Class Name        : (None)
* Namespace         : (None)
* Type              : Private
* Description       : Returns the maximum value of a single argument.
* Parameters (in)   : Number - The number to be compared.
* Parameters (out)  : None
* Return value      : The value of the input argument.
* Notes             : This function serves as a base case for the Maximum function template.
*****************************************************************************************************/
template <typename Type_1> 
Type_1 Maximum(Type_1 Number) 
{
     return Number;
}
/****************************************************************************************************
* Function Name     : Minimum
* Class Name        : (None)
* Namespace         : (None)
* Type              : Private
* Description       : Returns the minimum value of a single argument.
* Parameters (in)   : Number - The number to be compared.
* Parameters (out)  : None
* Return value      : The value of the input argument.
* Notes             : This function serves as a base case for the Minimum function template.
*****************************************************************************************************/
template <typename Type_1> 
Type_1 Minimum(Type_1 Number) 
{
     return Number;
}
public:
/****************************************************************************************************
* Destructor Name : ~Calculator
* Class           : Calculator
* Namespace       : Math
* Type            : Public
* Description     : Destructs a Calculator object and displays an end message.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : Displays an end message upon object destruction.
*****************************************************************************************************/
~Calculator();
/****************************************************************************************************
* Constructor Name: Calculator
* Class           : Calculator
* Namespace       : Math
* Type            : Public
* Description     : Constructs a Calculator object and displays a welcome message.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : Displays a welcome message upon object creation.
*****************************************************************************************************/
Calculator();
/****************************************************************************************************
* Function Name     : Factorial
* Class Name        : Calculator
* Namespace         : Math
* Type              : Public
* Description       : Calculates the factorial of a given number.
* Parameters (in)   : Number - The number whose factorial is to be calculated.
* Parameters (out)  : None
* Return value      : Factorial of the given number.
* Notes             : - The function uses recursion to calculate the factorial.
*                   : - It performs a static assertion to ensure that the argument is of arithmetic type.
*****************************************************************************************************/
template<typename Type>
Type Factorial(Type Number)
{
     static_assert(std::is_convertible_v<Type,float>);
     return (Number>0)?Factorial(Number-1)*Number:1;
}
/****************************************************************************************************
* Function Name     : Maximum
* Class Name        : Calculator
* Namespace         : Math
* Type              : Public
* Description       : Returns the maximum value among the provided arguments.
* Parameters (in)   : Number - The number whose maximum value is to be determined.
* Parameters (out)  : None
* Return value      : The maximum value among the provided arguments.
* Notes             : - This function template is overloaded.
*                   : - The first overload returns the maximum value of a single argument.
*                   : - The second overload returns the maximum value among multiple arguments.
*                   : - It performs static assertions to ensure that all arguments are of arithmetic types.
*****************************************************************************************************/
template<typename Type_1,typename... Types>
auto Maximum(Type_1 First_Number,Types... Arguments) 
{
     static_assert(((std::is_arithmetic_v<Types> or std::is_convertible_v<Types, float>) and ... ), "Arguments must be arithmetic types");
     return (First_Number>Maximum(Arguments...)?First_Number:Maximum(Arguments...));
}
/****************************************************************************************************
* Function Name     : Minimum
* Class Name        : Calculator
* Namespace         : Math
* Type              : Public
* Description       : Returns the minimum value among the provided arguments.
* Parameters (in)   : Number - The number whose minimum value is to be determined.
* Parameters (out)  : None
* Return value      : The minimum value among the provided arguments.
* Notes             : - This function template is overloaded.
*                   : - The first overload returns the minimum value of a single argument.
*                   : - The second overload returns the minimum value among multiple arguments.
*                   : - It performs static assertions to ensure that all arguments are of arithmetic types.
*****************************************************************************************************/
template<typename Type_1,typename... Types>
auto Minimum(Type_1 First_Number,Types... Arguments) 
{
     static_assert(((std::is_arithmetic_v<Types> or std::is_convertible_v<Types, float>) and ...), "Arguments must be arithmetic types");
     return (First_Number<Minimum(Arguments...)?First_Number:Minimum(Arguments...));
}
/****************************************************************************************************
* Function Name     : Subtraction
* Class Name        : Calculator
* Namespace         : Math
* Type              : Public
* Description       : Performs subtraction operation on the provided arguments.
* Parameters (in)   : Arguments - The numbers to be subtracted.
* Parameters (out)  : None
* Return value      : Result of the subtraction operation.
* Notes             : - The function template accepts a variadic number of arguments.
*                   : - It performs static assertions to ensure that all arguments are of arithmetic types.
*****************************************************************************************************/
template<typename... Types>
auto Subtraction(Types... Arguments)
{
     static_assert(((std::is_arithmetic_v<Types> or std::is_convertible_v<Types, float>) && ...), "Arguments must be arithmetic types");
     return ( ... - Arguments );
}
/****************************************************************************************************
* Function Name     : Summation
* Class Name        : Calculator
* Namespace         : Math
* Type              : Public
* Description       : Performs summation operation on the provided arguments.
* Parameters (in)   : Arguments - The numbers to be summed up.
* Parameters (out)  : None
* Return value      : Result of the summation operation.
* Notes             : - The function template accepts a variadic number of arguments.
*                   : - It performs static assertions to ensure that all arguments are of arithmetic types.
*****************************************************************************************************/
template<typename... Types>
auto Summation(Types... Arguments)
{
     static_assert(((std::is_arithmetic_v<Types> or std::is_convertible_v<Types, float>) && ...), "Arguments must be arithmetic types");
     return ( ... + Arguments );
}
private:
protected:
};
}
/********************************************************************
 *  END OF FILE:  ./Math.hpp
********************************************************************/
#endif
