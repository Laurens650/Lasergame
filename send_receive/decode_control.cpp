#include "decode_control.h"

Decode_control::Decode_control():   // ADD hit_control &h_control AS PARAMETER
    task(6, "decode_control"),
    MessageReceivedChannel ( this, "MessageReceivedChannel")
//    h_control(h_control)                 // HAS TO BE ADDED
//        p_control(p_control),         // HAS TO BE ADDED
{}

void Decode_control::decode_msg(uint16_t msg) {
    MessageReceivedChannel.write(msg);
}

void Decode_control::main() {
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
                player_nr = msg;
                player_nr >>= 10;
                player_nr &= mask;


                if(player_nr == 0){
                    if(first_msg){
                        gametime = msg;
                        gametime >>= 5;
                        gametime &= mask;
                        first_msg = 0;
                        hwlib::cout << "ho" << hwlib::endl;
                    }
                    else{
                        countdown = msg;
                        countdown >>= 5;
                        countdown &= mask;
//                        game_struct s = {gametime, countdown};
//                            p_control.start(s);                       // moet nog implemented worden
                        first_msg = 1;
                    }
                }
                else{
                    dmg = msg;
                    dmg >>= 5;
                    dmg &= mask;

                    hwlib::cout << "hi" << hwlib::endl;

//                    player_struct s = {player_nr, dmg};
//                    h_control.hit_detected(s);                        // NEEDS TO BE IMPLEMENTED
                }
                break;
        }
    }
}