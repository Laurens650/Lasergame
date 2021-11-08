#include "hwlib.hpp"
#include "rtos"


class Pause_detector : public rtos::task<>{
enum state_t {Idle, wait};

private:
    Pause_control & p_control;
    IR_receiver ir_receiver;
    state_t state = Idle;
    rtos::timer timer;
    int length = 0;
    bool signal;

    void main(){
        while(true){
            switch (state){
                case Idle:
                    timer.set(100);
                    wait(timer);
                    signal = ir_receiver.read();
                    if (signal == 0){
                        p_control.pause_detected(length);
                        state = wait;
                    }
                    else{
                        length += 100;
                        state = Idle;
                    }
                    break;
                case wait:
                    timer.set(100);
                    wait(timer);
                    signal = ir_receiver.read();
                    if (signal == 0){
                        state = wait;
                    }
                    else{
                        length = 0;
                        state = Idle;
                    }
                    break;
            }
        }
    }

public:
    Pause_detector(Pause_control & p_control, IR_receiver ir_receiver):
    timer(this, "timer"),
    p_control (p_control),
    ir_receiver (ir_receiver)
    {}

};