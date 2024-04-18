/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Server.hpp
 *  Date: November 30, 2023
 *  Description: 
 *  Class Name: 
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _SERVER_HPP_
#define _SERVER_HPP_
/******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEBUGGING 			1
constexpr int BUFFER_SIZE = 1024;
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
/*****************************************
------------ Math Class  -------------
*****************************************/
class Server_Hadler
{
private:
	int Server_Description{};
	int Client_Description{};
	uint16_t Socket_Number{};
public:
	Server_Hadler(uint16_t Socket_Number);
	~Server_Hadler();
	bool Initialization(void);
	bool Listen(void);
	bool Accept_Client(void);
	bool Write_Message(const std::string &Message);
	bool Read_Message(std::string &Message);
	bool Close_Client(void);
	bool Deinitialization(void);
};

}
/********************************************************************
 *  END OF FILE:  ./Server.hpp
********************************************************************/
#endif