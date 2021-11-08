#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"
#include "schiet_control.cpp"

class Fire_button : public rtos::task<>{
    private:
        schiet_control & s_control;
        hwlib::target::pin_in trigger;
        trigger.pullup_enable();
        
        void main(){
            for(;;){
                trigger.refresh();
                if(trigger.read()==0){
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
            trigger(hwlib::target::pins::d23),
            s_control(s_control)
        {}
};
