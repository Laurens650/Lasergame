#include "schiet_control.h"

void schiet_control::main() {
    for (;;) {
        switch (state) {
            case IDLE: {
                wait(StartFlag);
                state = READY_TO_SHOOT;
                break;
            }
            case READY_TO_SHOOT: {
                led.write(0);
                auto evt = wait(StopFlag + ButtonPressedFlag);
                if (evt == StopFlag) {
                    state = IDLE;
                } else if (evt == ButtonPressedFlag) {
                    state = COOLDOWN;
                    bieper.play_shoot();
                    led.write(1);
                    shoot_struct = p_info.get();
//                    logger.logText("shoot_struct_info");
//                    logger.logInt(shoot_struct.player_nr);
//                    logger.logInt(shoot_struct.dmg);
                    e_control.shoot(shoot_struct);
                }
                break;
            }
            case COOLDOWN: {
                Timer.set(1000000 / firerate);
                auto evt2 = wait(StopFlag + Timer);
                if (evt2 == StopFlag) {
                    state = IDLE;
                } else {
                    state = READY_TO_SHOOT;
                }
                break;
            }
        }
    }
}

schiet_control::schiet_control(Encode_control & e_control, Bieper & bieper, Player_info & p, hwlib::pin_out & led, Logger &logger):
    task(11, "schiet_control"),
    led(led),
    p_info(p),
    e_control(e_control),
    bieper(bieper),
    StartFlag(this, "StartFlag"),
    StopFlag(this, "StopFlag"),
    ButtonPressedFlag(this, "ButtonPressedFlag"),
    ButtonReleasedFlag(this, "ButtonReleasedFlag"),
    Timer(this, "Timer"),
    logger(logger)
{}

void schiet_control::start(){
    StartFlag.set();
}
void schiet_control::stop(){
    StopFlag.set();
}
void schiet_control::buttonPressed(){
    ButtonPressedFlag.set();
}
void schiet_control::buttonReleased(){
    ButtonReleasedFlag.set();
}