#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "keypad_listener.hpp"


///@file

/// \brief
/// Keypad ADT
/// \details
/// This class is an inheritance of rtos task.
/// It is responsible for polling the keypad and contains pointers to listeners that listen to the keypad
class Keypad : public rtos::task<>{
    enum state_t {WAIT};

private:
    static const int array_size = 2;
    int used = 0;
    state_t state = WAIT;
    hwlib::keypad< 16 > & keypad;
    rtos::timer timer;
    Keypad_listener *listeners[array_size];
    void main();

public:

    /// \brief
    /// Costructor for keypad
    /// \details
    /// This constructor initializes the keypad
    Keypad(hwlib::keypad< 16 > & keypad);

    /// \brief
    /// adds listeners
    /// \details
    /// This methods adds pointers of listerners to the array of listeners
    void addKeypad_listener(Keypad_listener *listener);
};

#endif //KEYPAD_H