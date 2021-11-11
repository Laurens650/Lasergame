#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "hit_control.h"
#include "schiet_control.h"
#include "timer_control.h"

///@file

class hit_control;
class timer_control;

/// \brief
/// Game_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It contains references to diffrent controls, rtos objects and methods to control the game
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

    /// \brief
    /// Signals gameover
    /// \details
    /// This method signals the other controls when the game is over.
    void meldGameover();

    /// \brief
    /// Signals start
    /// \details
    /// This method signals the other controls when the game is starting.
    void start(int gametime, int countdown);

    /// \brief
    /// Costructor for Game_control
    /// \details
    /// This constructor initializes the game control with the schiet_control, timer_control and hit_control.
    game_control(schiet_control & s_control, timer_control & t_control, hit_control & h_control);

};

#endif //GAME_CONTROL_H
