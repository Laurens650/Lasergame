#include "hit_control.h"
#include "Game_control.h"

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
            case OFF: {
                auto evt = wait(get_hitsFlag + startFlag);
                if (evt == startFlag) {
                    state = IDLE;
                } else {
//                    transfer_control.pull_hits(hits);                      // moet nog implemented worden
                }
                break;
            }
            case IDLE: {
                auto evt = wait(hitChannel + stopFlag);
                if(evt == hitChannel) {
                    logger.logText("hit received");
                    player_info = hitChannel.read();
                    dmg = player_info.dmg;
                    bieper.play_hit();
                    lives -= dmg;
                    logger.logInt(lives);
                    store_player_info(player_info);
                    if (lives <= 0) {
                        d.display_lives(0);
                        g_control->meldGameover();
                        state = OFF;
                    }
                    else{
                        d.display_lives(lives);
                    }
                }
                else{
                    state = OFF;
                }
                break;
            }
        }
    }
}

hit_control::hit_control( Bieper & bieper, display & d, Logger &logger):            // ADD FOR FULL PROGRAM: "transfer_hit_control & transfer_control "
        task(10, "hit_control"),
        d(d),
        bieper(bieper),
//        transfer_control(transfer_control),
        hitChannel(this, "hitChannel"),
        startFlag(this, "startFlag"),
        stopFlag(this, "stopFlag"),
        get_hitsFlag(this, "get_hitsFlag"),
        logger(logger)
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

void hit_control::set_game_p(game_control *game){
    g_control = game;
}