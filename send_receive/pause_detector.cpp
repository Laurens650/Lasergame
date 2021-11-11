#include "pause_detector.h"

Pause_detector::Pause_detector(Pause_control & p_control, hwlib::pin_in & ir_receiver, Logger & log):
        task(1, "pause_detector"),
        timer(this, "timer"),
        p_control (p_control),
        ir_receiver (ir_receiver),
        logger(log)
{}

void Pause_detector::main(){
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