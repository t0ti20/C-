/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Client.hpp
 *  Date: March 20, 2024
 *  Description: This file contains the declaration of the TCP_Server class, which represents a TCP .
 *  Class Name:  TCP_Server
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
/******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../Connectios/Connections.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
	using Message_Handler=std::function<void(std::string)>;
/*****************************************
------------    TCP_Client     -----------
*****************************************/
class TCP_Client
{
public:
	TCP_Client(const std::string &Address,unsigned int Port);
	void Run(void);
	void Stop(void);
	void Send_Message(const std::string &Message);
private:
	void Async_Reading(void);
	void Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred);
	void Async_Writing(void);
	void Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred);
public:
	/* Callback function for handling received messages from clients. */
	Message_Handler Message_Received;
private:
	boost::asio::io_context _IO_Context;
	boost::asio::ip::tcp::socket _Socket;
	boost::asio::ip::tcp::resolver::results_type _Endpoints;
	boost::asio::streambuf _Buffer{65536};
	std::queue<std::string> _Messages;

};

}
/********************************************************************
 *  END OF FILE:  ./Client.hpp
********************************************************************/
#endif