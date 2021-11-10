#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H

///@file 

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Game_control.h"
#include "Display.h"

class game_control;

/// This is a class for the timer_control. The timer_control is used for remaining time for the player while in game. This also states the gameover if the time reaches 0 seconds.
class timer_control : public rtos::task<>{
    enum state_t {IDLE, RUNNING};
private:
    state_t state = IDLE;
    display & d;

    game_control & g_control;
    rtos::pool<int> timePool;
    rtos::flag timeFlag;
    rtos::timer Timer;
    int time;

    void main();

public:

    timer_control(display & d, game_control & g_control);
	/// \details
	/// this fuction sets the flag to start the game. 
    void start(int gametime);
};

#endif //TIMER_CONTROL_H