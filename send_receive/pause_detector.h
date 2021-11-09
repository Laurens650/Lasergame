#ifndef PAUSE_DETECTOR_H
#define PAUSE_DETECTOR_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "pause_control.h"

class Pause_detector : public rtos::task<> {
    enum state_t {IDLE, WAIT};
private:
    rtos::timer timer;
    Pause_control & p_control;
    hwlib::pin_in & ir_receiver;
    state_t state = IDLE;
    int length = 0;
    bool signal;

    void main();

public:
    Pause_detector(Pause_control & p_control, hwlib::pin_in & ir_receiver);

};


#endif //PAUSE_DETECTOR_H
