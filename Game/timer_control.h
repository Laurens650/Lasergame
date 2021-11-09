#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Game_control.h"
#include "Display.h"

class game_control;
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
    void start(int gametime);
};

#endif //TIMER_CONTROL_H