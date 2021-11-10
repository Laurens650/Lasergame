#ifndef SCHIET_CONTROL_H
#define SCHIET_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Player_info.h"
#include "Bieper.h"

///@file

/// \brief
/// schiet_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// this class tells the bieper to play sounds, enable the led when a shot is fired and sends messages for the encoder to be encoded. 
class schiet_control : public rtos::task<>{
    enum state_t {IDLE, READY_TO_SHOOT, COOLDOWN};
private:
    hwlib::target::pin_out led;

    Player_info & p_info;
    Encode_control& e_control;
    Bieper& bieper;
    rtos::flag StartFlag;
    rtos::flag StopFlag;
    rtos::flag ButtonPressedFlag;
    rtos::flag ButtonReleasedFlag;
    rtos::timer Timer;
    player_struct shoot_struct = p_info.get();
    int dps = 10;
    int firerate = dps / shoot_struct.dmg;

    state_t state = IDLE;
    void main();
public:
    /// \brief
	/// Costructor for schiet control
	/// \details
	/// This constructor initializes the hit control with the encode control, bieper, player info and pin of the led.
    schiet_control(Encode_control & e_control, Bieper & bieper, Player_info & p, hwlib::target::pin_out & led);
   
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
