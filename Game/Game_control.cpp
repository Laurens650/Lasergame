#include "Game_control.h"

void game_control::main() {
    for (;;) {
        switch (state) {
            case IDLE: {
                wait(startFlag);
                state = TIMER;
                break;
            }
            case TIMER: {
                Timer.set(countDown * 1000000);
                wait(Timer);
                state = START_CONTROLS;
                break;
            }
            case START_CONTROLS: {
                h_control.start();
                s_control.start();
                t_control.start(gameTime * 60);

                wait(gameoverFlag);
                h_control.stop();
                s_control.stop();
                state = IDLE;
                break;
            }
        }
    }
}
void game_control::meldGameover(){
    gameoverFlag.set();
}

void game_control::start(int gametime, int countdown){
    startFlag.set();
    countDown = countdown;
    gameTime = gametime;
}

game_control::game_control(schiet_control & s_control, timer_control & t_control, hit_control & h_control):
    task(13, "game_control"),
    s_control(s_control),
    t_control(t_control),
    h_control(h_control),
    gameoverFlag(this, "gameoverFlag"),
    startFlag(this, "startFlag"),
    Timer(this, "Timer")
{}
