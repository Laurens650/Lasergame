#include "hwlib.hpp"
#include "rtos.hpp"
#include "Send_IR_control.hpp"
	
void Send_IR_control::main(){
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
			IR.write(1);
			IR.flush();
			timer.set(9000);
			wait(timer);
			state = WAIT_LOW;
			break;
		case WAIT_LOW:
			IR.write(0);
			IR.flush();
			timer.set(4000);
			wait(timer);
			bit = msg & mask;
			if(bit != 0){
				IR.write(1);
				state = WAIT1600;
			}
			else{
				IR.write(1);
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
						IR.write(1);
						IR.flush();
						state = WAIT1600;
					}
					else{
						IR.write(1);
						IR.flush();
						state = WAIT800;
					}
				}
			}
			else{
				IR.write(0);
				IR.flush();
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
						IR.write(1);
                        IR.flush();
						state = WAIT1600;
					}
					else{
						IR.write(1);
                        IR.flush();
						state = WAIT800;
					}
				}
			}
			else{
				IR.write(0);
                IR.flush();
				state = WAIT1600;
			}
			break;
		case SECOND_MSG:
			timer.set(3000);
                counter ++;
                mask = 1 << 15;
                wait(timer);
                if(counter < 2){
                    bit = msg & mask;
				if(bit != 0){
					IR.write(1);
                    IR.flush();
					state = WAIT1600;
				}
				else{
					IR.write(1);
                    IR.flush();
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

Send_IR_control::Send_IR_control(hwlib::target::d2_36kHz & IR):
	task(5, "Send_IR_Control"),
	IR (IR),
	msgChannel  (this, "msgChannel"),
	timer (this, "timer")
{}
	
void Send_IR_control::send_msg(uint16_t msg){
	msgChannel.write(msg);
}
