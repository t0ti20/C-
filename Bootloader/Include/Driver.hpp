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
#include <vector>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/asio.hpp>

#define ENABLE_DEBUG 2
/*****************************************
---------    Configurations     ----------
*****************************************/
unsigned char constexpr Bootloader_State_ACK{1};
unsigned int constexpr Sending_Delay_MS{100};
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Bootloader
{
/*****************************************
------------    CRC_Manage     -----------
*****************************************/
class CRC_Manage
{
protected:
    void Append_CRC(std::vector<unsigned char> &Data);
private:
    unsigned int CRC_Calculate(const std::vector<unsigned char> &Data);
};
/*****************************************
-----------    Serial Port     -----------
*****************************************/
class Serial_Port : private CRC_Manage
{
protected:
    Serial_Port(const std::string& Device_Location);
    void Write_Data(const unsigned char Data);
    unsigned char Read_Data(void);
    void Read_Data(size_t Size);
    void Write_Data(void);
protected:
    std::vector<unsigned char> Data_Buffer{};
private:
    boost::asio::io_service Input_Output;
    boost::asio::serial_port Port;
};
/*****************************************
------------    Services     -------------
*****************************************/
class Services : protected Serial_Port 
{
private:
    enum Bootloader_Command_t 
    {
        Bootloader_Command_Get_Help       =(1),
        Bootloader_Command_Get_ID         =(2),
        Bootloader_Command_Get_Version    =(3),
        Bootloader_Command_Erase_Flash     =(4),
        Bootloader_Command_Write_Flash     =(5),
        Bootloader_Command_Address_Jump    =(6)
    };
protected:
    Services(const std::string& Device_Location);
    void Get_Version(void);
    void Get_Help(void);
    void Get_ID(void);
    void Jump_Address(void);
    void Erase_Flash(void);
    void Write_Flash(void);
    void Jump_Address(unsigned int &Address);
    void Erase_Flash(unsigned int &Start_Page,unsigned int &Pages_Count);
    void Write_Flash(unsigned int &Start_Page,std::vector<unsigned char> &Payload);
private:
    bool Get_Acknowledge(void);
    void Update_Buffer(void);
    bool Send_Frame(Bootloader_Command_t Service);
    bool Send_Frame(std::vector<unsigned char> &Data);
    bool Send_Frame(Bootloader_Command_t Service,std::vector<unsigned char> &Data);
    bool Read_File(std::vector<unsigned char> &Binary_File);
private:
    std::string File_Location{"./Binary.bin"};
};
/*****************************************
---------    User Interface     ----------
*****************************************/
class User_Interface : private Services
{
public:
    User_Interface(const std::string& User_Interface_File);
    static void Start_Application(void);
public:
};
}
/********************************************************************
 *  END OF FILE:  Driver.h
********************************************************************/
#endif
