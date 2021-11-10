#ifndef PARAMETER_CONTROL_H
#define PARAMETER_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "../Game/Game_control.h"
#include "../send_Franky/send.hpp"
#include "Keypad.hpp"

class Parameter_control : public rtos::task<> , public Keypad_listener{
enum state_t {IDLE, WAIT_DATA, REGISTER_PLAYER_NR, DATA_WAIT, REGISTER_FIREPOWER};

private:
	player_struct & p_info;
	Game_control & g_control;
    Keypad & keypad;
	rtos::channel<char, 100> buttonChannel;
	rtos::channel<game_struct, 1> gameChannel;
	rtos::flag startFlag;
	state_t state = IDLE;
	void main();
	
public:
	Parameter_control(player_struct & p_info, Game_control & g_control, Keypad & keypad);
	void buttonPressed(char buttonID) override;
	void start(game_struct g_struct);
	
};

#endif // PARAMETER_CONTROL_H