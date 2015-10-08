#include "light.h"

volatile int switchLightsOn = 0;
Light *mainlight;
Floor *floorlight;

void setup() {
  Serial.begin( 9600 );
  Serial.println( "Welcome to Octolight" );
  mainlight = new Light( );
  floorlight = new Floor( );
  // interrupt 0 equals to input pin 2 on uno and mini
  // see http://arduino.cc/en/Reference/attachInterrupt
  attachInterrupt( 0, lightsOn, CHANGE );

}

void loop() {
  if( switchLightsOn ) {
    switchLightsOn = 0;
    Serial.println("octolight main looper Switch lights on");
    mainlight->SwitchOn( );
    floorlight->SwitchOn( );
  }
  if( mainlight->Active( ) ) mainlight->Update( );
  if( floorlight->Active( ) ) floorlight->Update( );
}

void lightsOn( ) {
  // Don't print in ISR, just for debugging
  //  Serial.println( "octointerrupt" );
  switchLightsOn = 1;
}

