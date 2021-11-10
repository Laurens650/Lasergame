#ifndef HIT_CONTROL_H
#define HIT_CONTROL_H
///@file
#include "hwlib.hpp"
#include "rtos.hpp"

#include "Bieper.cpp"
#include "Game_control.h"
#include "Display.h"
#include "../hit_transfer/transfer_hit_control.cpp"
#include "../send_Franky/send.hpp"

class transfer_hit_control;
class game_control;

/// this class calculates the lives of certain player sends it to the display. This also makes sure that a sound is played when the player is hit.
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
	/// \details
	/// this fuction sets the flag to start the game. 
    void start();
	/// \details
	/// this fuction sets the flag to stop the game. 
    void stop();
	///this fuction detects if a player is hit and adds the dmg to your lives and sends it to your display.
    void hit_detected(player_struct player);

};


#endif //HIT_CONTROL_H