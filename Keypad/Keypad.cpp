#include "hwlib.hpp"
#include "rtos.hpp"
#include <array>
#include "keypad_listener.hpp"

void Keypad::main(){
    while(true){
        switch (state){
            case WAIT:
                auto c = kbd.getc();
                timer.set(60000);
                wait(timer);
                state = WAIT;
        }
    }
}

Keypad::Keypad(hwlib::keypad< 16 > & keypad):
keypad (keypad),
timer (this, "timer")
{}

Keypad::addKeypad_listener(Keypad_listener* listener){
    if (used < array_size){
        listeners[used] = listener;
        used += 1;
    }
}

