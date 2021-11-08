#include "hwlib.hpp" 
#include "rtos.hpp"

class schiet_control : rtos::task<>{
    enum state_t {IDLE, READY_TO_SHOOT, COOLDOWN};
    private:
        state_t state = IDLE;
        
        hwlib::target::pin_out led;
        Fire_button trigger;
        Player_info& p_info;
        Encode_control& e_control;
        Bieper& bieper;
        rtos::flag StartFlag;
        rtos::flag StopFlag;
        rtos::flag ButtonPressedFlag;
        rtos::flag ButtonReleasedFlag;
        rtos::timer Timer;
        player_info shoot_struct = p_info.get();
        int dps = 10;
        int firerate = dps / shoot_struct.dmg;

        
        void main(){
            for(;;){
                switch(state){
                    case IDLE:
                        wait(StartFlag);
                        state = READY_TO_SHOOT;
                        break;
                    case READY_TO_SHOOT:
                        led.write(0);
                        auto evt = wait(StopFlag + ButtonPressedFlag);
                        if(evt==StopFlag){
                            state = IDLE;
                        }
                        else if(evt==ButtonPressedFlag){
                            state = COOLDOWN;
                            bieper.play_shoot();
                            led.write(1);
                            e_control.shoot(shoot_struct);
                        }
                        break;
                    case COOLDOWN:
                        Timer.set(1000000 / firerate);
                        auto evt = wait(StopFlag + Timer);
                        if(evt==StopFlag){
                            state = IDLE;
                        }else if(evt==Timer){
                            state = READY_TO_SHOOT;
                        }
                        break;
                }
            }
        }
        
    public:
        schiet_control(Encode_control & e_control, Bieper& bieper, hwlib::target::pin_out & led):
            rtos::task(3, "schiet_control"),
            e_control(e_control),
            bieper(bieper),
            StartFlag(this, "StartFlag"),
            StopFlag(this, "StopFlag"),
            ButtonPressedFlag(this, "ButtonPressedFlag"),
            ButtonReleasedFlag(this, "ButtonReleasedFlag"),
            Timer(this, "Timer"),
            led(led)
        {}
        void start(){
            StartFlag.set();
        }
        void stop(){
            StopFlag.set();
        }
        void buttonPressed(){
            ButtonPressedFlag.set();
        }
        void buttonReleased(){
            ButtonReleasedFlag.set();
        }
};
