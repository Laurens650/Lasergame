#ifndef SEND_HPP
#define SEND_HPP

#include "hwlib.hpp" 
#include "rtos.hpp" 

struct player_struct {
    int player_nr;
    int dmg;
};

struct hit_data {
    int player_nr;
    int hits;
};

struct hit_report {
    std::array<hit_data, 31> data;
    int valid;
};

struct game_struct {
    int gametime;
    int countdown;
};

uint16_t generate_checksum(uint16_t msg) {
    uint16_t checksum_mask_first = 0x4000;
    uint16_t checksum_mask_second = 0x200;

    uint16_t result = 0x00;
    for (int i = 0; i < 5; i++) {
        uint16_t masked_first = msg & checksum_mask_first;
        uint16_t masked_second = msg & checksum_mask_second;

        masked_first = (masked_first != 0) ? 1 : 0;
        masked_second = (masked_second != 0) ? 1 : 0;

        result <<= 1;
        result |= (masked_first ^ masked_second) ? 1 : 0;
    }
    return result;
}

class Send_IR_control : public rtos::task<> {
    enum state_t { IDLE, WAIT_HIGH, WAIT_LOW, WAIT1600, WAIT800, SECOND_MSG };

private:
    hwlib::pin_in& trigger;
    hwlib::pin_out& IR;
    state_t state = IDLE;
    uint16_t msg = 0;
    rtos::channel<uint16_t, 32> msgChannel;
    rtos::timer timer;
    void main();

public:
    Send_IR_control(hwlib::pin_in& trigger, hwlib::pin_out& IR);
    void send_msg(uint16_t msg);
};

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