#include "light.h"

volatile int switchLightsOn = 0;
Light *oktovalo;

void setup() {
  Serial.begin( 9600 );
  Serial.println( "Welcome to Oktovalo" );
  oktovalo = new Light( );
  switchLightsOn = 1;
  // interrupt 0 equals to input pin 2 on uno and mini
  // see http://arduino.cc/en/Reference/attachInterrupt
  attachInterrupt( 0, lightsOn, CHANGE );

}

void loop() {
  if( switchLightsOn ) {
    switchLightsOn = 0;
    Serial.println("oktovalo main looper Switch lights on");
    oktovalo->SwitchOn( );
  }
  if( oktovalo->Active( ) ) {
    oktovalo->Update( );
  }
}

void lightsOn( ) {
  // Don't print in ISR, just for debugging
  // Serial.println( "octointerrupt" );
  switchLightsOn = 1;
}

