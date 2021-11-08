#include "hwlib.hpp" 
#include "rtos.hpp"

class game_control : rtos::task<>{
    enum state_t {IDLE, TIMER, START_CONTROLS};
    private:
        state_t state = IDLE;
    
        schiet_control & s_control;
        timer_control & t_control;
        hit_control & h_control;
        rtos::flag gamoverFlag;
        rtos::flag startFlag;
        rtos::timer Timer;
        int countDown;
        int gameTime;
        
        void main(){
            for(;;){
                switch(state){
                    case IDLE:
                        wait(startFlag);
                        state = TIMER;
                        break;
                    case TIMER:
                        Timer.set(countDown * 1000000);
                        wait(Timer);
                        state = START_CONTROLS;
                        break;
                    case START_CONTROLS:
                        h_control.start();
                        s_control.start();
                        t_control.start();
                        
                        wait(gamoverFlag);
                        h_control.stop();
                        s_control.stop();
                        t_control.stop();
                        break;
                }
            }
        }
        
    public:
        void meldGameover(){
            gamoverFlag.set();
        }
        void start(int gametime, int countdown){
            startFlag.set();
            countDown = countdown;
            gameTime = gametime;
        }
        
        game_control(schiet_control & s_control, timer_control & t_control, hit_control & h_control):
            rtos::task(4, "game_control"),
            s_control(s_control),
            t_control(t_control),
            h_control(h_control),
            gameoverFlag(this, "gameoverFlag"),
            startFlag(this, "startFlag"),
            Timer(this, "Timer")
        {}
};
