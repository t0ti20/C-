/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Application.cpp
 *  Date: March 28, 2024
 *  Description: Testing Application For Device Driver
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../Include/Driver.hpp"
/*****************************************
----------   Main Application   ----------
*****************************************/
int main() 
{
    using namespace Bootloader;
    User_Interface::Start_Application();
    return 0;
}
/********************************************************************
 *  END OF FILE:  Application.cpp 
********************************************************************/