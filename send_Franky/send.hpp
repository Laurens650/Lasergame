#ifndef SEND_HPP
#define SEND_HPP

#include "hwlib.hpp" 
#include "rtos.hpp" 

struct player_struct{
	int player_nr;
	int dmg;
};

struct game_struct{
	int gametime;
	int countdown;
};



#endif