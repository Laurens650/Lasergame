#ifndef DECODE_CONTROL_HPP
#define DECODE_CONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "../send_Franky/send.hpp"
#include "../Game/hit_control.h"
#include "logger2.hpp"
#include "../Keypad/parameter_control.hpp"


///@file

/// \brief
/// Decode_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for decoding incoming messages.
class Decode_control : public rtos::task<>{
    enum state_t {WAIT_FOR_MSG};

private:
    state_t state = WAIT_FOR_MSG;

    hit_control & h_control;
    Parameter_control & p_control;
    rtos::channel<uint16_t, 2> MessageReceivedChannel;
    bool first_msg = 1;

    Logger &logger;

    void main();

public:

    /// \brief
    /// Costructor for Decode_control
    /// \details
    /// This constructor initializes the decode control
    Decode_control(Logger & log, hit_control & h_control, Parameter_control & p_control);

    /// \brief
    /// Decode message
    /// \details
    /// This method writes the message that is to be decoded to the Message Received Channel.
    void decode_msg(uint16_t msg);
};


#endif //DECODE_CONTROL_HPP
