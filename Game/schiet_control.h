#ifndef SCHIET_CONTROL_H
#define SCHIET_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Player_info.h"
#include "Bieper.h"
#include "../send_Franky/encode_control.hpp"
#include "../send_receive/logger2.hpp"

///@file

/// \brief
/// schiet_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// this class tells the bieper to play sounds, enable the led when a shot is fired and sends messages for the encoder to be encoded.
class schiet_control : public rtos::task<>{
    enum state_t {IDLE, READY_TO_SHOOT, COOLDOWN};
private:
    hwlib::pin_out & led;

    Player_info & p_info;
    Encode_control &e_control;
    Bieper& bieper;
    rtos::flag StartFlag;
    rtos::flag StopFlag;
    rtos::flag ButtonPressedFlag;
    rtos::flag ButtonReleasedFlag;
    rtos::timer Timer;
    Logger &logger;
    player_struct shoot_struct;
    int dps = 10;
    int firerate = dps / shoot_struct.dmg;

    state_t state = IDLE;
    void main();
public:

    /// \brief
    /// Costructor for schiet control
    /// \details
    /// This constructor initializes the hit control with the encode control, bieper, player info and pin of the led.
    schiet_control( Encode_control & e_control, Bieper & bieper, Player_info & p, hwlib::pin_out & led, Logger &logger);

    /// \brief
    /// Signals start
    /// \details
    /// This method signals the other controls when the game is starting.
    void start();

    /// \brief
    /// Signals start
    /// \details
    /// This method sets a flag to stop the game.
    void stop();

    /// \brief
    /// Signals button press
    /// \details
    /// This method sets a flag when the button is pressed
    void buttonPressed();

    /// \brief
    /// Signals button release
    /// \details
    /// This method sets a flag when the button is released
    void buttonReleased();
};

#endif //SCHIET_CONTROL_H
