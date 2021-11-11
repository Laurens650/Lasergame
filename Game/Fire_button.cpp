#include "Fire_button.h"

void Fire_button::main(){
    for(;;){
        switch (state) {
            case REFRESH: {
                timer.set(100000);
                wait(timer);
                trigger.refresh();
                current = trigger.read();
                if (current == 0 && previous != 0) {
                    s_control.buttonPressed();
                } else {
                    s_control.buttonReleased();
                }
                previous = current;
                break;
            }
        }
    }
}

Fire_button::Fire_button(schiet_control & s_control, hwlib::pin_in & trigger):
    task(17, "Fire_button"),
    timer(this, "timer"),
    s_control(s_control),
    trigger(trigger)
{}
