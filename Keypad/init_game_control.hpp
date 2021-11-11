#ifndef INIT_GAME_CONTROL_HPP
#define INIT_GAME_CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "Keypad.hpp"
#include "../send_Franky/encode_control.hpp"
#include "../Game/Display.h"

#include "../send_receive/logger2.hpp"

///@file

/// \brief
/// Init_game_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// This class is also an inheritance of keypad listener.
/// It is responsible for initializing the game control
class Init_game_control : public rtos::task<>, public Keypad_listener{
    enum state_t {IDLE, WAIT_DATA, SELECT_TIME, SEND_IR_MESSAGE};

private:
    display & d;
    Encode_control & e_control;
    Keypad & keypad;
    state_t state = IDLE;
    rtos::channel<char, 100> buttonChannel;

    Logger & logger;

    void main();

public:

    /// \brief
    /// Costructor for init game control
    /// \details
    /// This constructor initializes the init game control with the display, encode control and keypad
    Init_game_control(display & d, Encode_control & e_control, Keypad & keypad, Logger &logger);

    /// \brief
    /// writes to button channel
    /// \details
    /// This method writes the button presses to the buttonChannel.
    void buttonPressed(char buttonID) override;

};

#endif //INIT_GAME_CONTROL_HPP