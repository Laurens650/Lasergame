#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "../send_Franky/send.hpp"

///@file

/// \brief
/// Player_info ADT
/// \details
/// This class sets and returns the player info

class Player_info{
private:
    player_struct info;

public:

    /// \brief
    /// returns player info
    /// \details
    /// This method return the player info which contains the player number and damage.
    player_struct get(){
        return info;
    }

    /// \brief
    /// sets player info
    /// \details
    /// This method set the player info which contains the player number and damage.
    void set(int player_nr, int dmg){
        info.player_nr = player_nr;
        info.dmg = dmg;
    }
};


#endif // PLAYER_CONTROL_H