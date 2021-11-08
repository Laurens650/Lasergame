#include "hwlib.hpp"
#include "rtos.hpp"

class Send_IR_control : public rtos::task<>{
    enum state_t {IDLE, START, LOOP, SECOND_MSG};

private:
    hwlib::target::d2_36kHz ir_sender = hwlib::target::d2_36kHz();
    rtos::channel<uint16_t, 2> msgChannel;
    rtos::timer wachten;
    state_t state = IDLE;

    void write_bit(bool bit){
        if(bit){
            ir_sender.write(1);
            hwlib::wait_us_busy(1600);
            ir_sender.write(0);
            hwlib::wait_us_busy(800);
        }
        else{
            ir_sender.write(1);
            hwlib::wait_us_busy(800);
            ir_sender.write(0);
            hwlib::wait_us_busy(1600);
        }
    }

    void main(){
        int counter;
        uint16_t msg;
        uint16_t mask;
        int bit;

        for(;;){
            switch (state) {
                case IDLE:
                    wait(msgChannel);
                    msg = msgChannel.read();
                    counter = 0;
                    state = START;
                    break;

                case START:
                    mask = 0x01;
                    mask <<= 15;
                    if(counter < 2){
                        state = LOOP;
                    }
                    else{
                        state = IDLE;
                    }
                    break;

                case LOOP:
                   bit = msg & mask;
                   mask >>= 1;
                   if(bit != 0){
                       write_bit(1);
                       if(mask == 0){
                           state = SECOND_MSG;
                       }
                   }
                   else{
                       write_bit(0);
                       if(mask == 0){
                           state = SECOND_MSG;
                       }
                   }
                   break;

                case SECOND_MSG:
                    counter ++;
                    wachten.set(4000);
                    wait(wachten);
                    state = START;
                    break;
            }
        }
    }

public:
    Send_IR_control():
        msgChannel(this, "msgChannel"),
        wachten(this, "wachten")
    {}

    void send_msg(uint16_t msg){
        msgChannel.write(msg);
    }

};