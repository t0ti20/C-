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
#include "Driver.hpp"
#include <thread>
#include <chrono>
/*****************************************
----------    Button Class     -----------
*****************************************/
class Button
{   
private:
    static char Current_State;
public:
    static void Notify_On_Change(char Input);
};
/*--------------------------------------*/
char Button::Current_State{'1'};
/*--------------------------------------*/
void Button::Notify_On_Change(char Input)
{
    if(Input!=Current_State)
    {
        std::cout<<((Input=='0')?std::string{"Button Is Pressed"}:std::string{"Button Is Released"})<<std::endl;
        Current_State=Input;
    }
}
/*--------------------------------------*/
int main()
{
    Driver_Development::Driver LED_Driver{"/dev/Control_LED"};
    Driver_Development::Driver Button_Driver{"/dev/Control_Button"};
    int Input{};
    std::cout<<"Enter Blink Delay (ms) : ";
    std::cin>>Input;
    while(1)
    {
        if(Button_Driver.Read_File()!="1")
        {
            Button::Notify_On_Change('0');
            LED_Driver.Write_File("1",1);
            std::this_thread::sleep_for(std::chrono::milliseconds(Input));
            LED_Driver.Write_File("0",1);
            std::this_thread::sleep_for(std::chrono::milliseconds(Input));
        }
        else 
        {LED_Driver.Write_File("0",1);Button::Notify_On_Change('1');}
    }
    return 0;
}
/********************************************************************
 *  END OF FILE:  Application.cpp 
********************************************************************/