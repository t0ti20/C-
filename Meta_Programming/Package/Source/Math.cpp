/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Math.cpp
 *  Date: January 02, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: math
 *  (C) 2024 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Math.hpp"
#include <iostream>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Math
{
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
Calculator::Calculator(){std::cout<<"Welcome To My Calculator"<<std::endl;}
/****************************************************************************************************
* Destructor Name : ~Calculator
* Class           : Calculator
* Namespace       : Math
* Type            : Private
* Description     : Destructs a Calculator object and displays an end message.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : Displays an end message upon object destruction.
*****************************************************************************************************/
Calculator::~Calculator(){std::cout<<"End Of My Calculator"<<std::endl;}
}
/********************************************************************
 *  END OF FILE:  ./Math.cpp
********************************************************************/
