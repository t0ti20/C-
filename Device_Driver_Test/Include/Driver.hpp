/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Driver.h
 *  Date: March 28, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: Driver
 *  (C) 2024 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _DRIVER_HPP_
#define _DRIVER_HPP_
/******************************************************************/
/*****************************************
------------    Includes     -------------
*****************************************/
#include <iostream>
#include <fstream>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Driver_Development
{
class Driver
{
public:
    Driver(std::string Driver_Path);
    void Write_File(const char *Message,size_t Size);
    void Write_File(const std::string &Message);
    std::string Read_File(void);
private:
    std::string Path{};
    std::fstream File{};
};
}
/********************************************************************
 *  END OF FILE:  Driver.h
********************************************************************/
#endif
