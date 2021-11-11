#ifndef PARAMETER_CONTROL_H
#define PARAMETER_CONTROL_H

///@file

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "../Game/Game_control.h"
#include "../send_Franky/send.hpp"
#include "Keypad.hpp"

#include "../send_receive/logger2.hpp"

/// \brief
/// Init_game_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// This class is also an inheritance of keypad listener.
/// It is responsible for handling the game parameters and communicates this with game_control
class Parameter_control : public rtos::task<> , public Keypad_listener{
    enum state_t {IDLE, WAIT_DATA, REGISTER_PLAYER_NR, DATA_WAIT, REGISTER_FIREPOWER};

private:
    Player_info & p_info;
    game_control & g_control;
    Keypad & keypad;
    game_struct g_info;
    rtos::channel<char, 100> buttonChannel;
    rtos::channel<game_struct, 1> gameChannel;
    rtos::flag startFlag;

    Logger & logger;

    state_t state = IDLE;
    void main();

public:

    /// \brief
    /// Costructor for parameter control
    /// \details
    /// This constructor initializes the parameter control with player info and game control.
    Parameter_control(Player_info & p_info, game_control & g_control, Keypad & keypad, Logger &logger);

    /// \brief
    /// writes to button channel
    /// \details
    /// This method writes the button presses to the buttonChannel.
    void buttonPressed(char buttonID) override;

    /// \brief
    /// Signals start
    /// \details
    /// This method passes the game parameters to the gane_control
    void start(game_struct g_struct);

};

#endif // PARAMETER_CONTROL_H