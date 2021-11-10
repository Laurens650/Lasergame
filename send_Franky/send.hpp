#ifndef SEND_HPP
#define SEND_HPP
///@file
#include "hwlib.hpp" 
#include "rtos.hpp" 

/// This is the struct taht saves the player_nr and the dmg
struct player_struct {
    int player_nr;
    int dmg;
};
/// This struct stores the times your hit by which player
struct hit_data {
    int player_nr;
    int hits;
};

/// This struct makes the array of everyone who hit you 
struct hit_report {
    std::array<hit_data, 31> data;
    int valid;
};

/// this struct saves rthe game time and the countdown
struct game_struct {
    int gametime;
    int countdown;
};

/// this makes the checksum to verify the encoded msg
static uint16_t generate_checksum(uint16_t msg) {
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

        checksum_mask_first >>= 1;
        checksum_mask_second >>= 1;
    }
    return result;
}

#endif