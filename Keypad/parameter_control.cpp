#include "parameter_control.hpp"
#include "Keypad.hpp"

void Parameter_control::main(){
    char buttonID;
    int player_nr = 0;
    int firepower = 0;
    while(true){
        switch(state){
            case IDLE:{
//                logger.logText("STATE : IDLE");
                wait (buttonChannel);
                buttonID = buttonChannel.read();

//                logger.logInt(buttonID);
                if(buttonID == 'A'){
                    state = WAIT_DATA;
                }
                else{
                    state = IDLE;
                }
                break;
            }
            case WAIT_DATA:{
                logger.logText("STATE: WAIT_DATA");
                wait (buttonChannel);
                buttonID = buttonChannel.read();

//                logger.logInt(buttonID);
                if (buttonID >= '0' && buttonID <= '9'){
                    state = REGISTER_PLAYER_NR;
                }
                else{
                    state = IDLE;
                }
                break;
            }
            case REGISTER_PLAYER_NR:{
                logger.logText("STATE : REGISTER PLAYERNR");
                player_nr = (buttonID - '0');
                wait (buttonChannel);
                buttonID = buttonChannel.read();
//                logger.logInt(buttonID);
                if (buttonID == 'B'){
                    state = DATA_WAIT;
                }
                else{
                    state = IDLE;
                }
                break;
            }
            case DATA_WAIT:{
                logger.logText("STATE: DATA_WAIT");
                wait (buttonChannel);
                buttonID = buttonChannel.read();
//                logger.logInt(buttonID);
                if (buttonID >= '0' && buttonID <= '9'){
                    state = REGISTER_FIREPOWER;
                }
                else{
                    state = IDLE;
                }
                break;
            }
            case REGISTER_FIREPOWER:{
                logger.logText("STATE: REGISTER_FIREPOWER");
                firepower = (buttonID - '0') *3;

                p_info.set(player_nr, firepower);
                wait(gameChannel);
                g_info = gameChannel.read();
                g_control.start(g_info.gametime, g_info.countdown);
                state = IDLE;
                break;
            }
        }
    }
}

Parameter_control::Parameter_control(Player_info & p_info, game_control & g_control, Keypad & keypad, Logger &logger):
        task(8, "parameter_control"),
        p_info (p_info),
        g_control (g_control),
        keypad (keypad),
        buttonChannel (this, "buttonChannel"),
        gameChannel (this, "gameChannel"),
        startFlag (this, "startFlag"),
        logger(logger)
{
    keypad.addKeypad_listener(this);
}

void Parameter_control::buttonPressed(char buttonID) {
    buttonChannel.write(buttonID);
}

void Parameter_control::start(game_struct g_struct) {
    gameChannel.write(g_struct);
}