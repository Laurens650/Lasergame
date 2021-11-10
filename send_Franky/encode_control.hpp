#ifndef ENCODE_CONTROL_HPP
#define ENCODE_CONTROL_HPP
#include "hwlib.hpp" 
#include "rtos.hpp"
#include "Send_IR_control.hpp"

///@file

/// \brief
/// Encode_control ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for encoding and preparing messages that are to be send
class Encode_control : public rtos::task<> {
    enum state_t { IDLE };

private:
    Send_IR_control& sendControl;
    state_t state = IDLE;
    player_struct shoot_data;
    game_struct game_data;
    rtos::channel<player_struct, 32> shootStructChannel;
    rtos::channel<game_struct, 32> gameStructChannel;
    void main();

public:
/// \brief
	/// Costructor for Encode_control
	/// \details
	/// This constructor initializes the encode control with the send IR control, timer_control and hit_control.
    Encode_control(Send_IR_control& sendControl);
    /// \brief
	/// send shot
	/// \details
	/// This method sends an encoded shot message to the IR control.
    void shoot(player_struct shoot_info);
    /// \brief
	/// send game parameters
	/// \details
	/// This method sends an encoded message containing the game parameters to the IR control.
    void initialize(game_struct game_info);
    /// \brief
	/// encode data
	/// \details
	/// This method returns an encoded message containing the player number and data in a message.
    uint16_t encode(int player_nr, int data);

};

#endif