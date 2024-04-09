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
#include "Bootloader_Host.hpp"
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Bootloader
{
/*****************************************
-----------    GPIO_Manage     -----------
*****************************************/
/****************************************************************************************************
* Constructor Name: GPIO_Manage
* Class           : GPIO_Manage
* Namespace       : Bootloader
* Description     : Initializes GPIO management by exporting a specified pin and setting its direction.
* Parameters (in) : GPIO_Manage_Pin - The GPIO pin number to manage.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor opens the necessary files for exporting GPIO pins and setting pin direction.
*                   - It exports the specified pin, sets its direction as output, and prints error messages if any.
*****************************************************************************************************/
GPIO_Manage::GPIO_Manage(const std::string &GPIO_Manage_Pin):Pin_Number{GPIO_Manage_Pin}
{
    /* Open the file for exporting GPIO pins */
    Pin_Handlar.open("/sys/class/gpio/export");
    /* Check if file is successfully opened */
    if (Pin_Handlar.is_open())
    {
        Pin_Handlar<<Pin_Number;
        Pin_Handlar.flush();
        Pin_Handlar.close();
        /* Open the file for setting pin direction */
        Pin_Handlar.open("/sys/class/gpio/gpio"+Pin_Number+"/direction");
        if (Pin_Handlar.is_open())
        {
            /*  Write "out" to set pin direction as output */
            Pin_Handlar<<"out";
            Pin_Handlar.flush();
            Pin_Handlar.close();
        }
        /* Print error message if failed to open direction file */
        else{std::cout<<"Failed to open direction file."<<std::endl;}
    }
    /* Print error message if failed to open export file */
    else{std::cout<<"Failed to open export file."<<std::endl;}
}

/****************************************************************************************************
* Destructor Name : ~GPIO_Manage
* Class           : GPIO_Manage
* Namespace       : Bootloader
* Description     : Destructs GPIO management by unexporting the GPIO pin.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This destructor opens the necessary file for unexporting GPIO pins.
*                   - It unexports the specified pin and prints an error message if any.
*****************************************************************************************************/
GPIO_Manage::~GPIO_Manage()
{
    /* Unexport GPIO pin when object is destroyed */
    Pin_Handlar.open("/sys/class/gpio/unexport"); 
    /* Check if file is successfully opened */
    if (Pin_Handlar.is_open())
    {
        Pin_Handlar<<Pin_Number; 
        Pin_Handlar.flush(); 
        Pin_Handlar.close(); 
    }
    else
    {
        /* Print error message if failed to open direction file */
        std::cout<<"Failed to open direction file."<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Halt_MCU
* Class           : GPIO_Manage
* Namespace       : Bootloader
* Description     : Halts the microcontroller by triggering an interrupt to run the bootloader application.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function toggles a pin to generate an interrupt, triggering the bootloader application.
*                   - It first sets the pin, then prints a message, and finally clears the pin.
*****************************************************************************************************/
void GPIO_Manage::Halt_MCU(void)
{
    /* Toggle Pin To Generate Interrupt Tp Run Bootloader Application */
    Set_Pin();
    /* Print message */
    std::cout << "Done Triggering." << std::endl;
    Clear_Pin();
}

/****************************************************************************************************
* Function Name   : Set_Pin
* Class           : GPIO_Manage
* Namespace       : Bootloader
* Description     : Sets the GPIO pin to a high state.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function opens the file for setting the pin value to high.
*                   - It sets the pin value to "1" to set it high and prints an error message if any.
*****************************************************************************************************/
void GPIO_Manage::Set_Pin(void)
{
    /* Set pin high */
    Pin_Handlar.open("/sys/class/gpio/gpio"+Pin_Number+"/value"); 
    /* Check if file is successfully opened */
    if (Pin_Handlar.is_open())
    {
        Pin_Handlar<<"1"; 
        Pin_Handlar.flush(); 
        Pin_Handlar.close(); 
    }
    else
    {
        /* Print error message if failed to open direction file */
        std::cout<<"Failed to open direction file."<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Clear_Pin
* Class           : GPIO_Manage
* Namespace       : Bootloader
* Description     : Clears the GPIO pin by setting it to a low state.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function opens the file for setting the pin value to low.
*                   - It sets the pin value to "0" to clear it and prints an error message if any.
*****************************************************************************************************/
void GPIO_Manage::Clear_Pin(void)
{
    Pin_Handlar.open("/sys/class/gpio/gpio" + Pin_Number + "/value"); 
    /* Check if file is successfully opened */
    if (Pin_Handlar.is_open())
    {
        Pin_Handlar << "0"; 
        Pin_Handlar.flush(); 
        Pin_Handlar.close(); 
    }
    else
    {
        /* Print error message if failed to open direction file */
        std::cout<<"Failed to open direction file."<<std::endl;
    }
}

/*****************************************
------------    CRC_Manage     -----------
*****************************************/
/****************************************************************************************************
* Function Name   : Append_CRC
* Class           : CRC_Manage
* Namespace       : Bootloader
* Description     : Appends CRC (Cyclic Redundancy Check) to the given data vector.
* Parameters (in) : Data - Reference to a vector of unsigned characters representing the data.
* Parameters (out): Data - Updated data vector with CRC appended.
* Return value    : None
* Notes           : - This function adds padding bits to the data until its size is a multiple of 4.
*                   - It calculates CRC for the data using CRC_Calculate function.
*                   - After calculation, it removes the padding bits and appends the CRC to the data.
*****************************************************************************************************/
void CRC_Manage::Append_CRC(std::vector<unsigned char>& Data)
{
    size_t Padding_Bits{};
    unsigned int Result{};
    unsigned char* Result_Byte = reinterpret_cast<unsigned char*>(&Result);
    /* Add padding bits until the size of Data is a multiple of 4 */
    while(Data.size() % 4 != 0) 
    {
        Data.push_back(0);
        Padding_Bits++;
    }
    /* Calculate CRC */
    Result = CRC_Calculate(Data);
    /* Remove padding bits */
    while(Padding_Bits--) 
    {
        Data.pop_back();
    }
    /* Append CRC to Data */
    Data.push_back(Result_Byte[0]);
    Data.push_back(Result_Byte[1]);
    Data.push_back(Result_Byte[2]);
    Data.push_back(Result_Byte[3]);
}

/****************************************************************************************************
* Function Name   : CRC_Calculate
* Class           : CRC_Manage
* Namespace       : Bootloader
* Description     : Calculates CRC (Cyclic Redundancy Check) for the given data.
* Parameters (in) : Data - Reference to a vector of unsigned characters representing the data.
* Parameters (out): None
* Return value    : Unsigned integer representing the calculated CRC value.
* Notes           : - This function uses CRC32 algorithm to calculate CRC.
*                   - It initializes CRC with CRC32_INIT value, and then iterates through each byte of the data,
*                     performing bitwise XOR operations and polynomial division.
*                   - Finally, it returns the calculated CRC value.
*****************************************************************************************************/
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

/*****************************************
-----------    Serial Port     -----------
*****************************************/
/****************************************************************************************************
* Constructor Name: Serial_Port
* Class           : Serial_Port
* Namespace       : Bootloader
* Description     : Initializes a serial port with specified device location and GPIO pin for control.
* Parameters (in) : Device_Location   - The location of the serial device.
*                   GPIO_Manage_Pin  - The GPIO pin used for managing the serial port.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes the serial port with specified parameters such as baud rate,
*                     character size, stop bits, and parity.
*                   - It also initializes the GPIO management for controlling the serial port.
*****************************************************************************************************/
Serial_Port::Serial_Port(const std::string& Device_Location,const std::string &GPIO_Manage_Pin)
:Port{Input_Output, Device_Location},GPIO_Manage{GPIO_Manage_Pin}
{
    /* Set baud rate */
    Port.set_option(boost::asio::serial_port_base::baud_rate(115200));
    /* Set character size */
    Port.set_option(boost::asio::serial_port_base::character_size(8));
    /* Set stop bits */
    Port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    /* Set parity */
    Port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    /* Cancel any pending asynchronous operations */
    Port.cancel();
}

/****************************************************************************************************
* Function Name   : Send_Data
* Class           : Serial_Port
* Namespace       : Bootloader
* Description     : Writes data to the serial port after appending data length and CRC.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function inserts the data length at the beginning of the buffer and appends CRC to the data.
*                   - It then writes the data to the serial port using asynchronous write operation.
*                   - If ENABLE_DEBUG is defined, it prints debugging information about the sent frame.
*                   - Finally, it clears the data buffer.
*****************************************************************************************************/
void Serial_Port::Send_Data(void)
{
    /* Insert data length at the beginning of the buffer */
    Data_Buffer.insert(Data_Buffer.begin(), Data_Buffer.size() + 4);
    /* Append CRC to the data */
    Append_CRC(Data_Buffer);
    /* Write data to the serial port */
    boost::asio::write(Port, boost::asio::buffer(Data_Buffer));
    /* Debugging information */
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Sent Frame (Format="<<Data_Buffer.size()<<") : ";
        for(auto &Byte : Data_Buffer) { std::cout<<std::hex<<"0x"<<static_cast<int>(Byte)<<" "; }
        std::cout<<std::endl<<std::dec;
    #endif
    /* Clear the data buffer */
    Data_Buffer.clear();
}

/****************************************************************************************************
* Function Name   : Send_Data
* Class           : Serial_Port
* Namespace       : Bootloader
* Description     : Writes a single byte of data to the serial port.
* Parameters (in) : Data - The single byte of data to be written.
* Parameters (out): None
* Return value    : None
* Notes           : - This function writes a single byte of data to the serial port using asynchronous write operation.
*                   - If ENABLE_DEBUG is defined, it prints debugging information about the sent frame.
*****************************************************************************************************/
void Serial_Port::Send_Data(const unsigned char Data) 
{
    /* Write single byte data to the serial port */
    boost::asio::write(Port, boost::asio::buffer(&Data, 1));
    /* Debugging information */
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Sent Frame (Char) : ";
        std::cout<<std::hex<<"0x"<<static_cast<int>(Data)<<" ";
        std::cout<<std::endl<<std::dec;
    #endif
}

/****************************************************************************************************
* Function Name   : Receive_Data
* Class           : Serial_Port
* Namespace       : Bootloader
* Description     : Reads data from the serial port into the data buffer.
* Parameters (in) : Size - The size of data to be read from the serial port.
* Parameters (out): None
* Return value    : None
* Notes           : - This function resizes the data buffer to the specified size, reads data from the serial port,
*                     and then reverses the order of bytes in the buffer.
*                   - If ENABLE_DEBUG is defined, it prints debugging information about the received frame.
*****************************************************************************************************/
void Serial_Port::Receive_Data(size_t Size)
{
    /* Resize data buffer */
    Data_Buffer.resize(Size);
    /* Read data from the serial port */
    boost::asio::read(Port, boost::asio::buffer(Data_Buffer));
    /* Reverse the order of bytes */
    std::reverse(Data_Buffer.begin(), Data_Buffer.end());
    /* Debugging information */
    #ifdef ENABLE_DEBUG
        std::cout<<"[DEBUG] Received Frame (Format="<<Data_Buffer.size()<<") : ";
        for(auto &Byte : Data_Buffer) { std::cout<<std::hex<<"0x"<<static_cast<int>(Byte)<<" "; }
        std::cout<<std::endl<<std::dec;
    #endif
}

/****************************************************************************************************
* Function Name   : Receive_Data
* Class           : Serial_Port
* Namespace       : Bootloader
* Description     : Reads a single byte of data from the serial port.
* Parameters (in) : None
* Parameters (out): None
* Return value    : Unsigned char representing the read byte of data.
* Notes           : - This function reads a single byte of data from the serial port using asynchronous read operation.
*                   - If ENABLE_DEBUG is defined, it prints debugging information about the received frame.
*****************************************************************************************************/
unsigned char Serial_Port::Receive_Data(void) 
{
    unsigned char Return{Bootloader_State_NACK};
    boost::asio::steady_timer Timer(Input_Output, boost::asio::chrono::seconds(1));
    /* Perform asynchronous read with handlar */
    boost::asio::async_read(Port, boost::asio::buffer(&Return, 1),
    [&](const boost::system::error_code& Error_Code, std::size_t Bytes_Transferred)
    {
        /* Cancel the timer if data is received */
        if (!Error_Code){Timer.cancel();}
    }
    );
    /* Set up timeout handler */
    Timer.async_wait([&](const boost::system::error_code& Error_Code) 
    {
        /* Cancel the asynchronous operation if timeout occurs */
        if (!Error_Code)
        {
            std::cout<<"Timeout occurred: No data received within the specified time."<< std::endl;Port.cancel();
        }
    });
    /* Reset the IO service */
    Input_Output.reset();
    /* Run the IO service */
    Input_Output.run();
    /* Debugging information */
    #ifdef ENABLE_DEBUG
        std::cout << "[DEBUG] Received Frame (Char) : ";
        std::cout << std::hex << "0x" << static_cast<int>(Return) << " ";
        std::cout << std::endl << std::dec;
    #endif
    return Return;
}

/*****************************************
------------    Services     -------------
*****************************************/
/****************************************************************************************************
* Function Name   : Send_Frame
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a frame with a specified service command and additional data to the controller.
* Parameters (in) : Service - The service command to be sent.
*                   Data    - Additional data to be sent along with the service command.
* Parameters (out): None
* Return value    : bool - True if the frame is sent successfully and acknowledged, false otherwise.
* Notes           : - This function prepares a frame with the specified service command and additional data
*                     and sends it to the controller.
*                   - It checks for acknowledgment after sending the frame. If acknowledgment is received,
*                     it returns true.
*                   - If no acknowledgment is received or an error occurs during transmission, it returns false.
*****************************************************************************************************/
bool Services::Send_Frame(Bootloader_Command_t Service, std::vector<unsigned char> &Data)
{
    /* Initialize Result as false */
    bool Result{}; 
    /* Clear Data_Buffer */
    Data_Buffer.clear(); 
    /* Push Service into Data_Buffer */
    Data_Buffer.push_back(Service); 
    /* Copy Data into Data_Buffer */
    std::copy(Data.begin(), Data.end(), std::back_inserter(Data_Buffer)); 
    /* Call Send_Data function */
    Send_Data(); 
    /* Check if acknowledgement is received */
    if (Get_Acknowledge()) 
    {
        /* Set Result to true */
        Result = true; 
    }
    /* Return Result */
    return Result; 
}

/****************************************************************************************************
* Function Name   : Read_File
* Class           : Services
* Namespace       : Bootloader
* Description     : Reads binary file content into a vector.
* Parameters (in) : None
* Parameters (out): Binary_File - Reference to a vector where the file content will be stored.
* Return value    : bool - True if the file is successfully read, false otherwise.
* Notes           : - This function reads the content of a binary file located at File_Location.
*                   - It determines the size of the file, allocates memory in Binary_File accordingly,
*                     and reads the file content into the buffer.
*                   - If successful, it returns true and Binary_File contains the file content.
*                   - If unsuccessful (e.g., file not found or unable to read), it returns false
*                     and Binary_File is cleared.
*****************************************************************************************************/
bool Services::Read_File(std::vector<unsigned char> &Binary_File)
{
    /* Initialize Status as true */
    bool Status{true};
    /* Open the file */
    std::ifstream File(File_Location,std::ios::binary);
    /* Check if file is successfully opened */
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
            /* If failed to read, set Status to false and clear Binary_File */
            Status=false;
            Binary_File.clear();
        }
        /* Close the file */
        File.close();
    }
    else
    {
        /* If failed to open file, set Status to false */
        Status=false;
    }
    /* Return Status */
    return Status;
}

/****************************************************************************************************
* Function Name   : Send_Frame
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a frame with a specified service command to the controller.
* Parameters (in) : Service - The service command to be sent.
* Parameters (out): None
* Return value    : bool - True if the frame is sent successfully and acknowledged, false otherwise.
* Notes           : - This function prepares a frame with the specified service command and sends it to the controller.
*                   - It checks for acknowledgment after sending the frame. If acknowledgment is received,
*                     it updates the data buffer.
*                   - It returns true if the frame is sent successfully and acknowledged, otherwise returns false.
*****************************************************************************************************/
bool Services::Send_Frame(Bootloader_Command_t Service)
{
    /* Initialize Result as false */
    bool Result{};
    /* Clear Data_Buffer */
    Data_Buffer.clear();
    /* Push Service into Data_Buffer */
    Data_Buffer.push_back(Service);
    /* Call Send_Data function */
    Send_Data();
    /* Check if acknowledgement is received */
    if (Get_Acknowledge())
    {
        /* Update Data_Buffer */
        Update_Buffer();
        /* Set Result to true */
        Result=true;
    }
    /* Return Result */
    return Result;
}

/****************************************************************************************************
* Function Name   : Get_Help
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a get help command to the controller and prints available commands.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function sends a get help command to the controller.
*                   - It retrieves the list of available commands from the received data buffer and prints them.
*                   - It prints an error message if no acknowledgment is received after sending the get help command.
*****************************************************************************************************/
void Services::Get_Help(void)
{
    /* Check if Get_Help frame is sent successfully */
    if(Send_Frame(Bootloader_Command_Get_Help))
    {
        /* Iterate through Data_Buffer */
        for(auto &Command:Data_Buffer)
        {
            /* Print command details based on the received command */
            switch (Command)
            {
                case Bootloader_Command_Get_Help:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get Help."<<std::endl;
                    break;
                case Bootloader_Command_Get_ID:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get ID."<<std::endl;
                    break;
                case Bootloader_Command_Get_Version:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Get Version."<<std::endl;
                    break;
                case Bootloader_Command_Erase_Flash:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Erase Current Flash."<<std::endl;
                    break;
                case Bootloader_Command_Flash_Application:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Write On Flash."<<std::endl;
                    break;
                case Bootloader_Command_Address_Jump:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Jumb On Specific Address."<<std::endl;
                    break;               
                case Bootloader_Command_Say_Hi:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Say Hello To Chip."<<std::endl;
                    break;
                default:
                    std::cout<<"- (0x"<<static_cast<int>(Command)<<") Unknown New Feature"<<std::endl;
                    break;
            }
        }
    }
    else
    {
        /* Print error message if no acknowledgment received */
        std::cout<<"There Is No ACK From Controller On Get Help Frame"<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Get_Version
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a get version command to the controller and retrieves chip ID, major, and minor version.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function sends a get version command to the controller.
*                   - It retrieves chip ID, major, and minor version from the received data buffer and prints them.
*                   - It prints an error message if no acknowledgment is received after sending the get version command.
*****************************************************************************************************/
void Services::Get_Version(void)
{
    /* Check if Get_Version frame is sent successfully */
    if(Send_Frame(Bootloader_Command_Get_Version))
    {
        /* Print Chip ID, Major, and Minor version */
        std::cout<<"Chip ID : "<<static_cast<int>(Data_Buffer[0])<<std::endl;
        std::cout<<"Major : "<<static_cast<int>(Data_Buffer[1])<<std::endl;
        std::cout<<"Minor : "<<static_cast<int>(Data_Buffer[2])<<std::endl;
    }
    else
    {
        /* Print error message if no acknowledgment received */
        std::cout<<"There Is No ACK From Controller On Get Version Frame"<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Send_Frame
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends data frames to the controller.
* Parameters (in) : Data - The data to be sent in the frames.
* Parameters (out): None
* Return value    : bool - True if all frames are sent successfully and acknowledged, false otherwise.
* Notes           : - This function sends data frames to the controller. It breaks down the data into
*                     frames of maximum 250 bytes and sends them one by one.
*                   - It checks for acknowledgment after sending each frame. If acknowledgment is not
*                     received, it stops sending further frames and returns false.
*                   - It delays between sending each frame to ensure reliable communication.
*****************************************************************************************************/
bool Services::Send_Frame(std::vector<unsigned char> &Data)
{
    /* Initialize Result as true */
    bool Result{true};
    /* Loop until Data is empty */
    while(Data.size())
    {
        Data_Buffer.clear();
        /* Copy data into Data_Buffer, maximum 250 bytes */
        std::copy(Data.begin(), Data.size() >= 250 ? Data.begin() + 250 : Data.end(), std::back_inserter(Data_Buffer));
        /* Call Send_Data function */
        Send_Data();
        /* Check if acknowledgment is not received */
        if(!Get_Acknowledge())
        {
            /* Set Result to false and break the loop */
            Result = false;
            break;
        }
        /* Erase sent data from Data */
        Data.erase(Data.begin(), Data.size() >= 250 ? Data.begin() + 250 : Data.end());
        /* Delay sending next frame */
        std::this_thread::sleep_for(std::chrono::milliseconds(Sending_Delay_MS)); 
    }
    /* Return Result */
    return Result;
}

/****************************************************************************************************
* Function Name   : Flash_Application
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a flash application command to the controller with the specified start page
*                   and binary payload.
* Parameters (in) : Start_Page   - The start page for flashing.
*                   Payload      - The binary payload to be flashed.
* Parameters (out): None
* Return value    : None
* Notes           : - This function prepares the data bytes containing the start page and payload size,
*                     and sends a flash application command to the controller.
*                   - It then sends the payload frames to the controller.
*                   - It prints a message if the payload frame is sent successfully,
*                     otherwise, it prints an error message if an error occurs while sending frames
*                     or if no acknowledgment is received after sending the payload.
*****************************************************************************************************/
void Services::Flash_Application(unsigned int &Start_Page, std::vector<unsigned char> &Payload)
{
    /* Prepare data bytes */
    std::vector<unsigned char> Data_Bytes{static_cast<unsigned char>(Start_Page), static_cast<unsigned char>((Payload.size() / 250) + 1)};
    /* Send flash application command */
    if(Send_Frame(Bootloader_Command_Flash_Application, Data_Bytes))
    {
        /* Send payload */
        if(Send_Frame(Payload))
        {
            /* Print message if payload frame sent successfully */
            std::cout<<"Done Sending Payload Frame"<<std::endl;
        }
        else
        {
            /* Print error message if error occurred while sending frames */
            std::cout<<"Error In Sending Frames"<<std::endl;
        }
    }
    else
    {
        /* Print error message if no acknowledgment received after payload */
        std::cout<<"There Is No ACK After Payload"<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Flash_Application
* Class           : Services
* Namespace       : Bootloader
* Description     : Prompts the user to enter the start page and binary file location, and then
*                   flashes the application to the controller.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function prompts the user to enter the start page and binary file location.
*                   - It then reads the binary file and flashes the application to the controller
*                     with the specified start page and binary payload.
*****************************************************************************************************/
void Services::Flash_Application(void)
{
    unsigned int Start_Page{};
    std::string Input{};
    std::vector<unsigned char> Payload{};
    /* Prompt user to enter start page */
    std::cout<<"- Please Enter Start Page : ";
    std::cin>>Start_Page;
    /* Prompt user to edit file location */
    std::cout<<"- Binary File Location ["<<this->File_Location<<"] Want To Edit [N/y] : ";
    std::cin.ignore();
    std::getline(std::cin, Input);
    /* If user wants to edit file location */
    if (!Input.empty() && (Input == "y" || Input == "Y"))
    {
        std::cout<<"- Please Enter File Location : ";
        std::cin>>this->File_Location;
    }
    /* Read binary file */
    if (Read_File(Payload))
    {
        /* Flash application */
        Flash_Application(Start_Page, Payload);
        Halt_MCU();
    }
    else
    {
        /* Print error message if unable to read the binary file */
        std::cout << "Error: Unable to read the binary file." << std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Erase_Flash
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends an erase flash command to the controller with the specified start page and
*                   number of pages to erase.
* Parameters (in) : Start_Page   - The start page for erasing.
*                   Pages_Count  - The number of pages to erase.
* Parameters (out): None
* Return value    : None
* Notes           : - This function prepares the data bytes containing the start page and number of pages
*                     to erase and sends an erase flash command to the controller.
*                   - It prints a message if erasing is done successfully, otherwise, it prints an error message
*                     if no acknowledgment is received after sending the erase pages command.
*****************************************************************************************************/
void Services::Erase_Flash(unsigned int &Start_Page, unsigned int &Pages_Count)
{
    /* Prepare data bytes */
    std::vector<unsigned char> Data_Bytes{static_cast<unsigned char>(Start_Page), static_cast<unsigned char>(Pages_Count)};
    /* Send erase flash command */
    if(Send_Frame(Bootloader_Command_Erase_Flash, Data_Bytes))
    {
        /* Print message if erasing is done successfully */
        std::cout<<"Erasing Done Successfully"<<std::endl;
    }
    else
    {
        /* Print error message if no acknowledgment received after sending erase pages */
        std::cout<<"There Is No ACK After Sending Eraseing Pages"<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Erase_Flash
* Class           : Services
* Namespace       : Bootloader
* Description     : Prompts the user to enter the start page and the total number of pages to erase,
*                   and then initiates flash erasing.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function prompts the user to enter the start page and the total number of pages
*                     to erase for flashing.
*                   - It then initiates the flash erasing process with the specified start page and number of pages.
*****************************************************************************************************/
void Services::Erase_Flash(void)
{
    unsigned int Start_Page{};
    unsigned int Pages_Count{};
    /* Prompt user to enter start page */
    std::cout<<"- Please Enter Start Page : ";
    std::cin>>Start_Page;
    /* Prompt user to enter total number of pages to erase */
    std::cout<<"- Please Enter Total Number Of Pages To Erase : ";
    std::cin>>Pages_Count;
    /* Erase flash */
    Erase_Flash(Start_Page, Pages_Count);
}

/****************************************************************************************************
* Function Name   : Jump_Address
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a jump address command to the controller with the specified address.
* Parameters (in) : Address - The address to jump to.
* Parameters (out): None
* Return value    : None
* Notes           : - This function prepares the address bytes and sends a jump address command to the controller
*                     with the specified address.
*                   - It prints a message if jumping is done successfully, otherwise, it prints an error message
*                     if no acknowledgment is received after sending the jump address.
*****************************************************************************************************/
void Services::Jump_Address(unsigned int &Address)
{
    /* Prepare address bytes */
    std::vector<unsigned char> Address_Bytes(sizeof(Address));
    std::memcpy(Address_Bytes.data(), &Address, sizeof(Address));
    /* Send jump address command */
    if(Send_Frame(Bootloader_Command_Address_Jump, Address_Bytes))
    {
        /* Print message if jumping is done successfully */
        std::cout<<"Jumbing Done Successfully"<<std::endl;
    }
    else
    {
        /* Print error message if no acknowledgment received after sending jump address */
        std::cout<<"There Is No ACK After Sending Jump Address"<<std::endl;
    }
}

/****************************************************************************************************
* Function Name   : Jump_Address
* Class           : Services
* Namespace       : Bootloader
* Description     : Prompts the user to enter an address in hexadecimal and jumps to that address.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function prompts the user to enter an address in hexadecimal format.
*                   - It then jumps to the entered address.
*****************************************************************************************************/
void Services::Jump_Address(void)
{
    unsigned int Address{};
    /* Prompt user to enter address in hexadecimal */
    std::cout<<"Please Enter Address In HEX : 0x";
    std::cin>>std::hex>>Address>>std::dec;
    /* Jump to address */
    Jump_Address(Address);
}

/****************************************************************************************************
* Function Name   : Get_ID
* Class           : Services
* Namespace       : Bootloader
* Description     : Sends a Get ID frame to the controller and retrieves the built-in ID.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function sends a Get ID frame to the controller using Send_Frame function.
*                   - It then retrieves the built-in ID from the received data buffer and prints it.
*                   - If no acknowledgment is received, it prints an error message.
*****************************************************************************************************/
void Services::Get_ID(void)
{
    /* Check if Get_ID frame is sent successfully */
    if(Send_Frame(Bootloader_Command_Get_ID))
    {
        /* Print built-in ID */
        std::cout<<"Built In ID : 0x"<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[0]<<" 0x";
        std::cout<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[1]<<" 0x";
        std::cout<<std::hex<<(reinterpret_cast<unsigned int*>(Data_Buffer.data()))[2]<<std::endl;
        std::cout<<std::dec;
    }
    else
    {
        /* Print error message if no acknowledgment received */
        std::cout<<"There Is No ACK From Controller On Get ID Frame"<<std::endl;
    }
}

/****************************************************************************************************
* Constructor Name: Services
* Class           : Services
* Namespace       : Bootloader
* Description     : Initializes services with a serial port and GPIO pin for control.
* Parameters (in) : Device_Location   - The location of the serial device.
*                   GPIO_Manage_Pin  - The GPIO pin used for managing the serial port.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes services with a serial port and GPIO pin for control.
*                   - It initializes the Serial_Port base class with the provided device location and GPIO pin.
*****************************************************************************************************/
Services::Services(const std::string &Device_Location,const std::string &GPIO_Manage_Pin)
:Serial_Port{Device_Location,GPIO_Manage_Pin}{}

/****************************************************************************************************
* Function Name   : Get_Acknowledge
* Class           : Services
* Namespace       : Bootloader
* Description     : Reads a byte of data from the serial port and checks if it matches the ACK value.
* Parameters (in) : None
* Parameters (out): None
* Return value    : Boolean indicating whether ACK is received.
* Notes           : - This function reads a byte of data from the serial port and checks if it matches
*                     the ACK value defined in Bootloader_State_ACK.
*****************************************************************************************************/
bool Services::Get_Acknowledge(void)
{
    /* Check if received data is ACK */
    return Receive_Data() == Bootloader_State_ACK ? true : false;
}

/****************************************************************************************************
* Function Name   : Update_Buffer
* Class           : Services
* Namespace       : Bootloader
* Description     : Updates the buffer by reading data size and then reading data based on the size.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - This function reads a byte of data to determine the size of the incoming data.
*                   - It then reads data from the serial port based on the determined size and updates the buffer.
*****************************************************************************************************/
void Services::Update_Buffer(void)
{
    unsigned char Data_Size{};
    /* Read data size */
    Data_Size = Receive_Data();
    /* Read data based on size */
    Receive_Data(Data_Size);
}



void Services::Exit_Bootloader(void)
{
    unsigned int Address{Booting_Flag};
    unsigned int Data{};
    Write_Data(Address,Data);
}
void Services::Write_Data(void)
{
    unsigned int Address{};
    unsigned int Data{};
    /* Prompt user to enter start page */
    std::cout<<"- Please Enter Desired Address In HEX : 0x";
    std::cin>>std::hex>>Address>>std::dec;
    /* Prompt user to enter total number of pages to erase */
    std::cout<<"- Please Enter Data To Write In HEX : 0x";
    std::cin>>std::hex>>Data>>std::dec;
    /* Erase flash */
    Write_Data(Address, Data);
}
void Services::Write_Data(unsigned int &Address,unsigned int &Data)
{
    std::vector<unsigned char> Sending_Bytes(sizeof(Address) + sizeof(Data));
    std::memcpy(Sending_Bytes.data(), &Address, sizeof(Address));
    std::memcpy(Sending_Bytes.data() + sizeof(Address), &Data, sizeof(Data));

    /* Send erase flash command */
    if(Send_Frame(Bootloader_Command_Send_Data, Sending_Bytes))
    {
        /* Print message if erasing is done successfully */
        std::cout<<"Writing Done Successfully"<<std::endl;
    }
    else
    {
        /* Print error message if no acknowledgment received after sending erase pages */
        std::cout<<"There Is No ACK After Sending Writing Data"<<std::endl;
    }
}
bool Services::Say_Hi(void)
{
    return Send_Frame(Bootloader_Command_Say_Hi);
}
/*****************************************
---------    User Interface     ----------
*****************************************/
/****************************************************************************************************
* Function Name   : User_Interface
* Class           : User_Interface
* Namespace       : Bootloader
* Description     : Constructor for the User_Interface class.
* Parameters (in) : User_Interface_File - The file location for user interface initialization.
*                   GPIO_Manage_Pin    - The GPIO pin for managing user interface operations.
* Parameters (out): None
* Return value    : None
* Notes           : - This constructor initializes the user interface using the provided file location
*                     and GPIO pin for managing user interface operations.
*                   - It initializes the User_Interface class by inheriting from the Services class,
*                     which handles communication with the controller.
*****************************************************************************************************/
User_Interface::User_Interface(const std::string &User_Interface_File,const std::string &GPIO_Manage_Pin)
    :Services{User_Interface_File,GPIO_Manage_Pin}{}

/****************************************************************************************************
* Function Name   : Start_Application
* Class           : User_Interface
* Namespace       : Bootloader
* Description     : Initiates the user interface for the application, providing various options
*                   for user interaction.
* Parameters (in) : None
* Parameters (out): None
* Return value    : None
* Notes           : - The function utilizes a while loop to continuously display options to the user
*                     until the user chooses to exit.
*                   - User input is taken to select different options, and corresponding actions
*                     are executed based on the chosen option.
*****************************************************************************************************/
void User_Interface::Print_Target_Info(bool State)
{
    if(State)
    {
        std::cout << "\033[1;32m";
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "++++++++++++ Target Detected +++++++++++\n";
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        Get_Version();
        Get_ID();
        std::cout << "\033[0m";
    }
    else
    {
        std::cout << "\033[1;31m";
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "+++++++++ Failed To Find Target ++++++++\n";
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "\033[0m";
    }
}
User_Interface::~User_Interface()
{
    if(Say_Hi())
    {
        Exit_Bootloader();
    }
}
void User_Interface::Start_Application(void)
{
    bool Flag{true};
    char Chosen_Option{};
    /* Initialize Default Location For Serial And GPIO */
    Halt_MCU();
    std::this_thread::sleep_for(std::chrono::milliseconds(Sending_Delay_MS)); 
    Print_Target_Info(Say_Hi());
    while(Flag)
    {        
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "Options:" << std::endl;
        std::cout << "1. Get ID." << std::endl;
        std::cout << "2. Get Help." << std::endl;
        std::cout << "3. Write Data." << std::endl;
        std::cout << "4. Get Version." << std::endl;
        std::cout << "5. Erase Flash." << std::endl;
        std::cout << "6. Jump Address." << std::endl;
        std::cout << "7. Flash Application." << std::endl;
        std::cout << "9. Exit." << std::endl;
        std::cout << "Enter Option : ";
        /* Scan The Input By User */
        std::cin >> Chosen_Option;
        std::cout << "++++++++++++++++++++++++++++++++++++++++\n";
        /* Jump For The Option */
        switch (Chosen_Option)
        {
            case '4':Get_Version();break;
            case '2':Get_Help();break;
            case '3':Write_Data();break;
            case '1':Get_ID();break;
            case '6':Jump_Address();break;
            case '5':Erase_Flash();break;
            case '7':Flash_Application();break;
            case '9':Flag=false;break;
        }
    }
}
}
/********************************************************************
 *  END OF FILE:  Driver.cpp 
********************************************************************/