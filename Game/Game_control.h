#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "hit_control.h"
#include "schiet_control.h"
#include "timer_control.h"

class hit_control;
class timer_control;
class game_control : public rtos::task<>{
    enum state_t {IDLE, TIMER, START_CONTROLS};

private:
    state_t state = IDLE;

    schiet_control & s_control;
    timer_control & t_control;
    hit_control & h_control;
    rtos::flag gameoverFlag;
    rtos::flag startFlag;
    rtos::timer Timer;
    int countDown;
    int gameTime;

    void main();

public:
    void meldGameover();
    void start(int gametime, int countdown);
    game_control(schiet_control & s_control, timer_control & t_control, hit_control & h_control);

};

#endif //GAME_CONTROL_H
