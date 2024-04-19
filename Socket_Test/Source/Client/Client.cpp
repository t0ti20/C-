/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Client.cpp
 *  Date: March 20, 2024
 *  Description: This file contains the declaration of the TCP_Client class, which represents a TCP .
 *  Class Name:  TCP_Client
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../../Include/Client/Client.hpp"
#include <string>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
/*****************************************
------------    TCP_Client     -----------
*****************************************/
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
TCP_Client::TCP_Client(const std::string &Address,unsigned int Port):
/* Initialize the TCP socket with the IO context */
_Socket{_IO_Context}
{
     /* Create a resolver object with the IO context */
     boost::asio::ip::tcp::resolver Resolver{_IO_Context};
     /* Resolve the server's address and port */
     _Endpoints=Resolver.resolve(Address,std::to_string(Port));
}
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
void TCP_Client::Run(void)
{
     /* Asynchronously connect to the server */
     boost::asio::async_connect(_Socket,_Endpoints,
     [this](boost::system::error_code Error,boost::asio::ip::tcp::endpoint Endpoint)
     {
          /* Check if there is no error */
          if(!Error)
          {
               /* Start asynchronous reading from the server */
               Async_Reading();
          }
     });
     /* Run the IO context to start processing asynchronous operations */
     _IO_Context.run();
}
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
void TCP_Client::Stop(void)
{
     /* Initialize an error code variable */
     boost::system::error_code Error{};
     /* Attempt to close the socket and check for errors */
     if(_Socket.close(Error)&&Error){/* TODO */}
     /* If an error occurred while closing the socket, handle it here */
}
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
void TCP_Client::Send_Message(const std::string &Message)
{
     /* Add the message to the message queue */
     _Messages.push(Message);
     /* Check if the message queue is not empty */
     if(!_Messages.empty())
     {
          /* Initiate asynchronous writing if the queue was previously empty */
          Async_Writing();
     }
}
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
void TCP_Client::Async_Reading(void)
{
     /* Initiates asynchronous reading until a newline character is encountered */
    boost::asio::async_read_until(_Socket,_Buffer,"\n",
    [this](boost::system::error_code Error,size_t Bytes_Transferred)
    {
        /* Call Done_Reading upon completion */
        Done_Reading(Error,Bytes_Transferred);
    });
}
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
void TCP_Client::Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     if(Error)
     {
          /* Stop the client if an error occurred during reading */
          Stop();
     }
     else
     {
          /* Create a stringstream to store the received message */
          std::stringstream Message{};
          /* Format the received message */
          Message<<"-> "<<std::istream(&_Buffer).rdbuf();
          /* Call the message handler function with the received message */
          Message_Received(Message.str());
          /* Initiate another asynchronous read operation */
          Async_Reading();
     }
}
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
void TCP_Client::Async_Writing(void)
{
    /* Initiates asynchronous writing of the front message from the message queue */
     boost::asio::async_write(_Socket,boost::asio::buffer(_Messages.front()),
     [this](boost::system::error_code Error,size_t Bytes_Transferred)
     {
          /* Call Done_Writing upon completion */
          Done_Writing(Error,Bytes_Transferred);
     });
}
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
void TCP_Client::Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     /* Check if an error occurred during the write operation */
     if(Error)
     {
          /* Close the connection if an error occurred */
          if(_Socket.close(Error)&&Error){}
          /* TODO: If close failed */
     }
     /* If no error occurred */
     else
     {
          /* Remove the front message from the message queue */
          _Messages.pop();
          /* Check if the message queue is not empty */
          if(!_Messages.empty())
          {
               /* Initiate another asynchronous write operation if the queue is not empty */
               Async_Writing();
          }
     }
}
}
/********************************************************************
 *  END OF FILE:  Client.cpp
********************************************************************/
