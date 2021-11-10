#include "init_game_control.hpp"

void Init_game_control::main(){
	int gametime = 0;
	int start_countdown = 0;
	int remaining_time = 0;
	char buttonID;
	game_struct g_struct;
	while (true){
		switch(state){
			case IDLE:{
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if (buttonID == 'C'){
					state = WAIT_DATA;
				}
				else{
					state = IDLE;
				}
				break;
			}
			case WAIT_DATA:{
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if (buttonID >= '0' && buttonID <= '9'){
					state = SELECT_TIME;
				}
				else{
					state = WAIT_DATA;
				}
				break;
			}
			case SELECT_TIME:{
				gametime = (buttonID - '0' + 1) * 3;
				d.show_command(gametime);
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if (buttonID == '#'){
					start_countdown = hwlib::now_us();
					state = SEND_IR_MESSAGE;
				}
				else if (buttonID >= '0' && buttonID <= '9' ){
					state = SELECT_TIME;
				}
				break;
			}
			case SEND_IR_MESSAGE:{
				remaining_time = 30 - ((hwlib::now_us() - start_countdown) / 1000000);
				g_struct = {gametime, remaining_time};
				e_control.initialize(g_struct);
				wait(buttonChannel);
				buttonID = buttonChannel.read();
				remaining_time = 30 - ((hwlib::now_us() - start_countdown) / 1000000);
				if (buttonID == '*' && remaining_time > 0){
					state = SEND_IR_MESSAGE;
				}
				else{
					state = IDLE;	
				}
				break;
			}
		}
	}
}
	
Init_game_control::Init_game_control(Display & d, Encode_control & e_control, Keypad & keypad):
    task(9, "init_game_control"),
    d (d),
    e_control (e_control),
	keypad (keypad),
    buttonChannel (this, "ButtonChannel")
	{
	    keypad.addKeypad_listener(this);	
	}

void Init_game_control::buttonPressed(char buttonID){
	buttonChannel.write(buttonID);
}