#ifndef KEYPAD_H
#define KEYPAD_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"

/// this class makes sure the keypad works
class Keypad : public rtos::task<>{
    enum state_t {WAIT};

    private:
        const int array_size = 2;
        int used = 0;
        state_t state = WAIT;
        hwlib::keypad< 16 > & keypad;
        rtos::timer timer;
        Keypad_listener *listeners[array_size];
        void main();

    public:
        Keypad(hwlib::keypad< 16 > & keypad);
		/// \details
		/// this function adds the keypad_listener
        void addKeypad_listener(Keypad_listener *listener);
};

#define //KEYPAD_H