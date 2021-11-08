#include "hwlib.hpp" 
#include "rtos.hpp" 

uint16_t generate_checksum(uint16_t msg){
    return msg;
}

class Pause_control : public rtos::task<>{
enum state_t {IDLE, MESSAGE};
	
private:
	Decode_control & d_control;
	rtos::channel<int, 32> pauseChannel;
	state_t state = IDLE;
	
	void main(){
	    uint16_t msg;
	    int counter;
	    uint16_t checksum_mask;
	    uint16_t checksum_recieved;
	    uint16_t checksum_generated;
	    int length;sen
		
		while(true){
			switch (state){
                case IDLE:
                    wait(pauseChannel);
                    length = pauseChannel.read();
                    if(4000 < length && length < 5000){
                        msg = 0x01;
                        counter = 0;
                        state = MESSAGE;
                    }
                    break;

                case MESSAGE:
                    if(counter < 15){
                        wait(pauseChannel);
                        length = pauseChannel.read();
                        if(length > 200 && length < 2000){
                            msg <<= 1;
                            msg |= (length > 1000) ? 1 : 0;
                            counter ++;
                        }
                        else{
                            state = IDLE;
                        }
                    }
                    else{
                        checksum_mask = 0x1F;
                        checksum_recieved = msg & checksum_mask;
                        checksum_generated = generate_checksum(msg);
                        if(checksum_recieved == checksum_generated){
                            d_control.decode_msg(msg);
                        }
                        else{
                            state = IDLE;
                        }
                    }
                    break;
			}
		}
	}
	
public:
	Pause_control(Decode_Control & d_control):
        d_control (d_control),
        pauseChannel (this, "pauseChannel")
	{}
	
	void pause_detected(int length){
		pauseChannel.write(length);
	}
};