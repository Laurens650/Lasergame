#ifndef PARAMETER_CONTROL_H
#define PARAMETER_CONTROL_H
///@file
#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "../Game/Game_control.h"
#include "../send_Franky/send.hpp"
#include "Keypad.hpp"

///this class makes all the parameters for the players and the game itself.
class Parameter_control : public rtos::task<> : public Keypad_listener{
enum state_t {IDLE, WAIT_DATA, REGISTER_PLAYER_NR, DATA_WAIT, REGISTER_FIREPOWER}

private:
	player_struct & p_info;
	Game_control & g_control;
    Keypad & keypad;
	state_t state = IDLE;
	rtos::channel<char, 100> buttonChannel;
	rtos::channel<game_struct, 1> gameChannel;
	rtos::flag startFlag;
	void main();
	
public:
	Parameter_control(player_struct & p_info, Game_control & g_control);
	/// \details
	/// this function detects which button is pressed
	void buttonPressed(char buttonID) override;
	/// \details
	/// this function makes the start time of the game.
	void start(game_struct g_struct);
	
};

#endif // PARAMETER_CONTROL_H