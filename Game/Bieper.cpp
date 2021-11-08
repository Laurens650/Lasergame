#include "hwlib.hpp" 
#include "rtos.hpp" 

class Bieper: rtos::task(){
    private:
        hwlib::pin_out & lsp;
        
        void beep( hwlib::pin_out & lsp, int f, int d, int fd = 1000 ){
           auto t = hwlib::now_us();    
           auto end = t + d;
           while( end > hwlib::now_us() ){
               auto p = 500'000 / f;
               f = f * fd / 1000;
               lsp.write( 1 );
               lsp.flush();
               hwlib::wait( t += p );
               lsp.write( 0 );
               lsp.flush();
               hwlib::wait( t += p );
           }   
        }
        
    public:
        void play_hit(){
           for (int i = 0; i < 200; i++ ){
              lsp.write( 1 );
              lsp.flush();
              hwlib::wait_us( hwlib::random_in( 500, 600 )); 
              lsp.write( 0 );
              lsp.flush();
              hwlib::wait_us( hwlib::random_in( 500, 600 )); 
           }   
        }
        void play_shoot(){
            beep( lsp, 20'000, 200'000, 990 );
        }
        
        Bieper(hwlib::pin_out & lsp):
            rtos::task(7, "Bieper"),
            lsp(lsp)
        {}
};
