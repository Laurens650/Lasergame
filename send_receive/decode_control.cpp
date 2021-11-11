#include "decode_control.h"

Decode_control::Decode_control(Logger & log, hit_control & h_control, Parameter_control & p_control):
    task(6, "decode_control"),
    h_control(h_control),
    p_control(p_control),
    MessageReceivedChannel ( this, "MessageReceivedChannel"),
    logger(log)
{}

void Decode_control::decode_msg(uint16_t msg) {
//    logger.logText("msg_received:");
//    logger.logInt(msg);
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


//                logger.logText("playernr");
//                logger.logInt(player_nr);
                if(player_nr == 0){
                    if(first_msg){
                        gametime = msg;
                        gametime >>= 5;
                        gametime &= mask;
                        logger.logText("gametime");
                        logger.logInt(gametime);
                        first_msg = 0;
                    }
                    else{
                        countdown = msg;
                        countdown >>= 5;
                        countdown &= mask;
                        logger.logText("countdown");
                        logger.logInt(countdown);
                        game_struct s = {gametime, countdown};
                        p_control.start(s);
                        first_msg = 1;
                    }
                }
                else{
                    dmg = msg;
                    dmg >>= 5;
                    dmg &= mask;
                    logger.logText("hit_detected");
                    player_struct s = {player_nr, dmg};
                    h_control.hit_detected(s);
                }
                break;
        }
    }
}