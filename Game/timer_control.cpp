#include "hwlib.hpp" 
#include "rtos.hpp"

class timer_control : rtos::task<>{
    enum state_t {IDLE, RUNNING};
    private:
        display & d;
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
        
public:
        void start(int gametime){
            timePool.write(gametime);
            timeFlag.set();
        }
        
        timer_control(display & d, game_control & g_control)
            d(d),
            g_control(g_control),
            timePool("timePool"),
            timeFlag(this, "timeFlag"),
            Timer(this, "Timer")
        {}
};