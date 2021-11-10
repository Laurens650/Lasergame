#ifndef DISPLAY_H
#define DISPLAY_H

#include "hwlib.hpp"
#include "rtos.hpp"

/// \brief
/// display ADT
/// \details
/// 
/// 
/// 

///@file

/// \brief
/// display ADT
/// \details
/// This class is an inheritance of rtos task.
/// It contains the pins, rtos objects and methods to control the display
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
    /// \brief
    /// display lives
    /// \details
    /// This method takes an integer as argument and shows the integer as lives on the display.
    void display_lives(int lives);
    /// \brief
    /// display time
    /// \details
    /// This method takes an integer (seconds) as argument and show the time in minutes and seconds on the display.
    void showtime(int seconds);
    /// \brief
    /// display lives
    /// \details
    /// This method takes an integer provided by the ingame leader and shows the time
    void show_command(int time_min);
    /// \brief
	/// constructor of the display
	/// \details
	/// This constructor initializes the displays
    display();

};


#endif //DISPLAY_H