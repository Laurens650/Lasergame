#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"

class Pause_detector : public rtos::task<>{
enum state_t {IDLE, WAIT};

private:
    Pause_control & p_control;
    hwlib::target::pin_in ir_receiver;
    state_t state = IDLE;
    rtos::timer timer;
    int length = 0;
    bool signal;

    void main(){
        while(true){
            switch (state){
                case IDLE:
                    timer.set(100);
                    wait(timer);
                    signal = ir_receiver.read();
                    if (signal == 0){
                        p_control.pause_detected(length);
                        state = WAIT;
                    }
                    else{
                        length += 100;
                        state = IDLE;
                    }
                    break;

                case WAIT:
                    timer.set(100);
                    wait(timer);
                    signal = ir_receiver.read();
                    if (signal == 0){
                        state = WAIT;
                    }
                    else{
                        length = 0;
                        state = IDLE;
                    }
                    break;
            }
        }
    }

public:
    Pause_detector(Pause_control & p_control, hwlib::target::pin_in & ir_receiver):
        rtos::task(1, "pause_detector"),
        timer(this, "timer"),
        p_control (p_control),
        ir_receiver (ir_receiver)
    {}

};