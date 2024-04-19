
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
#include "../Include/Server.hpp"
#include <memory>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Socket
{
/*****************************************
----------    TCP_Connection     ---------
*****************************************/
TCP_Connection::TCP_Connection(boost::asio::ip::tcp::socket &&Socket):
_Socket{std::move(Socket)}
{
     boost::system::error_code Error{};
     std::stringstream Name{};
     Name<<_Socket.remote_endpoint();
     _Username=Name.str();
}
// /****************************************/
// void TCP_Connection::Write(void)
// {
//      boost::asio::streambuf Buffer{};
//      auto Strong_This{shared_from_this()};
//      boost::asio::async_write(_Socket,boost::asio::buffer(_Message),
//      [Strong_This](const boost::system::error_code &Error,size_t Sennded_Bytes)
//      {
//           if(Error){std::cerr<<"Failed To Send Message : "<<Error.message()<<std::endl;}
//           else{std::cout<<"Message Sendded ["<<Sennded_Bytes<<"] : "<<Strong_This->_Message<<std::endl;}
//      }
//      );
//      _Socket.async_receive(Buffer.prepare(255),
//      [this](const boost::system::error_code &Error,size_t Received_Bytes)
//      {
//           if(boost::asio::error::eof==Error){std::cout<<"Client Disconnected\n";}
//           else if(Error){throw boost::system::system_error(Error);}
//           else{}
//      });  
// }
/****************************************/
void TCP_Connection::Run(std::function<void(std::string)> &&Message_Handler,std::function<void(void)> &&Error_Handler)
{
     _Message_Handler=std::move(Message_Handler);
     _Error_Handler=std::move(Error_Handler);
     Async_Reading();
}
/****************************************/
void TCP_Connection::Send_Message(const std::string &Message)
{
     _Messages.push(Message);
     if(!_Messages.empty())
     {
          Async_Writing();
     }
}
/****************************************/
void TCP_Connection::Async_Reading(void)
{
     boost::asio::async_read_until(_Socket,_Buffer,"\n",
     [self=shared_from_this()](boost::system::error_code Error,size_t Bytes_Transferred)
     {
          self->Done_Reading(Error,Bytes_Transferred);
     });
}
/****************************************/
void TCP_Connection::Done_Reading(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     if(Error)
     {
          _Socket.close(Error);
          std::cout<<"- Connection Lost\n";
          _Error_Handler();
     }
     else
     {
          std::stringstream Message{};
          Message<<"- "<<_Username<<" : "<<std::istream(&_Buffer).rdbuf();
          _Message_Handler(Message.str());
          Async_Reading();
     }
}
/****************************************/

void TCP_Connection::Async_Writing(void)
{
     boost::asio::async_write(_Socket,boost::asio::buffer(_Messages.front()),
     [self=shared_from_this()](boost::system::error_code Error,size_t Bytes_Transferred)
     {
          self->Done_Writing(Error,Bytes_Transferred);
     });
}
/****************************************/
void TCP_Connection::Done_Writing(boost::system::error_code &Error,size_t Bytes_Transferred)
{
     if(Error)
     {
          _Socket.close(Error);
          std::cout<<"- Connection Lost\n";
          /* Chek Error again If close failed */
          _Error_Handler();
     }
     else
     {
          std::cout<<"- Done Sending Message\n";
          _Messages.pop();
          if(!_Messages.empty()){Async_Writing();}
     }
}
/****************************************/
boost::asio::ip::tcp::socket& TCP_Connection::Socket(void)
{
     return _Socket;
}


/****************************************/
/****************************************/
/****************************************/
/*****************************************
------------    TCP_Server     -----------
*****************************************/
TCP_Server::TCP_Server(unsigned int Port_Number):
_Port_Number{Port_Number},
_Acceptor{boost::asio::ip::tcp::acceptor(_IO_Context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),_Port_Number))}
{}
/****************************************/
bool TCP_Server::Run(void)
{
     try
     {
          _Start_Accept();
          _IO_Context.run();
     }
     catch (std::exception &Error)
     {
          std::cerr<<"Error : "<<Error.what()<<std::endl;
          return false;
     }
     return true;
}
/****************************************/
void TCP_Server::_Start_Accept(void)
{
     _Socket.emplace(_IO_Context);
     /* Asynchronously Accept Connection */
     _Acceptor.async_accept(*_Socket,[this](const boost::system::error_code &Error)
     {
          /* Create Connection */
          auto Connection{TCP_Connection::Create(std::move(*_Socket))};
          if(Client_Connected){Client_Connected(Connection);}
          _Connections.insert(Connection);
          if(!Error)
          {
               Connection->Run
               (
                    [this](const std::string &Message){if(Client_Received){Client_Received(Message);}},
                    [this,Pointer=std::weak_ptr<TCP_Connection>(Connection)]
                    {
                         if(std::shared_ptr<TCP_Connection> Shared=Pointer.lock();Shared&&_Connections.erase(Shared))
                         {
                              if(Client_Disconnected){Client_Disconnected(Shared);}
                         }
                    }
               );
          }
          _Start_Accept();
     });
}
/****************************************/
void TCP_Server::Broadcast(const std::string &Message)
{
     for(auto &Connection:_Connections)
     {
          Connection->Send_Message(Message);
     }
}

}
/********************************************************************
 *  END OF FILE:  Server.cpp
********************************************************************/
