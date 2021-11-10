#ifndef ENCODE_CONTROL_HPP
#define ENCODE_CONTROL_HPP
///@file
#include "hwlib.hpp" 
#include "rtos.hpp"
#include "Send_IR_control.hpp"

/// this class encodes the IR signal
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
    Encode_control(Send_IR_control& sendControl);
	/// \details
	/// this function sends the encoded msg to IR control if the player shoots
    void shoot(player_struct shoot_info);
	/// \details
	/// this function mkaes the msg that initializes the game
    void initialize(game_struct game_info);
	/// \details
	/// this funtion holds the player_nr and the data 
    uint16_t encode(int player_nr, int data);

};

#endif