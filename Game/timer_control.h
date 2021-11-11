#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Display.h"

///@file

class game_control;

/// \brief
/// timer_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for keeping track of and showuing the remaining time and signals a stop when the timer has run out.
class timer_control : public rtos::task<>{
    enum state_t {IDLE, RUNNING};
private:
    state_t state = IDLE;
    display & d;

    game_control *g_control;
    rtos::pool<int> timePool;
    rtos::flag timeFlag;
    rtos::timer Timer;
    int time;

    void main();

public:

    /// \brief
    /// Costructor for timer control
    /// \details
    /// This constructor initializes the timer control with a display and game control
    timer_control(display & d);

    /// \brief
    /// Signals start
    /// \details
    /// This method signals the other controls when the game is starting.
    void start(int gametime);

    void set_game_p(game_control *game);

};

#endif //TIMER_CONTROL_H