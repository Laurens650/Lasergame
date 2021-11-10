#ifndef PAUSE_CONTROL_H
#define PAUSE_CONTROL_H
///@file
#include "hwlib.hpp"
#include "rtos.hpp"
//#include "../send_Franky/send.hpp"
#include "decode_control.h"

/// this class checks the checksum and discards the second msg if the first msg is right
class Pause_control : public rtos::task<>{
    enum state_t {IDLE, MESSAGE};
private:
    rtos::channel<int, 32> pauseChannel;
    Decode_control & d_control;
    state_t state = IDLE;

    void main();

public:
    Pause_control(Decode_control & d_control);
	/// \details
	/// this function detects if the pause is from a long or short bit.
    void pause_detected(int length);
};

#endif //PAUSE_CONTROL_H
