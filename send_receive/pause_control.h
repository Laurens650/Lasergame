#ifndef PAUSE_CONTROL_H
#define PAUSE_CONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
//#include "../send_Franky/send.hpp"
#include "decode_control.h"
#include "logger2.hpp"

///@file

/// \brief
/// Pause_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for processing the pauses that are detected.
class Pause_control : public rtos::task<>{
    enum state_t {IDLE, MESSAGE};
private:
    rtos::channel<int, 32> pauseChannel;
    Decode_control & d_control;
    state_t state = IDLE;

    Logger &logger;

    void main();

public:

    /// \brief
    /// Costructor for Pause_control
    /// \details
    /// This constructor initializes the Pausecontrol with the Decode_control.
    Pause_control(Decode_control & d_control, Logger & log);

    /// \brief
    /// stores pause lengths
    /// \details
    /// This method writes the length of the detected pauses to the pause channel
    void pause_detected(int length);
};

#endif //PAUSE_CONTROL_H
