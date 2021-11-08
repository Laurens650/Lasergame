#include "hwlib.hpp"
#include "rtos.hpp"

class Fire_button : public rtos::task<>{
    private:
        schiet_control & s_control;
        auto trigger = hwlib::target::pin_in(hwlib::target::pins::d23);
        trigger.pullup_enable();
        
        void main(){
            for(;;){
                trigger.refresh();
                if(trigger.read()==1){
                    s_control.buttonPressed();
                }else{
                    s_control.buttonReleased();
                }
                hwlib::wait_ms(5);
            }
        }
        
    public:
        Fire_button(schiet_control & s_control):
            rtos::task(5, "Fire_button"),
            s_control(s_control)
        {}
};
