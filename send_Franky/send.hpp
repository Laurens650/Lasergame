#ifndef SEND_HPP
#define SEND_HPP

struct player_struct{
	int player_nr;
	int dmg;
};

struct hit_data {
    int player_nr;
    int hits;
};

struct hit_report{
    std::array<hit_data, 31> data;
    int valid;
};

struct game_struct{
	int gametime;
	int countdown;
};

uint16_t generate_checksum(uint16_t msg){
    uint16_t checksum_mask_first = 0x4000;
    uint16_t checksum_mask_second = 0x200;

    uint16_t result = 0x00;
    for(int i = 0; i++; i < 5){
        uint16_t masked_first = msg & checksum_mask_first;
        uint16_t masked_second = msg & checksum_mask_second;

        masked_first = (masked_first != 0) ? 1 : 0;
        masked_second = (masked_second != 0) ? 1 : 0;

        result <<= 1;
        result |= (masked_first ^ masked_second) ? 1 : 0;
    }
    return result;
}

#endif