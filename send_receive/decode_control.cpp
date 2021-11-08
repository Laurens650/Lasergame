#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"

#include "../send_Franky/send.hpp"
#include "../Game/hit_control.cpp"

class Decode_control : public rtos::task<>{
    enum state_t {WAIT_FOR_MSG};

private:
//    Parameter_control & p_control;                                // moet nog implemented worden
    hit_control & h_control;

    rtos::channel<uint16_t, 2> MessageReceivedChannel;
    state_t state = WAIT_FOR_MSG;

    bool first_msg = 1;

    void main(){
        uint16_t msg;
        uint16_t mask;

        uint16_t player_nr;
        uint16_t dmg;
        uint16_t gametime;
        uint16_t countdown;


        while(true){
            switch (state) {
                case WAIT_FOR_MSG:
                    wait(MessageReceivedChannel);
                    msg = MessageReceivedChannel.read();
                    mask = 0x1F;
                    player_nr >>= 10;
                    player_nr &= mask;

                    if(player_nr == 0){
                        if(first_msg){
                            gametime = msg;
                            gametime >>= 5;
                            gametime &= mask;
                            first_msg = 0;
                        }
                        else{
                            countdown = msg;
                            countdown >>= 5;
                            countdown &= mask;
                            game_struct s = {gametime, countdown};
//                            p_control.start(s);                       // moet nog implemented worden
                            first_msg = 1;
                        }
                    }
                    else{
                        dmg = msg;
                        dmg >>= 5;
                        dmg &= mask;
                        player_struct s = {player_nr, dmg};
                        h_control.hit_detected(s);
                    }
                    break;

            }
        }
    }

public:
    Decode_control( hit_control & h_control):                                  // ADD PARAMETER FOR FULL PROGRAM: "Parameter_control & p_control,"
        rtos::task(3, "decode_control"),
        MessageReceivedChannel ( this, "MessageReceivedChannel"),
        h_control(h_control)
//        p_control(p_control),

    {}
    void decode_msg(uint16_t msg){
        MessageReceivedChannel.write(msg);
    }


};