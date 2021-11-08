#include "hwlib.hpp"
#include "rtos.hpp"

class Encode_control : public rtos::task<>{
enum state_t {IDLE};

private:
	Send_IR_control & sendControl;
	state_t state = IDLE;
	rtos::channel<player_struct, 32> shootStructChannel;
	rtos::channel<game_struct, 32> gameStructChannel;
	
	void main(){
		uint16_t msg = 0;
		int player_nr = 0;
		int dmg = 0;
		int gametime = 0;
		int countdown = 0;
		while (true){
			switch (state){
				case IDLE:
					auto event = wait(shootStructChannel, gameStructChannel);
					if (event == shootStructChannel){
						shoot_info = shootStructChannel.read();
						player_nr = shoot_info.player_nr;
						dmg = shoot_info.dmg;
						msg = encode(player_nr, dmg); // wat doet encode?
						sendControl.send_msg(msg);
						state = IDLE;
						break;
					}
					else{
						game_info = gameStructChannel.read();
						gametime = game_info.gametime;
						countdown = game_info.countdown;
						msg = encode(0, gametime); // wat doet encode?
						sendControl.send_msg(msg);
						msg = encode(0, countdown);
						sendControl.send_msg(msg);
						state = IDLE;
						break;
					}
			}
		}
	}

public:
	Encode_control(Send_IR_control & sendControl):
	sendControl (sendControl),
	shootStructChannel (this, "shootStructChannel"),
	gameStructChannel (this, "gameStructChannel")
	{}
	
	void shoot(player_struct shoot_info){
		shootStructChannel.write(shoot_info);
	}
	void initialize(game_struct game_info){
		gameStructChannel.write(game_info);
	}
	
	void encode(int player_nr, int data){
		uint16_t msg = 0;
		msg = 1 << 15;
		msg |= player_nr <<10;
		msg |= data << 5;
		msg |= generate_checksum(msg);
	}
};