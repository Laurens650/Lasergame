#include "parameter_control.hpp"
#include "Keypad.hpp"

void Parameter_control::main(){
	char buttonID;
	int player_nr = 0;
	int firepower = 0;
	while(true){
		switch(state){
			case IDLE:{
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if(buttonID == 'A'){
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
					state = REGISTER_PLAYER_NR;
				}
				else{
					state = IDLE;
				}
				break;
			}
			case REGISTER_PLAYER_NR:{
				player_nr = (buttonID - '0');
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if (buttonID == 'B'){
					state = DATA_WAIT;
				}
				else{
					state = IDLE;
				}
				break;
			}
			case DATA_WAIT:{
				wait (buttonChannel);
				buttonID = buttonChannel.read();
				if (buttonID >= '0' && buttonID <= '9'){
					state = REGISTER_FIREPOWER;
				}
				else{
					state = IDLE;
				}
				break;
			}
			case REGISTER_FIREPOWER:{
				firepower = buttonID; // dmg formule en char to int?
				wait(gameChannel);
				game_struct g_info = gameChannel.read();
				g_control.start(g_info.gametime, g_info.countdown);
				state = IDLE;
				break;
			}
		}
	}
}
	
Parameter_control::Parameter_control(player_struct & p_info, Game_control & g_control, Keypad & keypad):
    task(8, "parameter_control"),
    p_info (p_info),
	g_control (g_control),
	keypad (keypad),
    buttonChannel (this, "buttonChannel"),
    gameChannel (this, "gameChannel"),
    startFlag (this, "startFlag")
	{
		keypad.addKeypad_listener(this);
	}

void Parameter_control::buttonPressed(char buttonID) {
	buttonChannel.write(buttonID);
}

void Parameter_control::start(game_struct g_struct) {
	gameChannel.write(g_struct);
}