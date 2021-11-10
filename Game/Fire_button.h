#ifndef FIRE_BUTTON_H
#define FIRE_BUTTON_H
///@file

#include "hwlib.hpp"
#include "rtos.hpp"
#include "schiet_control.h"

///this class is the input button for when the trigger is pulled. 
class Fire_button : public rtos::task<>{
    enum state_t {REFRESH};
private:
    state_t state = REFRESH;
    rtos::timer timer;
    schiet_control & s_control;
    hwlib::target::pin_in trigger;
    trigger.pullup_enable();

    void main();
public:
    Fire_button(schiet_control & s_control, hwlib::pin_in & trigger);

};

#endif //FIRE_BUTTON_H
