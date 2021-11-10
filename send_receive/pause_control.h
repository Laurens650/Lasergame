#ifndef PAUSE_CONTROL_H
#define PAUSE_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
//#include "../send_Franky/send.hpp"
#include "decode_control.h"

class Pause_control : public rtos::task<>{
    enum state_t {IDLE, MESSAGE};
private:
    rtos::channel<int, 32> pauseChannel;
    Decode_control & d_control;
    state_t state = IDLE;

    void main();

public:
    Pause_control(Decode_control & d_control);
    void pause_detected(int length);
};

#endif //PAUSE_CONTROL_H
