#include "hwlib.hpp"
#include "rtos.hpp"
#include "send.hpp"
#include "encode_control.hpp"

void Encode_control::main(){
	uint16_t msg = 0;
	int player_nr = 0;
	int dmg = 0;
	int gametime = 0;
	int countdown = 0;
	while (true){
		switch (state){
			case IDLE:
				auto event = wait(shootStructChannel + gameStructChannel);
				if (event == shootStructChannel){
					shoot_data = shootStructChannel.read();
					player_nr = shoot_data.player_nr;
					dmg = shoot_data.dmg;
					msg = encode(player_nr, dmg);
					sendControl.send_msg(msg);
					state = IDLE;
					break;
				}
				else{
					game_data = gameStructChannel.read();
					gametime = game_data.gametime;
					countdown = game_data.countdown;
					msg = encode(0, gametime);
					sendControl.send_msg(msg);
					msg = encode(0, countdown);
					sendControl.send_msg(msg);
					state = IDLE;
					break;
				}
		}
	}
}

Encode_control::Encode_control(Send_IR_control & sendControl):
	task(3, "encode_control"),
	sendControl (sendControl),
	shootStructChannel (this, "shootStructChannel"),
	gameStructChannel (this, "gameStructChannel")
{}

void Encode_control::shoot(player_struct shoot_info){
	shootStructChannel.write(shoot_info);
}
void Encode_control::initialize(game_struct game_info){
	gameStructChannel.write(game_info);
}

uint16_t  Encode_control::encode(int player_nr, int data){
	uint16_t msg = 0;
	msg = 1 << 15;
	msg |= player_nr <<10;
	msg |= data << 5;
	msg |= generate_checksum(msg);
	return msg;
}