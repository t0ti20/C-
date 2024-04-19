/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Server.hpp
 *  Date: March 20, 2024
 *  Description: This file contains the declaration of the TCP_Server class, which represents a TCP .
 *  Class Name:  TCP_Server
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _SERVER_HPP_
#define _SERVER_HPP_
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
	using Connection_Pointer=std::shared_ptr<TCP_Connection>;
	using Connection_Handler=std::function<void(Connection_Pointer)>;
	using Message_Handler=std::function<void(std::string)>;
/*****************************************
------------    TCP_Server     -----------
*****************************************/
class TCP_Server
{
public:
/****************************************************************************************************
* Constructor Name: TCP_Server
* Class           : TCP_Server
* Namespace       : Socket
* Type            : Public
* Description     : Constructs a TCP server object and initializes the acceptor to listen on the specified port.
* Parameters (in) : Port_Number - The port number on which the server will listen for incoming connections.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes the TCP server object with the specified port number.
*                 : - It creates an acceptor object and binds it to the specified port for accepting incoming connections.
*****************************************************************************************************/
TCP_Server(unsigned int Port_Number);
/****************************************************************************************************
* Function Name   : Run
* Class           : TCP_Server
* Namespace       : Socket
* Type            : Public
* Description     : Runs the TCP server to start accepting incoming connections.
* Parameters (in) : None
* Parameters (out): None
* Return value    : bool - True if the server runs successfully, false otherwise.
* Notes           : - This function starts accepting incoming connections and runs the IO context.
*                 : - It catches any exceptions that occur during execution and prints an error message.
*****************************************************************************************************/
bool Run(void);
/****************************************************************************************************
* Function Name   : Broadcast
* Class           : TCP_Server
* Namespace       : Socket
* Type            : Public
* Description     : Sends a message to all connected clients.
* Parameters (in) : Message - The message to be broadcasted to all connected clients.
* Parameters (out): None
* Return value    : None
* Notes           : - This function iterates through all connected clients and sends the provided message to each of them.
*                 : - It uses the Send_Message function of each TCP_Connection object to send the message.
*****************************************************************************************************/
void Broadcast(const std::string &Message);
private:
/****************************************************************************************************
* Function Name   : _Start_Accept
* Class           : TCP_Server
* Namespace       : Socket
* Type            : Private
* Description     : Initiates asynchronous accept operations to accept incoming connections.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function is called internally to start accepting incoming connections asynchronously.
*                 : - Upon accepting a connection, it creates a TCP_Connection object and adds it to the list of connections.
*                 : - It also sets up message and error handlers for the connection and initiates its Run function.
*****************************************************************************************************/
void _Start_Accept(void);
public:
	/* Callback function for handling client connection events. */
	Connection_Handler Client_Connected;
	/* Callback function for handling client disconnection events. */
	Connection_Handler Client_Disconnected;
	/* Callback function for handling received messages from clients. */
	Message_Handler Message_Received;
private:
	/* The port number on which the server listens for incoming connections. */
	unsigned int _Port_Number;
	/* The Boost.Asio IO context for managing asynchronous operations. */
	boost::asio::io_context _IO_Context;
	/* The Boost.Asio acceptor object for accepting incoming connections. */
	boost::asio::ip::tcp::acceptor _Acceptor;
	/* An optional Boost.Asio TCP socket for accepting connections. */
	std::experimental::optional<boost::asio::ip::tcp::socket> _Socket;
	/* A set of shared pointers to TCP_Connection objects representing connected clients. */
	std::unordered_set<Connection_Pointer> _Connections{};
};

}
/********************************************************************
 *  END OF FILE:  ./Server.hpp
********************************************************************/
#endif