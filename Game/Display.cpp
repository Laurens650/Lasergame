#include "hwlib.hpp" 
#include "rtos.hpp"

class display : public rtos::task<>{
    enum state_t {IDLE};
    private:
        rtos::flag livesFlag;
        rtos::flag timeFlag;
        rtos::flag commandFlag;
        auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
        auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
        auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);
        auto oled = hwlib::glcd_oled(bus, 0x3c);
        oled.clear();
        oled.flush();
        state_t state = IDLE;
        int Lives;
        int Seconds;
        int Time_min;
        int minutes;
        int display_seconds;
        auto font    = hwlib::font_default_8x8();
        auto Display = hwlib::terminal_from( oled, font );
        
        
        void main(){
            for(;;){
                switch(state){
                    case IDLE:
                        auto evt = wait(livesFlag + timeFlag + commandFlag);
                        if(evt==livesFlag){
                            minutes = Seconds % 60;
                            display_seconds = Seconds - (minutes * 60);
                            Display 
                                << 
                                << hwlib::flush;
                        }else if(evt==timeFlag){
                            
                        }else if(evt==commandFlag){
                            
                        }
                        oled.flush();
                }
            }
        }
        
    public:
        void display_lives(int lives){
            livesFlag.set();
            Lives = lives;
        }
        void showtime(int seconds){
            timeFlag.set();
            Seconds = seconds;
        }
        void show_command(int time_min){
            commandFlag.set();
            Time_min = time_min;
        }
        
        display():
            rtos::task(6, "display"),
            livesFlag(this, "livesFlag"),
            timeFlag(this, "timeFlag"),
            commandFlag(this, "commandFlag")
        {}
};