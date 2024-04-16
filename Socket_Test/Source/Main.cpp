#include "Server.hpp"
#include <string>
#include <signal.h>
using namespace Socket;
constexpr int SOCKET_NUMBER{8000};
std::string Message{};
Server_Hadler Server{SOCKET_NUMBER};
void handle_sigint(int signum) 
{
    Server.Deinitialization();
}
int main() 
{
    signal(SIGINT, handle_sigint);
    if (Server.Listen()) 
    {
        std::cout << "Waiting for client connection...\n";
        if (Server.Accept_Client()) {
            std::cout << "Client connected!\n";
            std::string Message;
            do
            {
                // Read message from client
                if (!Server.Read_Message(Message)) {
                    std::cerr << "Error reading message from client\n";
                    break;
                }

                // Echo back the message to client
                if (!Server.Write_Message(Message)) {
                    std::cerr << "Error writing message to client\n";
                    break;
                }
            } while (Message != "exit\n");
            // Close client connection
            Server.Close_Client();
        }
    }
    return 0;
}