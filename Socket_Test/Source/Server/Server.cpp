/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Server.cpp
 *  Date: March 20, 2024
 *  Description: This file contains the declaration of the TCP_Server class, which represents a TCP .
 *  Class Name:  TCP_Server
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../../Include/Server/Server.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
/*****************************************
------------    TCP_Server     -----------
*****************************************/
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
TCP_Server::TCP_Server(unsigned int Port_Number):
/* Initialize the port number member variable */
_Port_Number{Port_Number},
/* Initialize the acceptor object */
_Acceptor{boost::asio::ip::tcp::acceptor(_IO_Context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),_Port_Number))}
{}
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
bool TCP_Server::Run(void)
{
     try
     {
          /* Start accepting incoming connections */
          _Start_Accept();
          /* Run the IO context for asynchronous operations */
          _IO_Context.run();
     }
     catch (std::exception &Error)
     {
          /* Print error message if an exception occurs */
          std::cerr<<"Error : "<<Error.what()<<std::endl;
          /*  Return false to indicate failure */
          return false;
     }
     /* Return true to indicate success */
     return true;
}
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
void TCP_Server::Broadcast(const std::string &Message)
{
     for(auto &Connection:_Connections)
     {
          Connection->Send_Message(Message);
     }
}
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
void TCP_Server::_Start_Accept(void)
{
     /* Create a socket for accepting connections */
     _Socket.emplace(_IO_Context);
     /* Asynchronously Accept Connection */
     _Acceptor.async_accept(*_Socket,[this](const boost::system::error_code &Error)
     {
          /* Create a TCP_Connection object */
          auto Connection{TCP_Connection::Create(std::move(*_Socket))};
          /* Call client connected callback if set */
          if(Client_Connected){Client_Connected(Connection);}
          /* Add the connection to the list of connections */
          _Connections.insert(Connection);
          if(!Error)
          {
               /* Set up message and error handlers for the connection and initiate its Run function */
               Connection->Run
               (
                    [this](const std::string &Message){if(Message_Received){Message_Received(Message);}},
                    [this,Pointer=std::weak_ptr<TCP_Connection>(Connection)]
                    {
                         if(std::shared_ptr<TCP_Connection> Shared=Pointer.lock();Shared&&_Connections.erase(Shared))
                         {
                              if(Client_Disconnected){Client_Disconnected(Shared);}
                         }
                    }
               );
          }
          /* Start accepting another connection */
          _Start_Accept();
     });
}
}
/********************************************************************
 *  END OF FILE:  Server.cpp
********************************************************************/
