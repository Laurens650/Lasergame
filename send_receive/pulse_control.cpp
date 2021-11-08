#include "hwlib.hpp" 
#include "rtos.hpp" 

class Pulse_control : public rtos::task<>{
enum state_t {WAIT_FOR_PULSE, WAIT, READ};

private:
	Recieve_control & r_control;
	IR_receiver ir_receiver;
	state_t state = Waiting_for_Pulse;
	rtos::timer timer;
	
	void main(){
		while (true){
			switch (state){
				case Waiting_for_Pulse:
                    bool signal = ir_receiver.read();
                    if(signal == true){
                        state = WAIT;
                    }
                    else{
                        state = WAIT_FOR_PULSE;
                    }
                    break;

				case wait:
					timer.set(1200); // moet nog naar gekeken worden
					wait(timer);
					state = READ;
					break;

				case read:
					signal = IR_receiver.read();
					Receive_control.receive_bit(signal);
					timer.set(1200);
					wait (timer);
					state = WAIT_FOR_PULSE;
					break;
			}
		}
	}

public:
	Pulse_control(Recieve_control & r_control):
	r_control (r_control),
	timer(this, "timer")
	{}
	ir_receiver () // Moet nog naar gekeken worden hoe dit wordt gemaakt

};