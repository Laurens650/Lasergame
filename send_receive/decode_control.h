#ifndef DECODE_CONTROL_HPP
#define DECODE_CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "../send_Franky/send.hpp"
//#include "../Game/hit_control.cpp"

class Decode_control : public rtos::task<>{
    enum state_t {WAIT_FOR_MSG};

private:
//    hit_control & h_control;                              // NEEDS TO BE IMPLEMENTED
    rtos::channel<uint16_t, 2> MessageReceivedChannel;
    state_t state = WAIT_FOR_MSG;
    bool first_msg = 1;

    void main();

public:
    Decode_control();    // NEED TO ADD PARAMETER CONTROL AND HIT_CONTROL: hit_control & h_control
    void decode_msg(uint16_t msg);
};


#endif //DECODE_CONTROL_HPP
