#ifndef FIRE_BUTTON_H
#define FIRE_BUTTON_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "schiet_control.h"

///@file

/// \brief
/// button ADT
/// \details
/// This class is an inheritance of rtos task.
/// It contains the pins, rtos objects and methods to control the trigger button.
class Fire_button : public rtos::task<>{
    enum state_t {REFRESH};
private:
    state_t state = REFRESH;
    bool previous = 1;
    bool current = 1;
    rtos::timer timer;
    schiet_control & s_control;
    hwlib::pin_in & trigger;

    void main();
public:
    /// \brief
    /// constructor for Fire button
    /// \details
    /// This constructor initializes the fire button with a control and pin.
    Fire_button(schiet_control & s_control, hwlib::pin_in & trigger);

};

#endif //FIRE_BUTTON_H
