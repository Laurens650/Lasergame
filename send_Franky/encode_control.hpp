#ifndef ENCODE_CONTROL_HPP
#define ENCODE_CONTROL_HPP

#include "hwlib.hpp" 
#include "rtos.hpp"
#include "Send_IR_control.hpp"

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
    void shoot(player_struct shoot_info);
    void initialize(game_struct game_info);
    uint16_t encode(int player_nr, int data);

};

#endif