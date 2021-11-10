#ifndef KEYPAD_LISTENER_H
#define KEYPAD_LISTENER_H
///@file

/// \brief
/// keypad listener
/// \details
/// This class act as a listener for the keypad
class Keypad_listener{
public:
    Keypad_listener():
    {}
    virtual void buttonPressed(char buttonID) = 0;
};


#endif // KEYPAD_LISTENER_H