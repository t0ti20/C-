#include "../Include/Server/Server.hpp"
#include "../Include/Client/Client.hpp"
#include <chrono>
#include <thread>
void Server()
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
    My_Server.Message_Received=[&My_Server](const std::string &Message)
    {
        std::cout<<"+ Message Received "<<Message;
        My_Server.Broadcast(Message);
        std::cout<<"Done Broadcating ..."<<std::endl;
    };
    My_Server.Run();
}
void Client()
{
    Socket::TCP_Client My_Client{"pc",8000};
    My_Client.Message_Received=[](const std::string &Message)
    {
        std::cout<<"- New Message Received : "<<Message;
    };
    std::thread Listenning {[&My_Client](){My_Client.Run();}};
    while(true)
    {
        std::string Message{};
        std::cout<<"Please Enter Message To Send : \n";
        getline(std::cin,Message);
        if(Message=="\\q"){break;}
        else 
        {
            Message+='\n';
            My_Client.Send_Message(Message);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    My_Client.Stop();
    Listenning.join();
}
int main() 
{
    Client();
    return 0;
}

