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
/****************************************************************************************************
* Constructor Name: TCP_Client
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Public
* Description     : Constructs a TCP client object and resolves the server's address and port.
* Parameters (in) : Address - The IP address or hostname of the server.
*                 : Port - The port number on which the server is listening.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes the TCP client object with the specified server address and port.
*                 : - It resolves the server's address and port using Boost.Asio resolver.
*****************************************************************************************************/
TCP_Client(const std::string &Address,unsigned int Port);
/****************************************************************************************************
* Function Name   : Run
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Public
* Description     : Initiates asynchronous connection to the server and starts the IO context.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function asynchronously connects to the server using the specified endpoints.
*                 : - Upon successful connection, it initiates asynchronous reading from the server.
*                 : - It runs the IO context to start processing asynchronous operations.
*****************************************************************************************************/
void Run(void);
/****************************************************************************************************
* Function Name   : Stop
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Public
* Description     : Stops the TCP client by closing the socket.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function closes the TCP socket, effectively stopping the client's communication with the server.
*                 : - It ensures proper cleanup of resources associated with the client.
*****************************************************************************************************/
void Stop(void);
/****************************************************************************************************
* Function Name   : Send_Message
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Public
* Description     : Queues a message for sending to the server.
* Parameters (in) : Message - The message to be sent to the server.
* Parameters (out): None
* Return value    : None
* Notes           : - This function adds the message to the message queue and initiates asynchronous writing
*                     if the queue was previously empty.
*****************************************************************************************************/
void Send_Message(const std::string &Message);
private:
/****************************************************************************************************
* Function Name   : Async_Reading
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Private
* Description     : Initiates asynchronous reading from the server until a newline character is encountered.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function asynchronously reads data from the server until a newline character is encountered.
*                 : - It uses the _Buffer member variable to store the received data.
*                 : - Upon completion, it calls the Done_Reading function to handle the received data.
*****************************************************************************************************/
void Async_Reading(void);
/****************************************************************************************************
* Function Name   : Done_Reading
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Private
* Description     : Handles the completion of asynchronous reading from the server.
* Parameters (in) : Error             - Error code indicating the success or failure of the read operation.
*                 : Bytes_Transferred - The number of bytes transferred during the read operation.
* Parameters (out): None
* Return value    : None
* Notes           : - This function is called when the asynchronous read operation completes.
*                 : - If an error occurred during the read operation, it stops the client.
*                 : - If no error occurred, it processes the received message and initiates another
*                     asynchronous read operation to continue receiving data from the server.
*****************************************************************************************************/
void Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred);
/****************************************************************************************************
* Function Name   : Async_Writing
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Private
* Description     : Initiates asynchronous writing of the front message from the message queue.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function asynchronously writes the front message from the message queue to the server.
*                 : - It uses the _Messages member variable to access the message queue.
*                 : - Upon completion, it calls the Done_Writing function to handle the result.
*****************************************************************************************************/
void Async_Writing(void);
/****************************************************************************************************
* Function Name   : Done_Writing
* Class           : TCP_Client
* Namespace       : Socket
* Type            : Private
* Description     : Handles the completion of asynchronous writing to the server.
* Parameters (in) : Error             - Error code indicating the success or failure of the write operation.
*                 : Bytes_Transferred - The number of bytes transferred during the write operation.
* Parameters (out): None
* Return value    : None
* Notes           : - This function is called when the asynchronous write operation completes.
*                 : - If an error occurred during the write operation, it closes the connection.
*                 : - If no error occurred, it removes the front message from the message queue
*                     and initiates another asynchronous write operation if the queue is not empty.
*****************************************************************************************************/
void Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred);
public:
	/* Callback function for handling received messages from clients. */
	Message_Handler Message_Received;
private:
	/* The Boost.Asio IO context for managing asynchronous operations. */
	boost::asio::io_context _IO_Context;
	/* The Boost.Asio TCP socket for communication with the server. */
	boost::asio::ip::tcp::socket _Socket;
	/* The resolved endpoints of the server to establish a connection. */
	boost::asio::ip::tcp::resolver::results_type _Endpoints;
	/* The Boost.Asio stream buffer for storing received data. */
	boost::asio::streambuf _Buffer{65536};
	/* The queue of messages to be sent to the server. */
	std::queue<std::string> _Messages;
};

}
/********************************************************************
 *  END OF FILE:  ./Client.hpp
********************************************************************/
#endif