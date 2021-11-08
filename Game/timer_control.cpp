#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"
#include "Game_control.cpp"

class game_control;

class timer_control : public rtos::task<>{
    enum state_t {IDLE, RUNNING};
    private:
        state_t state = IDLE;
    
//        display & d;                                          // GOTTA BE IMPLEMENTED

        game_control & g_control;
        rtos::pool<int> timePool;
        rtos::flag timeFlag;
        rtos::timer Timer;
        int time;
        
        void main(){
            for(;;){
                switch(state){
                    case IDLE:
                        wait(timeFlag);
                        time = timePool.read();
                        state = RUNNING;
                        break;
                    case RUNNING:
//                        d.showtime(time);                         // GOTTA BE IMPLEMENTED
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
        
    public:
        timer_control(game_control & g_control):                        // ADD AS PARAMETER FOR FULL PROGRAM: "display & d, "
            rtos::task(3, "timer_control"),
//            d(d),                                                     // GOTTA BE IMPLEMENTED
            g_control(g_control),
            timePool("timePool"),
            timeFlag(this, "timeFlag"),
            Timer(this, "Timer")
        {}

        void start(int gametime){
            timePool.write(gametime);
            timeFlag.set();
        }
};
