#include "../Include/Server/Server.hpp"
#include <thread>
int main() 
{
    Socket::TCP_Server My_Server{8000};
    My_Server.Client_Connected=[](Socket::Connection_Pointer My_Server)
    {
        std::cout<<"Client_Connected : "<<My_Server->Print_Username()<<std::endl;
    };
    My_Server.Client_Disconnected=[](Socket::Connection_Pointer My_Server)
    {
        std::cout<<"Client_Disconnected : "<<My_Server->Print_Username()<<std::endl;
    };
    My_Server.Client_Received=[&My_Server](const std::string &Message)
    {
        std::cout<<Message;
        //My_Server.Broadcast(Message);
    };
    My_Server.Run();
}
