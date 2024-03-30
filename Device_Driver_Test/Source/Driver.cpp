/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Driver.cpp
 *  Date: March 28, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: Driver
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Driver.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
using namespace std;
namespace Driver_Development
{
/*****************************************
----=-----    Driver Class     -----------
*****************************************/
/*--------------------------------------*/
void Driver::Write_File(std::string &Message)
{
    Driver_File.open(Driver_Path,std::ios::out);
    if(Driver_File.is_open())
    {
        Driver_File.write(Message.c_str(),Message.size());
        Driver_File.close();
    }
    else
    {
        std::cout<<"File : "<<Driver_Path<<"Not Exists."<<endl;
    }
}
/*--------------------------------------*/
std::string Driver::Read_File(void)
{
    std::string Result{};
    Driver_File.open(Driver_Path,std::ios::in);
    if(Driver_File.is_open())
    {
        std::getline(Driver_File,Result);
        Driver_File.close();
    }
    else
    {
        std::cout<<"File : "<<Driver_Path<<"Not Exists."<<endl;
    }
    return Result;
}
/*--------------------------------------*/
}
/********************************************************************
 *  END OF FILE:  Driver.cpp
********************************************************************/
using namespace Driver_Development;
using namespace std;
int main()
{
    Driver LED{};
    string Input{};
    while(1)
    {
        cout<<"Enter String To Write To File : ";
        getline(cin,Input);
        LED.Write_File(Input);
        Input=LED.Read_File();
        cout<<"Data From File : "<<Input<<endl;
    }
    return 0;
}