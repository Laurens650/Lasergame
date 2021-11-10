#ifndef SEND_IR_CONTROL_HPP
#define SEND_IR_CONTROL_HPP
///@file
#include "hwlib.hpp" 
#include "rtos.hpp" 

///this class sends the IR signal to the reciever
class Send_IR_control : public rtos::task<> {
    enum state_t { IDLE, WAIT_HIGH, WAIT_LOW, WAIT1600, WAIT800, SECOND_MSG };

private:
    hwlib::target::d2_36kHz & IR;
    state_t state = IDLE;
    uint16_t msg = 0;
    rtos::channel<uint16_t, 32> msgChannel;
    rtos::timer timer;
    void main();

public:
    Send_IR_control(hwlib::target::d2_36kHz & IR);
	/// \details
	///this funtion sends th bits to the IR reciever
    void send_msg(uint16_t msg);
};

#endif