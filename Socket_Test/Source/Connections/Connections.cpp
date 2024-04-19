/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Connections.cpp
 *  Date: November 30, 2023
 *  Description: This file contains the declaration of the TCP_Connection class, which represents a TCP 
 *  Namespace:  Socket
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../../Include/Connectios/Connections.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
/*****************************************
----------    TCP_Connection     ---------
*****************************************/
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
std::shared_ptr<TCP_Connection> TCP_Connection::Create(boost::asio::ip::tcp::socket &&Socket)
{
    /* Create New Object Of TCP_Connection And Returning Its Address */
    return std::shared_ptr<TCP_Connection> (new TCP_Connection(std::move(Socket)));
}
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
std::string TCP_Connection::Print_Username(void)
{
    /* Return the username associated with this TCP connection */
    return _Username;
}
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
boost::asio::ip::tcp::socket& TCP_Connection::Socket(void)
{
    return _Socket;
}
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
void TCP_Connection::Run(std::function<void(std::string)> &&Message_Handler,std::function<void(void)> &&Error_Handler)
{
    /* Set the message handler function */
    _Message_Handler=std::move(Message_Handler);
    /* Set the error handler function */
    _Error_Handler=std::move(Error_Handler);
    /* Start asynchronous reading on the TCP connection */
    Async_Reading();
}
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
void TCP_Connection::Send_Message(const std::string &Message)
{
    /* Add the message to the message queue */
    _Messages.push(Message);
    /* Check if the message queue is not empty */
    if(!_Messages.empty())
    {
        /* Start asynchronous writing if the queue was empty */
        Async_Writing();
    }
}
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
TCP_Connection::TCP_Connection(boost::asio::ip::tcp::socket &&Socket):
/* Initialize _Socket member variable with the provided socket */
_Socket{std::move(Socket)}
{
    /* Error code object for error handling */
    boost::system::error_code Error{};
    /* Stream to store remote endpoint information */
    std::stringstream Name{};
    /* Extract and store remote endpoint information */
    Name<<_Socket.remote_endpoint();
    /* Initialize _Username member variable with remote endpoint information */
    _Username=Name.str();
}
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
void TCP_Connection::Async_Reading(void)
{
    /* Initiates asynchronous reading until a newline character is encountered */
    boost::asio::async_read_until(_Socket,_Buffer,"\n",
    [self=shared_from_this()](boost::system::error_code Error,size_t Bytes_Transferred)
    {
        /* Call Done_Reading upon completion */
        self->Done_Reading(Error,Bytes_Transferred);
    });
}
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
void TCP_Connection::Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred)
{
    /* Check if an error occurred during the read operation */
    if(Error)
    {
        /* Close the connection if an error occurred */
        _Socket.close(Error);
        /* Call the error handler function */
        _Error_Handler();
    }
    /* If no error occurred */
    else
    {
        /* Create a stringstream to store the received message */
        std::stringstream Message{};
        /* Format the received message */
        Message<<"- "<<_Username<<" : "<<std::istream(&_Buffer).rdbuf();
        /* Call the message handler function with the received message */
        _Message_Handler(Message.str());
        /* Initiate another asynchronous read operation */
        Async_Reading();
    }
}
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
void TCP_Connection::Async_Writing(void)
{
    /* Initiates asynchronous writing of the front message from the message queue */
    boost::asio::async_write(_Socket,boost::asio::buffer(_Messages.front()),
    [self=shared_from_this()](boost::system::error_code Error,size_t Bytes_Transferred)
    {
        /* Call Done_Writing upon completion */
        self->Done_Writing(Error,Bytes_Transferred);
    });
}
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
void TCP_Connection::Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred)
{
    /* Check if an error occurred during the write operation */
    if(Error)
    {
        /* Close the connection if an error occurred */
        _Socket.close(Error);
        /* TODO: If close failed */
        /* Call the error handler function */
        _Error_Handler();
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
 *  END OF FILE:  Connections.cpp
********************************************************************/
