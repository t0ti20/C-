/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Client.cpp
 *  Date: March 20, 2024
 *  Description: This file contains the declaration of the TCP_Server class, which represents a TCP .
 *  Class Name:  TCP_Server
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
TCP_Client::TCP_Client(const std::string &Address,unsigned int Port):
_Socket{_IO_Context}
{
     boost::asio::ip::tcp::resolver Resolver{_IO_Context};
     _Endpoints=Resolver.resolve(Address,std::to_string(Port));
}
void TCP_Client::Run(void)
{
     boost::asio::async_connect(_Socket,_Endpoints,
     [this](boost::system::error_code Error,boost::asio::ip::tcp::endpoint Endpoint)
     {
          if(!Error)
          {
               Async_Reading();
          }
     });
     _IO_Context.run();
}
void TCP_Client::Stop(void)
{
     boost::system::error_code Error{};
     _Socket.close(Error);
     if(Error){}
}
void TCP_Client::Send_Message(const std::string &Message)
{
     _Messages.push(Message);
     if(!_Messages.empty())
     {
          Async_Writing();
     }
}
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
void TCP_Client::Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     if(Error)
     {
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
void TCP_Client::Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     /* Check if an error occurred during the write operation */
     if(Error)
     {
          /* Close the connection if an error occurred */
          _Socket.close(Error);
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
