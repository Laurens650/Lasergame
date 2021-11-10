#ifndef HIT_CONTROL_H
#define HIT_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Bieper.cpp"
#include "Game_control.h"
#include "Display.h"
#include "../hit_transfer/transfer_hit_control.cpp"
#include "../send_Franky/send.hpp"

class transfer_hit_control;
class game_control;
class hit_control : public rtos::task<>{
    enum state_t {OFF, IDLE};
private:
    state_t state = OFF;

    display & d;
//    transfer_hit_control & transfer_control;       // moet nog implemented worden

    Bieper & bieper;
    game_control & g_control;
    player_struct player_info;
    hit_report hits;
    rtos::channel<char, 2048> hitChannel;
    rtos::flag startFlag;
    rtos::flag stopFlag;
    rtos::flag get_hitsFlag;
    int lives = 200;
    int dmg;

    void store_player_info(player_struct player);
    void main();
public:
    hit_control( Bieper & bieper, game_control & g_control):       //ADD PARAMETERS FOR FULL PROGRAM: "display & d, transfer_hit_control & transfer_control"

    void get_hits();
    void start();
    void stop();
    void hit_detected(player_struct player);

};


#endif //HIT_CONTROL_H