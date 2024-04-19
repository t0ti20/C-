/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Main.cpp
 *  Date: March 20, 2024
 *  Description: Main File For Testing Socket Server And Client
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../Include/Server/Server.hpp"
#include "../Include/Client/Client.hpp"
#include <chrono>
#include <thread>
/****************************************************************************************************
* Function Name   : Server
* Type            : Global
* Description     : Function representing a TCP server instance.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function creates a TCP server instance and handles client connections,
*                     disconnections, and received messages.
*                 : - It also broadcasts received messages to all connected clients.
*****************************************************************************************************/
void Server()
{
    /* Create a TCP server instance listening on port 8000 */
    Socket::TCP_Server My_Server{8000};
    /* Define the callback functions for client connection and disconnection events */
    My_Server.Client_Connected=[](Socket::Connection_Pointer My_Server)
    {
        std::cout<<"Client_Connected : "<<My_Server->Print_Username()<<std::endl;
    };
    My_Server.Client_Disconnected=[](Socket::Connection_Pointer My_Server)
    {
        std::cout<<"Client_Disconnected : "<<My_Server->Print_Username()<<std::endl;
    };
    /* Define the message handler function for received messages */
    My_Server.Message_Received=[&My_Server](const std::string &Message)
    {
        std::cout<<"+ Message Received "<<Message;
        /* Broadcast the received message to all connected clients */
        My_Server.Broadcast(Message);
        std::cout<<"Done Broadcating ..."<<std::endl;
    };
    /* Start the server */
    My_Server.Run();
}
/****************************************************************************************************
* Function Name   : Client
* Type            : Global
* Description     : Function representing a TCP client instance.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function creates a TCP client instance and interacts with the user to send
*                     and receive messages to/from the server.
*****************************************************************************************************/
void Client()
{
    /* Create a TCP client instance with the server address "pc" and port 8000 */
    Socket::TCP_Client My_Client{"pc",8000};
    /* Define the message handler function for received messages */
    My_Client.Message_Received=[](const std::string &Message)
    {
        std::cout<<"- New Message Received : "<<Message;
    };
    /* Start a thread to run the client asynchronously */
    std::thread Listenning {[&My_Client](){My_Client.Run();}};
    /* Main loop for sending messages */
    while(true)
    {
        std::string Message{};
        std::cout<<"Please Enter Message To Send : \n";
        getline(std::cin,Message);
        /* Check if the user wants to quit */
        if(Message=="\\q"){break;}
        else 
        {
            /* Append a newline character to the message */
            Message+='\n';
            /* Send the message to the server */
            My_Client.Send_Message(Message);
        }
        /* Sleep for 1 second before sending the next message */
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    /* Stop the client and wait for the listening thread to join */
    My_Client.Stop();
    Listenning.join();
}
/*****************************************
---------    Main_Application     --------
*****************************************/
int main() 
{
    /* Start Application */
    Server();
    return 0;
}

