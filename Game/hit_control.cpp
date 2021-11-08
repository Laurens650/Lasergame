#include "hwlib.hpp" 
#include "rtos.hpp" 

struct hit_data {
    int player_nr;
    int hits;
}

class hit_control : public rtos::task<>{
    enum state_t {OFF, IDLE};
    private:
        state_t state = OFF;
        
        display & d;
        Bieper & bieper;
        game_control & g_control;
        Transfer_hit_control & transfer_control;
        rtos::flag startFlag;
        rtos::flag stopFlag;
        rtos::flag get_hitsFlag;
        struct player_struct;
        int dmg;
        int lives = 200;
        

        
        std::array<hit_data, 31> s;
        int valid = 0;
        
        void store_player_info(player_struct player){
            bool found = false;
            for(usigned int i = 0; i < s.size(); i++){
                if(s[i].player_nr == player.player_nr){
                    s[i].hits ++;
                    found = true;
                    break;
                }
            }
            if(!found){
                hit_data d = {player.player_nr, 1};
                s[valid] = d;
                valid ++;
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
                            transfer_control.pull_hits(s);
                        }
                        break;
                    case IDLE:
                        wait(hitChannel);
                        player_struct = hitChannel.read()
                        dmg = player_struct.dmg;
                        bieper.play_hit();
                        lives -= dmg;
                        store_player_info(player_struct);
                        d.display_score(lives);
                        if(lives <= 0){
                            g_control.meldGameover();
                            state = OFF;
                        }
                        break;
                }
            }
        }
        
    public:
        rtos::channel<char, 2048> hitChannel(this, "hitChannel");
    
        void start(){
            startFlag.set();
        }
        void stop(){
            stopFlag.set();
        }
        void hit_detected(struct player_sturct){
            hitChannel.write(player_struct);
        }
    
    
    hit_control(display & d, Bieper & bieper, Game_control & g_control, Transfer_hit_control & transfer_control):
        rtos::task(3, "hit_control"),
        d(d),
        bieper(bieper),
        g_control(g_control),
        transfer_control(transfer_control),
        startFlag(this, "startFlag"),
        stopFlag(this, "stopFlag"),
        get_hitsFlag(this, "get_hitsFlag")
    {}
    
    
};

