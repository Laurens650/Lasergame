#ifndef HIT_CONTROL_H
#define HIT_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Bieper.cpp"
#include "Game_control.h"
#include "Display.h"
#include "../hit_transfer/transfer_hit_control.cpp"
#include "../send_Franky/send.hpp"

///@file

class transfer_hit_control;
class game_control;

/// \brief
/// hit_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for calculating the remaining lives of the player.
/// It is also responsible for making a sound will be played when the player is hit
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
    /// \brief
	/// Costructor for hit control
	/// \details
	/// This constructor initializes the hit control with the bieper and game control.
    hit_control( Bieper & bieper, game_control & g_control):       //ADD PARAMETERS FOR FULL PROGRAM: "display & d, transfer_hit_control & transfer_control"
    /// \brief
	/// Sets the hit flag
	/// \details
	/// This method sets a flag when the player is hit.
    void get_hits();
    /// \brief
	/// Signals start
	/// \details
	/// This method sets a flag to start the game.
    void start();
    /// \brief
	/// Signals start
	/// \details
	/// This method sets a flag to stop the game.
    void stop();
    /// \brief
	/// Registers hits
	/// \details
	/// This method detect hit and is responsible for deducting the damage from a player's life.
    void hit_detected(player_struct player);

};


#endif //HIT_CONTROL_H