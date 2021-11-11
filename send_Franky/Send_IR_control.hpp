#ifndef SEND_IR_CONTROL_HPP
#define SEND_IR_CONTROL_HPP

#include "hwlib.hpp" 
#include "rtos.hpp"
#include "../send_receive/logger2.hpp"

///@file

/// \brief
/// Game_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It contains rtos objects and methods needed to send an IR message.
/// It is responsible for sending the encoded message by pulsating the IR led on diffrent timings.
class Send_IR_control : public rtos::task<> {
    enum state_t { IDLE, WAIT_HIGH, WAIT_LOW, WAIT1600, WAIT800, END_HIGH, SECOND_MSG };

private:
    hwlib::target::d2_36kHz & IR;
    state_t state = IDLE;
    uint16_t msg = 0;
    rtos::channel<uint16_t, 32> msgChannel;
    rtos::timer timer;

    Logger &logger;


    void main();

public:

    /// \brief
    /// Costructor for Send_IR_control
    /// \details
    /// This constructor initializes the Send IR control with the d2_36kHz object
    Send_IR_control(hwlib::target::d2_36kHz & IR, Logger & log);

    /// \brief
    /// Sends IR message
    /// \details
    /// This method takes a 16 bit message as argument and writes it to a message channel where it will be send
    void send_msg(uint16_t msg);
};

#endif