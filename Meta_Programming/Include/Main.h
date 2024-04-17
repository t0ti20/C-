/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Company.hpp
 *  Date: November 30, 2023
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: Employee
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _COMPANY_HPP_
#define _COMPANY_HPP_
/******************************************************************/
// #include <string>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Mine
{
/*****************************************
------------ Math Class  -------------
*****************************************/
class Math
{
private:
	double Number_1{10};
	double Number_2{10};
public:
    Math(double Math_Number_1=10,double Math_Number_2=10);
    ~Math();
	double Add(void);
	void Initialization(void);
	void Print(void);
};
/*****************************************
------------- Square Class  --------------
*****************************************/
class Square
{
private:
	double Side_Length{};
public:
	explicit Square(double Square_Side_Length=10);
	double Surface() const;
};
}
/********************************************************************
 *  END OF FILE:  ./Company.hpp
********************************************************************/
#endif