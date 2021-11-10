#ifndef BIEPER_H
#define BIEPER_H
/// @file

#include "hwlib.hpp"
#include "rtos.hpp"

/// this class is for the beeper and the sound it possesses
class Bieper{
private:
    hwlib::pin_out & lsp;
    void beep( hwlib::pin_out & lsp, int f, int d, int fd = 1000 );

public:
	/// \details
	/// this funtion plays the sound when a player is hit
    void play_hit();
	/// \details
	///this funtion plays the sound when you press the shoot button
    void play_shoot();
    Bieper(hwlib::pin_out & lsp);

};


#endif //BIEPER_H
