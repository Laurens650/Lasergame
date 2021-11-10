#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H
///@file


#include "../send_Franky/send.hpp"
///this class sets the player_nr and the dmg in the constructor
class Player_info{
private:
    player_struct info;

public:
    player_struct get(){
        return info;
    }
	/// \details
	/// this set fuction sets the player_nr and the dmg in the struct.
    void set(int player_nr, int dmg){
        info.player_nr = player_nr;
        info.dmg = dmg;
    }
};


#endif // PLAYER_CONTROL_H