#ifndef SEND_IR_CONTROL_HPP
#define SEND_IR_CONTROL_HPP

#include "hwlib.hpp" 
#include "rtos.hpp" 

class Send_IR_control : public rtos::task<> {
    enum state_t { IDLE, WAIT_HIGH, WAIT_LOW, WAIT1600, WAIT800, SECOND_MSG };

private:
    hwlib::pin_in& trigger;
    hwlib::pin_out& IR;
    state_t state = IDLE;
    uint16_t msg = 0;
    rtos::channel<uint16_t, 32> msgChannel;
    rtos::timer timer;
    void main();

public:
    Send_IR_control(hwlib::pin_in& trigger, hwlib::pin_out& IR);
    void send_msg(uint16_t msg);
};

#endif