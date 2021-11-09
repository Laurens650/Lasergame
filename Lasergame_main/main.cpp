#include "hwlib.hpp"
#include "rtos.hpp"
#include "../send_receive/pause_detector.h"
#include "../send_Franky/encode_control.hpp"
//#include "../Game/hit_control.cpp"

int main(){
    hwlib::wait_ms(2000);
    hwlib::cout << "start" << hwlib::endl;
    auto ir_receive = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto ir_send = hwlib::target::d2_36kHz();

    game_struct test = {15, 30};
//    player_struct test2 = {4, 14};

    Decode_control decode;
    Pause_control pause_ctrl(decode);
    Pause_detector pause_detec(pause_ctrl, ir_receive);

    Send_IR_control sender(ir_send);
    Encode_control encoder(sender);

    encoder.initialize(test);
//    encoder.shoot(test2);



    rtos::run();


}
