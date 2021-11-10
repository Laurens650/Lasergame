#include "timer_control.h"

void timer_control::main(){
    for(;;){
        switch(state){
            case IDLE:
                wait(timeFlag);
                time = timePool.read();
                state = RUNNING;
                break;
            case RUNNING:
                d.showtime(time);
                Timer.set(1000000);
                wait(Timer);
                if(time==0){
                    g_control.meldGameover();
                    state = IDLE;
                }else{
                    time--;
                }
        }
    }
}

timer_control::timer_control(display & d, game_control & g_control):                        // ADD AS PARAMETER FOR FULL PROGRAM: " "
    task(3, "timer_control"),
    d(d),
    g_control(g_control),
    timePool("timePool"),
    timeFlag(this, "timeFlag"),
    Timer(this, "Timer")
{}

void timer_control::start(int gametime){
    timePool.write(gametime);
    timeFlag.set();
}