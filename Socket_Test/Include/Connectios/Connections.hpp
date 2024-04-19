/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Connections.hpp
 *  Date: November 30, 2023
 *  Description: This file contains the declaration of the TCP_Connection class, which represents a TCP 
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
#ifndef _CONNECTIONS_HPP_
#define _CONNECTIONS_HPP_
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
/*****************************************
----------    TCP_Connection     ---------
*****************************************/
class TCP_Connection: public std::enable_shared_from_this<TCP_Connection>
{
public:
/****************************************************************************************************
* Function Name   : Create
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Public
* Description     : Creates a new TCP_Connection object using a move-constructed socket.
* Parameters (in) : Socket - A rvalue reference to a boost::asio::ip::tcp::socket object.
* Parameters (out): None
* Return value    : std::shared_ptr<TCP_Connection> - A shared pointer to the newly created TCP_Connection object.
* Notes           : - This function creates a new instance of TCP_Connection by moving the provided socket.
*                 : - The newly created TCP_Connection object is managed by a shared pointer to enable shared ownership.
*****************************************************************************************************/
static std::shared_ptr<TCP_Connection> Create(boost::asio::ip::tcp::socket &&Socket);
/****************************************************************************************************
* Function Name   : Print_Username
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Public
* Description     : Returns the username associated with this TCP connection.
* Parameters (in) : None
* Parameters (out): None
* Return value    : std::string - The username associated with this TCP connection.
* Notes           : - This function retrieves and returns the username stored in the private member variable _Username.
*****************************************************************************************************/
std::string Print_Username(void);
/****************************************************************************************************
* Function Name   : Socket
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Public
* Description     : Returns a reference to the underlying boost::asio::ip::tcp::socket object associated with this TCP connection.
* Parameters (in) : None
* Parameters (out): None
* Return value    : boost::asio::ip::tcp::socket& - A reference to the underlying socket object.
* Notes           : - This function allows access to the underlying socket object for performing socket-related operations.
*****************************************************************************************************/
boost::asio::ip::tcp::socket &Socket(void);
/****************************************************************************************************
* Function Name   : Run
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Public
* Description     : Initiates asynchronous reading on the TCP connection.
* Parameters (in) : Message_Handler - A rvalue reference to a function that handles incoming messages.
*                 : Error_Handler - A rvalue reference to a function that handles errors.
* Parameters (out): None
* Return value    : None
* Notes           : - This function sets the message and error handlers, then starts asynchronous reading.
*****************************************************************************************************/
void Run(std::function<void(std::string)> &&Message_Handler,std::function<void(void)> &&Error_Handler);
/****************************************************************************************************
* Function Name   : Send_Message
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Public
* Description     : Queues a message to be sent over the TCP connection.
* Parameters (in) : Message - A reference to the message to be sent.
* Parameters (out): None
* Return value    : None
* Notes           : - This function adds the message to the message queue and starts asynchronous writing if the queue was empty.
*****************************************************************************************************/
void Send_Message(const std::string &Message);
private:
/****************************************************************************************************
* Constructor Name: TCP_Connection
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Private
* Description     : Constructs a TCP_Connection object with a move-constructed socket.
* Parameters (in) : Socket - A rvalue reference to a boost::asio::ip::tcp::socket object.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes the TCP_Connection object with the provided socket.
*                 : - It retrieves the remote endpoint of the socket and initializes the _Username member variable.
*****************************************************************************************************/
explicit TCP_Connection(boost::asio::ip::tcp::socket &&Socket);
/****************************************************************************************************
* Function Name   : Async_Reading
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Private
* Description     : Initiates asynchronous reading from the TCP connection until encountering a newline character.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function uses boost::asio::async_read_until to asynchronously read data until a newline character is encountered.
*                 : - Upon completion, it calls the Done_Reading function.
*****************************************************************************************************/
void Async_Reading(void);
/****************************************************************************************************
* Function Name   : Done_Reading
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Private
* Description     : Handles completion of asynchronous reading operation.
* Parameters (in) : Error - A reference to a boost::system::error_code object indicating any errors that occurred during the operation.
*                 : Bytes_Transferred - The number of bytes transferred during the operation.
* Parameters (out): None
* Return value    : None
* Notes           : - This function is called upon completion of an asynchronous read operation.
*                 : - It checks for errors and closes the connection if an error occurred.
*                 : - If no error occurred, it processes the received message and initiates another asynchronous read operation.
*****************************************************************************************************/
void Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred);
/****************************************************************************************************
* Function Name   : Async_Writing
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Private
* Description     : Initiates asynchronous writing to the TCP connection.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function uses boost::asio::async_write to asynchronously write the front message from the message queue.
*                 : - Upon completion, it calls the Done_Writing function.
*****************************************************************************************************/
void Async_Writing(void);
/****************************************************************************************************
* Function Name   : Done_Writing
* Class           : TCP_Connection
* Namespace       : Socket
* Type            : Private
* Description     : Handles completion of asynchronous writing operation.
* Parameters (in) : Error - A reference to a boost::system::error_code object indicating any errors that occurred during the operation.
*                 : Bytes_Transferred - The number of bytes transferred during the operation.
* Parameters (out): None
* Return value    : None
* Notes           : - This function is called upon completion of an asynchronous write operation.
*                 : - It checks for errors and closes the connection if an error occurred.
*                 : - If no error occurred, it removes the front message from the message queue and initiates another asynchronous write operation if the queue is not empty.
*****************************************************************************************************/
void Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred);
private:
/* Function object for handling incoming messages. */
std::function<void(std::string)> _Message_Handler;
/* Function object for handling errors. */
std::function<void(void)> _Error_Handler;
/* Stream buffer for storing received data. */
boost::asio::streambuf _Buffer{65536};
/* TCP socket object representing the connection. */
boost::asio::ip::tcp::socket _Socket;
/* Queue for storing outgoing messages. */
std::queue<std::string> _Messages{};
/* Username associated with the TCP connection. */
std::string _Username{};
};
}
/********************************************************************
 *  END OF FILE:  ./Connections.hpp
********************************************************************/
#endif