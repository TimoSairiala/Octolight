#ifndef light_h
#define light_h

#include "Arduino.h"

// Arduino mini has PWM output on pins
// 3, 5, 6, 9, 10 and 11
// status led in pin 13, maybe use it to indicate active status
// interrupt 0 is in pin 2

class Light {
  public:
    Light( );
    void SwitchOn( );
    void Update( );
    bool Active( );
    bool ButtonPressed( );
  private:
    void WriteOutput( );

    const static int _buttonPin = 2;
    const static int _backLightPin = 3;
    const static int _buttonBackLightPin = 5;
    const static int _statusPin = 13;

    const static int _backLightNormal = 0;
    const static int _buttonBackLightNormal = 255;

    int _buttonBackLightCurrent;
    int _backLightCurrent;

    unsigned long _timeOfLastUpdate;
    const static long _updateDelay = 50;
    const static long _delayBeforeDimming = 10000;
};

#endif

