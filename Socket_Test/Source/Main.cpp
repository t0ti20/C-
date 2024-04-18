#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <iostream>
#include <chrono> 
#include <array> 
#include <thread>
void Server(void);
int main() 
{
    Server();
}
void Server(void)
{
    std::string Message{"Hello World !\n"};
    boost::system::error_code Error{};
    try
    {
        boost::asio::io_context IO{};
        boost::asio::ip::tcp::acceptor Acceptor(IO,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),8000));
        std::cout<<"Accepting Connections on ["<<PORT_NUMBER<<"] ..."<<std::endl;
        boost::asio::ip::tcp::socket Socket(IO);
        Acceptor.accept(Socket);
        std::cout<<"Client Connected ..."<<std::endl;
        while (true)
        {
            std::cout<<"Sending Message ..."<<std::endl;
            boost::asio::write(Socket,boost::asio::buffer(Message),Error);
            std::cout<<"Message Sendded"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    catch(std::exception &Exception)
    {
        std::cerr<<Exception.what()<<std::endl;
    }
}
void Client(void)
{
    std::array<char,255> Buffer{};
    boost::system::error_code Error{};
    size_t Bytes_Received{};
    try
    {
        boost::asio::io_context IO{};
        boost::asio::ip::tcp::resolver Resolver{IO};
        auto Endpoint{Resolver.resolve("pc","8000")};

        boost::asio::ip::tcp::socket Socket(IO);
        boost::asio::connect(Socket,Endpoint);

        std::cout<<"Client Connected ..."<<std::endl;
        while (true)
        {
            std::cout<<"Receiving Message Message ..."<<std::endl;
            Bytes_Received=Socket.read_some(boost::asio::buffer(Buffer),Error);
            if(Error==boost::asio::error::eof){std::cout<<"Server Disconnected"<<std::endl;break;}
            else if (Error){throw boost::system::system_error(Error);}
            std::cout<<"Message Received ["<<Bytes_Received<<"] : ";
            std::cout.write(Buffer.data(),Bytes_Received);
        }
    }
    catch(std::exception &Exception)
    {
        std::cerr<<"Error : "<<Exception.what()<<std::endl;
    }
}