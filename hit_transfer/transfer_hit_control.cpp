#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"

#include "../send_Franky/send.hpp"
#include "../Game/hit_control.cpp"

class hit_control;
class transfer_hit_control : public rtos::task<>{
    enum state_t {IDLE, read_write};
private:
    state_t state = IDLE;

    hit_control & h_control;
//    USB_poort & poort;                            // HAS TO BE IMPLEMENTED
    rtos::channel<std::array<hit_report, 1>, 1> hitsChannel;
    rtos::flag requestFlag;

    int countDown;
    int gameTime;

    void main(){
        for(;;){
            switch(state){
                case IDLE:
                    wait(requestFlag);
                    state = read_write;
                    break;
                case read_write:
                    h_control.get_hits();
                    wait(hitsChannel);
                    hit_report hits = hitsChannel.read();
//                    poort.write(hits);            // HAS TO BE IMPLEMENTED
            }
        }
    }

public:
    transfer_hit_control( hit_control & h_control):
            task(3, "transfer_hit_control"),
            h_control(h_control),
            requestFlag(this, "requestFlag"),
            hitsChannel(this, "hitsChannel")
    {}

    void write_request(){
        requestFlag.set();
    }

    void pull_hits(hit_report hits){
        hitsChannel.write(hits)
    }

};
