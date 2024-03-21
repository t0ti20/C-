/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Print.hpp
 *  Date: November 30, 2023
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: Print
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
------------    Include     --------------
*****************************************/
#include <iostream>
#include <unistd.h>
#include <string>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Mine
{
class Print
{
public:
     Print(){std::cout<<Welcome_Message<<std::endl;}
     ~Print(){std::cout<<Exit_Message<<std::endl;}
     void Busy_Test(void)
     {
          while(true)
          {
               std::cout<<"Hello World !"<<std::endl;
               sleep(5);
          }
     }
private:
     std::string Welcome_Message{"Starting Hello World Application !"};
     std::string Exit_Message{"Ending My Application"};
protected:
};
}
/********************************************************************
 *  END OF FILE:  ./Print.hpp
********************************************************************/
