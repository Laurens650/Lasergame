#ifndef KEYPAD_LISTENER_H
#define KEYPAD_LISTENER_H

class Keypad_listener{
public:
    Keypad_listener():
    {}
    virtual void buttonPressed(char buttonID) = 0;
};


#endif // KEYPAD_LISTENER_H