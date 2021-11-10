#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "../send_Franky/send.hpp"

class Player_info{
private:
    player_struct info;

public:
    player_struct get(){
        return info;
    }

    void set(int player_nr, int dmg){
        info.player_nr = player_nr;
        info.dmg = dmg;
    }
};


#endif // PLAYER_CONTROL_H