#pragma once
#include "hwlib.hpp"
#include "rtos.hpp"


#include "Bieper.cpp"
#include "Game_control.cpp"
#include "../hit_transfer/transfer_hit_control.cpp"
#include "../send_Franky/send.hpp"

class transfer_hit_control;
class game_control;
class hit_control : public rtos::task<>{
    enum state_t {OFF, IDLE};
    private:
        state_t state = OFF;

//        display & d;                                   // moet nog implemented worden
        transfer_hit_control & transfer_control;       // moet nog implemented worden

        Bieper & bieper;
        game_control & g_control;
        player_struct player_info;
        hit_report hits;
        rtos::channel<char, 2048> hitChannel;
        rtos::flag startFlag;
        rtos::flag stopFlag;
        rtos::flag get_hitsFlag;
        int lives = 200;
        int dmg;

        void store_player_info(player_struct player){
            bool found = false;
            for(unsigned int i = 0; i < hits.data.size(); i++){
                if(hits.data[i].player_nr == player.player_nr){
                    hits.data[i].hits ++;
                    found = true;
                    break;
                }
            }
            if(!found){
                hit_data d = {player.player_nr, 1};
                hits.data[hits.valid] = d;
                hits.valid ++;
            }
        }

    void main(){
        for(;;){
            switch(state){
                case OFF:
                    auto evt = wait(get_hitsFlag + startFlag);
                    if(evt==startFlag){
                        state = IDLE;
                    }else if(evt==get_hitsFlag){
                            transfer_control.pull_hits(hits);                      // moet nog implemented worden
                    }
                    break;
                case IDLE:
                    wait(hitChannel);
                    player_info = hitChannel.read()
                    dmg = player_struct.dmg;
                    bieper.play_hit();
                    lives -= dmg;
                    store_player_info(player_info);
//                        d.display_score(lives);                                  // moet nog implemented worden
                    if(lives <= 0){
                        g_control.meldGameover();
                        state = OFF;
                    }
                    break;
            }
        }
    }
        
    public:
        hit_control( Bieper & bieper, game_control & g_control, transfer_hit_control & transfer_control ):       //ADD PARAMETERS FOR FULL PROGRAM: "display & d, "
                rtos::task(3, "hit_control"),
                transfer_control(transfer_control),
                bieper(bieper),
                g_control(g_control),
                //        d(d),                                                      // moet nog implemented worden
                hitChannel(this, "hitChannel"),
                startFlag(this, "startFlag"),
                stopFlag(this, "stopFlag"),
                get_hitsFlag(this, "get_hitsFlag")
        {}

        void get_hits() {
            get_hitsFlag.set();
        }
        void start(){
                startFlag.set();
        }
        void stop(){
                stopFlag.set();
        }

        void hit_detected(player_struct player){
            hitChannel.write(player);
        }

    
};