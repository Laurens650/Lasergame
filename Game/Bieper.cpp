#include "Bieper.h"


void Bieper::hit() {
    for (int i = 0; i < 200; i++ ){
        lsp.write( 1 );
        lsp.flush();
        hwlib::wait_us( hwlib::random_in( 500, 600 ));
        lsp.write( 0 );
        lsp.flush();
        hwlib::wait_us( hwlib::random_in( 500, 600 ));
    }
}

void Bieper::shoot(){
    beep( lsp, 880, 200'000, 990 );
}

void Bieper::beep( hwlib::pin_out & lsp, int f, int d, int fd ){
   auto t = hwlib::now_us();
   auto end = t + d;

   while( end > hwlib::now_us() ){

       auto p = 500'000 / f;
       f = f * fd / 1000;
       lsp.write( 1 );
       lsp.flush();

       hwlib::wait_us( p );
       lsp.write( 0 );
       lsp.flush();
       hwlib::wait_us( p );
   }
}

void Bieper::main() {
    for(;;){
        switch (state) {
            case WAIT: {
                auto evt = wait(hitFlag + shootFlag);
                if (evt == hitFlag) {
                    hit();
                } else {
                    shoot();
                }
                break;
            }
        }
    }
}

void Bieper::play_hit(){
    hitFlag.set();
}

void Bieper::play_shoot() {
    shootFlag.set();
}

Bieper::Bieper(hwlib::pin_out & lsp):
        task(18, "Bieper"),
        shootFlag(this, "shootFlag"),
        hitFlag(this, "hitFlag"),
        lsp(lsp)
{}