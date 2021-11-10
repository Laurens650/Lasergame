#ifndef SCHIET_CONTROL_H
#define SCHIET_CONTROL_H
///@file
#include "hwlib.hpp"
#include "rtos.hpp"

#include "Player_info.h"
#include "Bieper.h"

/// this class plays the sounds of the beeper, makes sure that the led works and sends the messages for the encoder. 
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
    schiet_control(Encode_control & e_control, Bieper & bieper, Player_info & p, hwlib::target::pin_out & led);
	/// \details
	/// this fuction sets the flag to start the game. 
    void start();
	/// \details
	/// this fuction sets the flag to stop the game. 
    void stop();
	/// \details
	/// if the button is pressed then the buttonPressedFlag is set. 
    void buttonPressed();
	/// \details
	/// if the button is released then the buttonReleasedFlag is set. 
    void buttonReleased();
};

#endif //SCHIET_CONTROL_H
