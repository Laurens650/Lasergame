#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"

class Parameter_control : public rtos::task<> : public Keypad_listener{
enum state_t {IDLE, WAIT_DATA, REGISTER_PLAYER_NR, DATA_WAIT, REGISTER_FIREPOWER}

private:
	player_struct & p_info;
	Game_control & g_control;
    Keypad & keypad;
	state_t state = IDLE;
	rtos::channel<char, 100> buttonChannel;
	rtos::flag startFlag;
	void main();
	
public:
	Parameter_control(player_struct & p_info, Game_control & g_control);
	void buttonPressed(char buttonID) override;
	void start(game_struct g_struct);
	
};