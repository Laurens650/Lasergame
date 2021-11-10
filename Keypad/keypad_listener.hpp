#ifndef KEYPAD_LISTENER_H
#define KEYPAD_LISTENER_H
///@file

/// this is the abstract class of a keypad listener
class Keypad_listener{
public:
    Keypad_listener():
    {}
    virtual void buttonPressed(char buttonID) = 0;
};


#endif // KEYPAD_LISTENER_H