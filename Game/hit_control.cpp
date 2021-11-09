#include "hit_control.h"

void hit_control::store_player_info(player_struct player){
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

void hit_control::main(){
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
                d.display_score(lives);
                if(lives <= 0){
                    g_control.meldGameover();
                    state = OFF;
                }
                break;
        }
    }
}

hit_control::hit_control( Bieper & bieper, game_control & g_control, transfer_hit_control & transfer_control ):
        task(3, "hit_control"),
        transfer_control(transfer_control),
        bieper(bieper),
        g_control(g_control),
        d(d),
        hitChannel(this, "hitChannel"),
        startFlag(this, "startFlag"),
        stopFlag(this, "stopFlag"),
        get_hitsFlag(this, "get_hitsFlag")
{}

void hit_control::get_hits() {
    get_hitsFlag.set();
}
void hit_control::start(){
    startFlag.set();
}
void hit_control::stop(){
    stopFlag.set();
}
void hit_control::hit_detected(player_struct player){
    hitChannel.write(player);
}