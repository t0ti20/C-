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
#include "Bootloader_Host.hpp"
constexpr const char GPIO_Pin[]                 {"18"};
constexpr const char Serial_Driver[]            {"/dev/ttyS0"};
/*****************************************
----------   Main Application   ----------
*****************************************/
int main() 
{
    using namespace Bootloader;
    User_Interface Terminal{Serial_Driver,GPIO_Pin};
    Terminal.Start_Application();
    return 0;
}
/********************************************************************
 *  END OF FILE:  Application.cpp 
********************************************************************/