#ifndef INIT_GAME_CONTROL_HPP
#define INIT_GAME_CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "Keypad.hpp"
#include "../send_Franky/encode_control.hpp"
#include "../Game/Display.h"

class Init_game_control : public rtos::task<>, public Keypad_listener{
enum state_t {IDLE, WAIT_DATA, SELECT_TIME, SEND_IR_MESSAGE};

private:
	Display & d;
	Encode_control & e_control;
	Keypad & keypad;
	state_t state = IDLE;
	rtos::channel<char, 100> buttonChannel;
	void main();
	
public:
	Init_game_control(Display & d, Encode_control & e_control, Keypad & keypad);
	void buttonPressed(char buttonID) override;

};

#endif //INIT_GAME_CONTROL_HPP