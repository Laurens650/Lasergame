#include "hwlib.hpp" 
#include "rtos.hpp"

class display : public rtos::task<>{
    enum state_t {IDLE};
    private:
        rtos::flag livesFlag;
        rtos::flag timeFlag;
        rtos::flag commandFlag;
        hwlib::target::pin_oc scl;
        hwlib::target::pin_oc sda;
        hwlib::i2c_bus_bit_banged_scl_sda bus;
        hwlib::glcd_oled oled;
        oled.clear();

        state_t state = IDLE;
        int Lives;
        int Seconds;
        int Time_min;
        int minutes;
        int display_seconds;
        hwlib::font_default_8x8 font;
        hwlib::terminal_from Display;

        std::array<char, 2> two_ints_to_char(int a){
            if (a < 10){
                char eental = (char)a + '0';
                std::array<char, 2> array = {'0', eental};
                return array;
            }
            else{
                float int_decimal = a / 10.0;
                int left = (int)int_decimal;
                int right = a % 10;

                char tiental = (char)(left + '0');
                char eental = (char)(right + '0');

                std::array<char, 2> array = {tiental, eental};
                return array;
            }
        }

        std::array<char, 3> three_ints_to_char(int a){
            if ( a < 100 ){
                std::array<char, 2> b = two_ints_to_char(a);
                std::array<char, 3> array = {'0',  b[0], b[1]};
                return array;
            }
            else{
                float int_decimal = a / 100.0;
                int left = (int)int_decimal;
                char honderdtal = (char)(left + '0');

                int rest = (float)(int_decimal - left) * 100;
                std::array<char, 2> b = two_ints_to_char(rest);
                std::array<char, 3> array = {honderdtal, b[0], b[1]};
                return array;
            }

        }
        
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
                        }
                        else if(evt==timeFlag){
                            
                        }
                        else if(evt==commandFlag){
                            
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
            commandFlag(this, "commandFlag"),
            scl(hwlib::target::pins::scl),
            sda(hwlib::target::pins::sda),
            bus(scl, sda),
            oled(bus, 0x3c),
            font(),
            Display( oled, font )
        {}
};