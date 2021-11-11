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
class Bieper: public rtos::task<>{
    enum state_t {WAIT};
private:
    state_t state = WAIT;
    rtos::flag shootFlag;
    rtos::flag hitFlag;

    hwlib::pin_out & lsp;

    void shoot();
    void hit();

    /// \brief
    /// plays a note on a given beeper
    /// \details
    /// this function creates a note on a given beeper (lsp)
    void beep( hwlib::pin_out & lsp, int f, int d, int fd );

    void main();
public:

    /// \brief
    /// constructor from pins and integers
    /// \details
    /// This constructor initializes the bieper with a pin and integers
    Bieper(hwlib::pin_out & lsp);

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
};


#endif //BIEPER_H
