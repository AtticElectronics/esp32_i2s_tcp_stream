#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
public:
    Button(int pin);
    int checkState();

private:
    int _pin;
    int _buttonState;
    int _lastButtonState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
};

#endif
