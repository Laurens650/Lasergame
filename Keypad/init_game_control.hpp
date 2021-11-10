///@file
#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"
#include "Keypad.hpp"
#include "../send_Franky/encode_control.hpp"
#include "../Game/Display.h"

/// this class initiates the game control
class Init_game_control : public rtos::task<> : public Keypad_listener{
enum state_t {IDLE, WAIT_DATA, SELECT_TIME, SEND_IR_MESSAGE};

private:
	display & d;
	Encode_control & e_control;
	Keypad & keypad;
	state_t state = IDLE;
	rtos::channel<char, 100> buttonChannel;
	void main();
	
public:
	Init_game_control(display & d, Encode_control & e_control, Keypad & keypad);
	/// \details
	///this functions detects if the button is pressed
	buttonPressed(char buttonID) override;

};

