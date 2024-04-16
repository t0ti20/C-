
/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: ./Server.cpp
 *  Date: November 30, 2023
 *  Description: 
 *  Class Name:  
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Server.hpp"
#include <sys/socket.h>
#include <sys/types.h>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/

namespace Socket
{
/*****************************************
----------    Server_Hadler     ----------
*****************************************/
Server_Hadler::Server_Hadler(uint16_t Shared_Socket_Number)
:Socket_Number{Shared_Socket_Number}
{
     Initialization();
}
/*--------------------------------------*/
Server_Hadler::~Server_Hadler()
{
     Close_Client();
     Deinitialization();
}
/*--------------------------------------*/
bool Server_Hadler::Initialization()
{
     sockaddr_in Server_Socket{.sin_family=PF_INET,.sin_port=htons(Socket_Number)};
     /* Make It (IPV4,TCP,Select_Port_Automatically) */
     Server_Description=socket(PF_INET,SOCK_STREAM,0);
     if(Server_Description<0)
     {
          std::cout<<"xx Error Creating Socket xx\n";
          return false;
     }
     /* This function converts an Internet number from presentation format to binary network format and stores the result.*/
     inet_pton(PF_INET,"0.0.0.0",&Server_Socket.sin_addr);
     /*  Bind the socket represented by Description to the network address specified in the Socket structure */
     if(bind(Server_Description, reinterpret_cast<sockaddr*>(&Server_Socket), sizeof(Server_Socket)))
     {
          std::cout<<"xx Error Creating Bind xx\n";
          return false;
     }
     return true;
}
bool Server_Hadler::Listen(void)
{
     if(listen(Server_Description,1)<0)
     {
          std::cout<<"xx Error Listening To Socket xx\n";
          return false;
     }
     return true;
}
bool Server_Hadler::Accept_Client(void)
{
     sockaddr_in Client_Socket{};
     socklen_t Client_Socket_Length{sizeof(Client_Socket)};
     Client_Description=accept(Server_Description, reinterpret_cast<sockaddr*>(&Client_Socket),&Client_Socket_Length);
     if(Client_Description<0)
     {
          std::cout<<"xx Error Accept Desired Client xx\n";
          return false;
     }
     return true;
}
bool Server_Hadler::Write_Message(const std::string &Message)
{
     if(send(Client_Description, Message.data(), Message.size(),0)<0)
     {
          std::cout<<"xx Error Sending Message xx\n";
          return false;
     }
#ifdef DEBUGGING
     else
     {
          std::cout<<"[DEBUG] Data Sendded ["<<Message.size()<<"]: "<<Message<<"\n";
     }
#endif
     return true;
}
bool Server_Hadler::Read_Message(std::string &Message)
{
     char Buffer[BUFFER_SIZE]{};
     Message.clear();
     ssize_t Received_Bytes{recv(Client_Description, Buffer, BUFFER_SIZE,0)};
     if(Received_Bytes<0)
     {
          std::cout<<"xx Error Receiving Message xx\n";
          return false;
     }
#ifdef DEBUGGING
     else
     {
          std::cout<<"[DEBUG] Data Received ["<<Received_Bytes<<"]: "<<Buffer<<"\n";
     }
#endif
     Message.append(Buffer,Received_Bytes);
     return true;
}
bool Server_Hadler::Close_Client(void)
{
     if(Client_Description!=-1)
     {
          if(close(Client_Description)==-1){return true;}
          else
          {
               std::cout<<"xx Error Closing Client xx\n";
               return false;
          }
     }
     return true;
}
bool Server_Hadler::Deinitialization(void)
{
     if(Server_Description!=-1)
     {
          if(close(Server_Description)==-1){return true;}
          else
          {
               std::cout<<"xx Error Closing Client xx\n";
               return false;
          }
     }
     return true;
}
}
/********************************************************************
 *  END OF FILE:  Server.cpp
********************************************************************/
