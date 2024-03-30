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
    Driver(void)=default;
    void Write_File(std::string &Message);
    std::string Read_File(void);
private:
    const std::string Driver_Path{"/dev/Control_LED"};
    std::fstream Driver_File{};
};
}
/********************************************************************
 *  END OF FILE:  Driver.h
********************************************************************/
#endif
