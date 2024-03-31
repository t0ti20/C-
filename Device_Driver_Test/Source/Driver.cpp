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
----------    Driver Class     -----------
*****************************************/
/*--------------------------------------*/
Driver::Driver(std::string Driver_Path):Path{Driver_Path}{}
/*--------------------------------------*/
void Driver::Write_File(const char *Message,size_t Size)
{
    File.open(Path,std::ios::out);
    if(File.is_open())
    {
        File.write(Message,Size);
        File.close();
    }
    else
    {
        std::cout<<"File : "<<Path<<"Not Exists."<<endl;
    }
}
void Driver::Write_File(const std::string &Message)
{
    File.open(Path,std::ios::out);
    if(File.is_open())
    {
        File.write(Message.c_str(),Message.size());
        File.close();
    }
    else
    {
        std::cout<<"File : "<<Path<<"Not Exists."<<endl;
    }
}
/*--------------------------------------*/
std::string Driver::Read_File(void)
{
    std::string Result{};
    File.open(Path,std::ios::in);
    if(File.is_open())
    {
        std::getline(File,Result);
        File.close();
    }
    else
    {
        std::cout<<"File : "<<Path<<"Not Exists."<<endl;
    }
    return Result;
}
/*--------------------------------------*/
}
/********************************************************************
 *  END OF FILE:  Driver.cpp
********************************************************************/