#ifndef SEND_HPP
#define SEND_HPP

#include "hwlib.hpp" 
#include "rtos.hpp"

///@file

/// \brief
/// player data struct
/// \details
/// struct containing the player number and damage.
struct player_struct {
    int player_nr;
    int dmg;
};

/// \brief
/// hit data struct
/// \details
/// struct containing the total hits and by which player number.
struct hit_data {
    int player_nr;
    int hits;
};

/// \brief
/// hit report struct
/// \details
/// struct containing the player numbers of players hit by.
struct hit_report {
    std::array<hit_data, 31> data;
    int valid;
};

/// \brief
/// game struct
/// \details
/// struct containing the gametime and countdown.
struct game_struct {
    int gametime;
    int countdown;
};

/// \brief
/// generates IR-checksum for given message
/// \details
/// This function returns a generated checksum of a given message, to be used to verify incoming messages.
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