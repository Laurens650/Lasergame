#ifndef BIEPER_H
#define BIEPER_H


#include "hwlib.hpp"
#include "rtos.hpp"

/// @file

/// \brief
/// Bieper ADT
/// \details
/// This is an ADT that contains the pins for the Bieper.
/// The methods can be used to play sounds
class Bieper{
private:
    hwlib::pin_out & lsp;
    /// \brief
	/// constructor from pins and integers
	/// \details
	/// This constructor initializes the bieper with a pin and integers
    void beep( hwlib::pin_out & lsp, int f, int d, int fd = 1000 );

public:
    /// \brief
    /// Plays hit sound.
	/// \details
	/// this method can be called to play an hit sound.
    void play_hit();
    /// \brief
    /// Plays shoot sound.
	/// \details
	/// this method can be called to play a shoot sound.
    void play_shoot();
    Bieper(hwlib::pin_out & lsp);

};


#endif //BIEPER_H
