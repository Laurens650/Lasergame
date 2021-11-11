#include "timer_control.h"
#include "Game_control.h"

void timer_control::main(){
    for(;;){
        switch(state){
            case IDLE: {
                wait(timeFlag);
                time = timePool.read();
                state = RUNNING;
                break;
            }
            case RUNNING: {
                d.showtime(time);
                Timer.set(1000000);
                wait(Timer);
                if (time == 0) {
                    g_control->meldGameover();
                    state = IDLE;
                } else {
                    time--;
                }
                break;
            }
        }
    }
}

timer_control::timer_control(display & d):                        // ADD AS PARAMETER FOR FULL PROGRAM: " "
    task(12, "timer_control"),
    d(d),
    timePool("timePool"),
    timeFlag(this, "timeFlag"),
    Timer(this, "Timer")
{}

void timer_control::start(int gametime){
    timePool.write(gametime);
    timeFlag.set();
}

void timer_control::set_game_p(game_control *game){
    g_control = game;
}
