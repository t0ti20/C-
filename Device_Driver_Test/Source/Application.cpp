#include "Driver.hpp"
#include <thread>
#include <chrono>
class Button
{   
private:
    static char Current_State;
public:
    static void Notify_On_Change(char Input);
};
char Button::Current_State{'1'};
void Button::Notify_On_Change(char Input)
{
    if(Input!=Current_State)
    {
        std::cout<<((Input=='0')?std::string{"Button Is Pressed"}:std::string{"Button Is Released"})<<std::endl;
        Current_State=Input;
    }
}
using namespace Driver_Development;
using namespace std;
int main()
{
    Driver LED_Driver{"/dev/Control_LED"};
    Driver Button_Driver{"/dev/Control_Button"};
    int Input{};
    cout<<"Enter Blink Delay (ms) : ";
    cin>>Input;
    while(1)
    {
        if(Button_Driver.Read_File()!="1")
        {
            Button::Notify_On_Change('0');
            LED_Driver.Write_File("1",1);
            this_thread::sleep_for(chrono::milliseconds(Input));
            LED_Driver.Write_File("0",1);
            this_thread::sleep_for(chrono::milliseconds(Input));
        }
        else 
        {LED_Driver.Write_File("0",1);Button::Notify_On_Change('1');}
    }
    return 0;
}
