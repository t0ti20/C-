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
#include <experimental/optional>
#include <boost/asio.hpp>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <memory>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
	using msghmndler=std::function<void(std::string)>;
	using error=std::function<void(void)>;
/*****************************************
----------    TCP_Connection     ---------
*****************************************/
class TCP_Connection: public std::enable_shared_from_this<TCP_Connection>
{
public:
	static std::shared_ptr<TCP_Connection> Create(boost::asio::ip::tcp::socket &&Socket)
	{
		return std::shared_ptr<TCP_Connection> (new TCP_Connection(std::move(Socket)));
	}
	boost::asio::ip::tcp::socket &Socket(void);
	void Run(std::function<void(std::string)> &&Message_Handler,std::function<void(void)> &&Error_Handler);
	std::string Print_Username(void)
	{
		return _Username;
	}
	void Send_Message(const std::string &Message);
private:
	explicit TCP_Connection(boost::asio::ip::tcp::socket &&Socket);
	void Async_Reading(void);
	void Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred);
	void Async_Writing(void);
	void Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred);
private:
	boost::asio::streambuf _Buffer{65536};
	boost::asio::ip::tcp::socket _Socket;
	std::queue<std::string> _Messages{};
	std::string _Username{};
	std::function<void(std::string)> _Message_Handler;
	std::function<void(void)> _Error_Handler;
};
/*****************************************
------------    TCP_Server     -----------
*****************************************/
class TCP_Server
{
public:
	TCP_Server(unsigned int Port_Number);
	bool Run(void);
	void Broadcast(const std::string &Message);
private:
	void _Start_Accept(void);
private:
	unsigned int _Port_Number;
	boost::asio::io_context _IO_Context;
	boost::asio::ip::tcp::acceptor _Acceptor;
	std::experimental::optional<boost::asio::ip::tcp::socket> _Socket;
	std::unordered_set<std::shared_ptr<TCP_Connection>> _Connections{};
public:
	std::function<void(std::shared_ptr<TCP_Connection>)> Client_Connected;
	std::function<void(std::shared_ptr<TCP_Connection>)> Client_Disconnected;
	std::function<void(std::string)> Client_Received;
};

}
/********************************************************************
 *  END OF FILE:  ./Server.hpp
********************************************************************/
#endif