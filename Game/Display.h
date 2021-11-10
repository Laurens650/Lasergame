#ifndef DISPLAY_H
#define DISPLAY_H

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

    state_t state = IDLE;
    int Lives;
    int Seconds;
    int Time_min;
    int minutes;
    int display_seconds;
    std::array<char, 3> live;
    std::array<char, 2> min;
    std::array<char, 2> sec;
    hwlib::font_default_16x16 font;
    hwlib::terminal_from Display;

    std::array<char, 2> two_ints_to_char(int a);
    std::array<char, 3> three_ints_to_char(int a);
    void main();

public:

    void display_lives(int lives);
    void showtime(int seconds);
    void show_command(int time_min);
    display();

};


#endif //DISPLAY_H