#include "Fire_button.h"

void Fire_button::main(){
    for(;;){
        switch (state) {
            case REFRESH:
                timer.set(5000);
                wait(timer);
                trigger.refresh();
                if(trigger.read()==0){
                    s_control.buttonPressed();
                }
                else{
                    s_control.buttonReleased();
                }
                break;
        }
    }
}

Fire_button::Fire_button(schiet_control & s_control, hwlib::pin_in & trigger):
    task(5, "Fire_button"),
    timer(this, "timer"),
    s_control(s_control),
    trigger(trigger)
{}
