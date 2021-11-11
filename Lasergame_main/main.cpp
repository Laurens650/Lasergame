#include "hwlib.hpp"
#include "rtos.hpp"

#include "all.h"


int main(){
    hwlib::wait_ms(2000);
    hwlib::cout << "start" << hwlib::endl;

    auto dumpLogButtonPin = hwlib::target::pin_in( hwlib::target::pins::d42 );
    Logger logger(0,dumpLogButtonPin);

    //=========================================
    auto ir_receive = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto ir_send = hwlib::target::d2_36kHz();
    auto bieper = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto led = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto trigger = hwlib::target::pin_in(hwlib::target::pins::d6);

    auto out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
    auto out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
    auto out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
    auto out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

    auto in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
    auto in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
    auto in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
    auto in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );

    auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
    auto keypad   = hwlib::keypad< 16 >( matrix, "D#0*C987B654A321" );

    Keypad pad(keypad);

    //=========================================

    Bieper biep(bieper);
    display d = display();
    Player_info p_info = Player_info();
    Send_IR_control sender(ir_send, logger);
    Encode_control encoder(sender, logger);
    hit_control hit(biep, d, logger);
    timer_control time(d);
    schiet_control schiet(encoder,biep ,p_info, led, logger);

    Fire_button fire(schiet, trigger);

    game_control game(schiet, time, hit);

    hit.set_game_p(&game);
    time.set_game_p(&game);
    //=========================================

    Parameter_control param(p_info, game, pad, logger);
    Decode_control decode(logger, hit, param);
    Pause_control pause_ctrl(decode, logger);
    Pause_detector pause_detec(pause_ctrl, ir_receive, logger);



    Init_game_control init(d, encoder, pad, logger);
    rtos::run();


}
