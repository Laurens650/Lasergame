#include "hwlib.hpp"
#include "rtos.hpp"

class Send_IR_control : public rtos::task<>{
enum state_t {IDLE, WAIT_HIGH, WAIT_LOW, WAIT1600, WAIT800, SECOND_MSG};

private:
	auto trigger = hwlib::target::pin_in(hwlib::target::pins::d7);
	auto ir = hwlib::target::pin_out(hwlib::target::pins::d8);
	
	
	state_t state = IDLE;
	uint16_t msg = 0;
	rtos::channel<uint16_t, 32> ms:timer timer;
	
	void main(){
		int counter = 0;
		uint16_t mask = 0;
		bool bit = 0;
		while (true){
			switch(state){
			case IDLE:
				wait(msgChannel);
				msg = msgChannel.read();
				counter = 0;
				mask = 1 << 15;
				state = WAIT_HIGH;
				break;
			case WAIT_HIGH:
				ir.write(1); // Kijken hoe IR sender word aangeroepen
				ir.flush();
				timer.set(9000)
				wait(timer);
				state = WAIT_LOW;
				break;
			case WAIT_LOW:
				ir.write(0);
				ir.flush();
				timer.set(4000)
				wait(timer);
				bit = msg & mask
				if(bit != 0){
					ir_pin.write(1);
					state = WAIT1600;
				}
				else{
					ir_pin.write(1);
					state = WAIT800;
				}
				break;
			case WAIT1600:
				timer.set(1600);
				wait(timer);
				if (bit == 0 ){
					mask >>= 1;
					if (mask == 0){
						state = SECOND_MSG;
					}
					else{
						bit = msg & mask;
						if(bit != 0){
							ir_pin.write(1);
							state = WAIT1600;
						}
						else{
							ir_pin.write(1);
							state = WAIT800;
						}
					}
				}
				else{
					ir_pin.write(0);
					state = WAIT800;
				}
				break;
			case WAIT800:
				timer.set(800);
				wait(timer);
				if(bit != 0){
					mask >>= 1;
					if (mask == 0){
						state = SECOND_MSG;
					}
					else{
						bit = msg & mask;
						if(bit != 0){
							ir_pin.write(1);
							state = WAIT1600;
						}
						else{
							ir_pin.write(1);
							state = WAIT800;
						}
					}
				}
				else{
					ir_pin.write(0);
					state = WAIT1600;
				}
				break;
			case SECOND_MSG:
				timer.set(4000);
				counter ++;
				mask = 1 << 15;
				wait(timer);
				if(counter < 2){
					bit = msg & mask
					if(bit != 0){
						ir_pin.write(1);
						state = WAIT1600;
					}
					else{
						ir_pin.write(1);
						state = WAIT800;
					}	
				}
				else{
					state = IDLE;
				}
				break;
			}
		}
	}

public:
	Send_IR_control():
	rtos::task(3, "Send_IR_Control"),
	msgChannel  (this, "msgChannel")
	{}
	
	void send_msg(uint16_t msg){}
};