#ifndef BIEPER_H
#define BIEPER_H

#include "hwlib.hpp"
#include "rtos.hpp"

class Bieper{
private:
    hwlib::pin_out & lsp;
    void beep( hwlib::pin_out & lsp, int f, int d, int fd = 1000 );

public:
    void play_hit();
    void play_shoot();
    Bieper(hwlib::pin_out & lsp);

};


#endif //BIEPER_H
