/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Driver.cpp
 *  Date: March 28, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name: Driver
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "../Include/Driver.hpp"
#include "Driver.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Bootloader
{

/*****************************************
---------    User Interface     ----------
*****************************************/
User_Interface::User_Interface(const std::string& User_Interface_File):Services{User_Interface_File}{}
/*--------------------------------------*/
void User_Interface::Start_Application(void)
{
    User_Interface Bootloader{"/dev/ttyS0"};
    char Chosen_Option{};
    bool Flag{true};
    while(Flag) 
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "Options:" << std::endl;
        std::cout << "1. Get Version." << std::endl;
        std::cout << "2. Get Help." << std::endl;
        std::cout << "3. Get ID." << std::endl;
        std::cout << "4. Jump Address." << std::endl;
        std::cout << "5. Erase Flash." << std::endl;
        std::cout << "6. Write Flash." << std::endl;
        std::cout << "7. Exit." << std::endl;
        std::cout << "Enter Option : ";
        std::cin >> Chosen_Option;
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        switch (Chosen_Option)
        {
            case '1':Bootloader.Get_Version();break;
            case '2':Bootloader.Get_Help();break;
            case '3':Bootloader.Get_ID();break;
            case '4':Bootloader.Jump_Address();break;
            case '5':Bootloader.Erase_Flash();break;
            case '6':Bootloader.Write_Flash();break;
            case '7':Flag=false;break;
        }
    }
}
/*****************************************
------------    Services     -------------
*****************************************/
/*--------------------------------------*/
bool Services::Send_Frame(Bootloader_Command_t Service,std::vector<unsigned char> &Data)
{
    bool Result{};
    Data_Buffer.clear();
    Data_Buffer.push_back(Service);
    std::copy(Data.begin(), Data.end(),std::back_inserter(Data_Buffer));
    Write_Data();
    if(Get_Acknowledge())
    {
        Result=true;
    }
    return Result;
}
/*--------------------------------------*/
bool Services::Read_File(std::vector<unsigned char> &Binary_File)
{
    bool Status{true};
    std::ifstream File(File_Location,std::ios::binary);
    if (File.is_open())
    {
        /* Seek to the end of the file to determine its size */
        File.seekg(0, std::ios::end);
        std::streamsize Size = File.tellg();
        File.seekg(0, std::ios::beg);
        Binary_File.resize(Size);
        /* Read the file content into the buffer */
        if (!File.read(reinterpret_cast<char*>(Binary_File.data()),Size))
        {
            Status=false;
            Binary_File.clear();
        }
        File.close();
    }
    else{Status=false;}
    return Status;
}
/*--------------------------------------*/
bool Services::Send_Frame(Bootloader_Command_t Service)
{
    bool Result{};
    Data_Buffer.clear();
    Data_Buffer.push_back(Service);
    Write_Data();
    if(Get_Acknowledge())
    {
        Update_Buffer();
        Result=true;
    }
    return Result;
}
/*--------------------------------------*/
void Services::Get_Help(void)
{
    if(Send_Frame(Bootloader_Command_Get_Help))
    {
        for(auto &Command:Data_Buffer)
        {
            switch (Command)
            {
                case Bootloader_Command_Get_Help:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get Help."<<std::endl;break;
                case Bootloader_Command_Get_ID:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get ID."<<std::endl;break;
                case Bootloader_Command_Get_Version:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get Version."<<std::endl;break;
                case Bootloader_Command_Erase_Flash:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Erase Current Flash."<<std::endl;break;
                case Bootloader_Command_Write_Flash:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Write On Flash."<<std::endl;break;
                case Bootloader_Command_Address_Jump:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Jumb On Specific Address."<<std::endl;break;
                default:std::cout<<"- (0x"<<static_cast<int>(Command)<<") Unknown New Feature"<<std::endl;break;
            }
        }
    }
    else
    {
        std::cout<<"There Is No ACK From Controller On Get Help Frame"<<std::endl;
    }
}
/*--------------------------------------*/
void Services::Get_Version(void)
{
    if(Send_Frame(Bootloader_Command_Get_Version))
    {
        std::cout<<"Chip ID : "<<static_cast<int>(Data_Buffer[0])<<std::endl;
        std::cout<<"Major : "<<static_cast<int>(Data_Buffer[1])<<std::endl;
        std::cout<<"Minor : "<<static_cast<int>(Data_Buffer[2])<<std::endl;
    }
    else
    {
        std::cout<<"There Is No ACK From Controller On Get Version Frame"<<std::endl;
    }
}
/*--------------------------------------*/
bool Services::Send_Frame(std::vector<unsigned char> &Data)
{
    bool Result{true};
    while(Data.size())
    {
        Data_Buffer.clear();
        std::copy(Data.begin(),Data.size()>=250?Data.begin()+250:Data.end(),std::back_inserter(Data_Buffer));
        Write_Data();
        if(!Get_Acknowledge()){Result=false;break;}
        Data.erase(Data.begin(),Data.size()>=250?Data.begin()+250:Data.end());
        std::this_thread::sleep_for(std::chrono::milliseconds(Sending_Delay_MS)); 
    }
    return Result;
}
/*--------------------------------------*/
void Services::Write_Flash(unsigned int &Start_Page,std::vector<unsigned char> &Payload)
{
    std::vector<unsigned char> Data_Bytes{static_cast<unsigned char>(Start_Page),static_cast<unsigned char>((Payload.size()/250)+1)};
    if(Send_Frame(Bootloader_Command_Write_Flash,Data_Bytes))
    {
        if(Send_Frame(Payload))
        {
            std::cout<<"Done Sending Payload Frame"<<std::endl;

        }
        else{std::cout<<"Error In Sending Frames"<<std::endl;}
    }
    else
    {
        std::cout<<"There Is No ACK After Payload"<<std::endl;
    }
}
void Services::Write_Flash(void)
{
    unsigned int Start_Page{};
    std::string Input{};
    std::vector<unsigned char> Payload{};
    std::cout<<"- Please Enter Start Page : ";
    std::cin>>Start_Page;
    std::cout<<"- Binary File Location ["<<this->File_Location<<"] Want To Edit [N/y] : ";
    std::cin.ignore();
    std::getline(std::cin, Input);
    if(!Input.empty()&&(Input=="y"||Input=="Y"))
    {
        std::cout<<"- Please Enter File Location : ";
        std::cin>>this->File_Location;
    }
    if(Read_File(Payload))
    {
        Write_Flash(Start_Page,Payload);
    }
    else
    {
        std::cout << "Error: Unable to read the binary file." << std::endl;
    }
    std::cout<<"- Want To Jump To Application [Y/n] : ";
    std::getline(std::cin, Input);
    if(Input.empty())
    {
        unsigned int Address{0x8000000+(Start_Page*1024)};
        Jump_Address(Address);
        std::cout<<"------";
    }
}
/*--------------------------------------*/
void Services::Erase_Flash(unsigned int &Start_Page,unsigned int &Pages_Count)
{
    std::vector<unsigned char> Data_Bytes{static_cast<unsigned char>(Start_Page),static_cast<unsigned char>(Pages_Count)};
    if(Send_Frame(Bootloader_Command_Erase_Flash,Data_Bytes))
    {
        std::cout<<"Erasing Done Successfully"<<std::endl;
    }
    else
    {
        std::cout<<"There Is No ACK After Sending Eraseing Pages"<<std::endl;
    }
}
void Services::Erase_Flash(void)
{
    unsigned int Start_Page{};
    unsigned int Pages_Count{};
    std::cout<<"- Please Enter Start Page : ";
    std::cin>>Start_Page;
    std::cout<<"- Please Enter Total Number Of Pages To Erase : ";
    std::cin>>Pages_Count;
    Erase_Flash(Start_Page,Pages_Count);
}
/*--------------------------------------*/
void Services::Jump_Address(unsigned int &Address)
{
    std::vector<unsigned char> Address_Bytes(sizeof(Address));
    std::memcpy(Address_Bytes.data(), &Address, sizeof(Address));
    if(Send_Frame(Bootloader_Command_Address_Jump,Address_Bytes))
    {
        std::cout<<"Jumbing Done Successfully"<<std::endl;
    }
    else
    {
        std::cout<<"There Is No ACK After Sending Jump Address"<<std::endl;
    }
}
void Services::Jump_Address(void)
{
    unsigned int Address{};
    std::cout<<"Please Enter Address In HEX : 0x";
    std::cin>>std::hex>>Address>>std::dec;
    Jump_Address(Address);
}
/*--------------------------------------*/
void Services::Get_ID(void)
{
    if(Send_Frame(Bootloader_Command_Get_ID))
    {
        std::cout<<"Built In ID : 0x"<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[0]<<" 0x";
        std::cout<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[1]<<" 0x";
        std::cout<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[2]<<std::endl;
        std::cout<<std::dec;
    }
    else
    {
        std::cout<<"There Is No ACK From Controller On Get ID Frame"<<std::endl;
    }

}
/*--------------------------------------*/

Services::Services(const std::string& Device_Location):Serial_Port{Device_Location}{}
/*--------------------------------------*/
bool Services::Get_Acknowledge(void)
{
    return Read_Data()==Bootloader_State_ACK?true:false;
}
/*--------------------------------------*/
void Services::Update_Buffer(void)
{
    unsigned char Data_Size{};
    Data_Size=Read_Data();
    Read_Data(Data_Size);
}
/*****************************************
-----------    Serial Port     -----------
*****************************************/
Serial_Port::Serial_Port(const std::string& Device_Location):Port(Input_Output, Device_Location)
{
    Port.set_option(boost::asio::serial_port_base::baud_rate(115200));
    Port.set_option(boost::asio::serial_port_base::character_size(8));
    Port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    Port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    Port.cancel();
}
/*--------------------------------------*/
void Serial_Port::Write_Data(void)
{
    Data_Buffer.insert(Data_Buffer.begin(),Data_Buffer.size()+4);
    Append_CRC(Data_Buffer);
    boost::asio::write(Port,boost::asio::buffer(Data_Buffer));
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Sendded Frame (Format="<<Data_Buffer.size()<<") : ";
        for(auto &Byte:Data_Buffer){std::cout<<std::hex<<"0x"<<static_cast<int>(Byte)<<" ";}
        std::cout<<std::endl<<std::dec;
    #endif
    Data_Buffer.clear();
}
/*--------------------------------------*/
void Serial_Port::Write_Data(const unsigned char Data) 
{
    boost::asio::write(Port, boost::asio::buffer(&Data, 1));
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Sendded Frame (Char) : ";
        std::cout<<std::hex<<"0x"<<static_cast<int>(Data)<<" ";
        std::cout<<std::endl<<std::dec;
    #endif
}
/*--------------------------------------*/
void Serial_Port::Read_Data(size_t Size)
{
    Data_Buffer.resize(Size);
    boost::asio::read(Port, boost::asio::buffer(Data_Buffer));
    std::reverse(Data_Buffer.begin(), Data_Buffer.end());
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Received Frame (Format="<<Data_Buffer.size()<<") : ";
        for(auto &Byte:Data_Buffer){std::cout<<std::hex<<"0x"<<static_cast<int>(Byte)<<" ";}
        std::cout<<std::endl<<std::dec;
    #endif
}
/*--------------------------------------*/
unsigned char Serial_Port::Read_Data(void) 
{
    unsigned char Return;
    boost::asio::read(Port, boost::asio::buffer(&Return,1));
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Received Frame (Char) : ";
        std::cout<<std::hex<<"0x"<<static_cast<int>(Return)<<" ";
        std::cout<<std::endl<<std::dec;
    #endif
    return Return;
}
/*****************************************
------------    CRC_Manage     -----------
*****************************************/
void CRC_Manage::Append_CRC(std::vector<unsigned char>& Data)
{
    size_t Padding_Bits{};
    unsigned int Result{};
    unsigned char* Result_Byte = reinterpret_cast<unsigned char*>(&Result);
    while(Data.size()%4!=0){Data.push_back(0);Padding_Bits++;}
    Result=CRC_Calculate(Data);
    while(Padding_Bits--){Data.pop_back();}
    Data.push_back(Result_Byte[0]);
    Data.push_back(Result_Byte[1]);
    Data.push_back(Result_Byte[2]);
    Data.push_back(Result_Byte[3]);
}
/*--------------------------------------*/
unsigned int CRC_Manage::CRC_Calculate(const std::vector<unsigned char> &Data)
{
    constexpr bool CRC32_REFIN=false;
    constexpr bool CRC32_REFOUT=false;
    constexpr unsigned int CRC32_INIT=0xFFFFFFFF;
    constexpr unsigned int CRC32_XOROUT=0x00000000;
    constexpr unsigned int CRC32_POLYNOMIAL=0x04C11DB7;
    unsigned int CRC{CRC32_INIT};
    unsigned int Result{};
    for (const unsigned char Byte : Data)
	{
        CRC ^= static_cast<unsigned int>(Byte)<<24;
        for (int Counter=0;Counter<8;++Counter) 
        {
            if (CRC&0x80000000){CRC=(CRC<<1)^CRC32_POLYNOMIAL;}
            else{CRC <<= 1;}
        }
    }
    if (!CRC32_REFOUT){Result=CRC^CRC32_XOROUT;}   
    else{Result=CRC;}
    return Result;
}
}
/********************************************************************
 *  END OF FILE:  Driver.cpp 
********************************************************************/