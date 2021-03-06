#include "Light.h"

Light::Light( ) {
  Serial.println( "Light::Light" );
  pinMode( this->_buttonBackLightPin, OUTPUT );
  pinMode( this->_backLightPin, OUTPUT );
  pinMode( this->_redPin, OUTPUT );
  pinMode( this->_greenPin, OUTPUT );
  pinMode( this->_bluePin, OUTPUT );
  pinMode( this->_statusPin, OUTPUT );
  // this pullup to be removed?
  pinMode( this->_buttonPin, INPUT_PULLUP );

  this->_backLightCurrent = 255;
  this->_buttonBackLightCurrent = 255;
  this->_redCurrent = 0;
  this->_greenCurrent = 0;
  this->_blueCurrent = 128;

  WriteOutput( );
}

void Light::SwitchOn( ) {
  Serial.println("Light::SwitchOn switching lights on");
  this->_backLightCurrent = 255;
  this->_buttonBackLightCurrent = 255;
  this->_redCurrent = 255;
  this->_greenCurrent = 255;
  this->_blueCurrent = 255;

  // first lastupdate will be in the future to enable smooth delay
  this->_timeOfLastUpdate = millis( ) + this->_delayBeforeDimming;
}

void Light::Update( ) {
  unsigned long currentMillis = millis();
/*
  Serial.print( "Active: " );
  Serial.print( Active( ) );
  Serial.print( " currentMillis: " );
  Serial.print( currentMillis );
  Serial.print( " lastUpdate: " );
  Serial.println( this->_timeOfLastUpdate );
*/
  if( Active( ) &&
    ((unsigned long)(currentMillis - this->_timeOfLastUpdate ) >= this->_updateDelay ) ) {
    if( this->_backLightCurrent > this->_backLightNormal ) this->_backLightCurrent --;
    else if( this->_backLightCurrent < this->_backLightNormal ) this->_backLightCurrent ++;
    if( this->_buttonBackLightCurrent > this->_buttonBackLightNormal ) this->_buttonBackLightCurrent --;
    else if( this->_buttonBackLightCurrent < this->_buttonBackLightNormal ) this->_buttonBackLightCurrent ++;
    if( this->_redCurrent > this->_redNormal ) this->_redCurrent --;
    else if( this->_redCurrent < this->_redNormal ) this->_redCurrent ++;
    if( this->_greenCurrent > this->_greenNormal) this->_greenCurrent --;
    else if( this->_greenCurrent < this->_greenNormal) this->_greenCurrent ++;
    if( this->_blueCurrent > this->_blueNormal) this->_blueCurrent --;
    else if( this->_blueCurrent < this->_blueNormal) this->_blueCurrent ++;
    
    this->_timeOfLastUpdate = millis( );
    WriteOutput( );
  }
}

bool Light::Active( ) {
//  Serial.println("Light::Active checking if light is alerady active");
/* Serial.print( "backlight: " );
Serial.println( this->_backLightCurrent );
Serial.print( "red: " );
Serial.println( this->_redCurrent );
Serial.print( "green: " );
Serial.println( this->_greenCurrent );
Serial.print( "blue: " );
Serial.println( this->_blueCurrent ); */

  if( _backLightCurrent != this->_backLightNormal ||
      _buttonBackLightCurrent != this->_buttonBackLightNormal ||
      _redCurrent != this->_redNormal ||
      _greenCurrent != this->_greenNormal ||
      _blueCurrent != this->_blueNormal )
        return true;
  else
    return false;
}

void Light::WriteOutput( ) {
  Serial.print( "backlight: " );
  Serial.print( this->_backLightCurrent );
  Serial.print( " red: " );
  Serial.print( this->_redCurrent );
  Serial.print( " blue: " );
  Serial.print( this->_blueCurrent );
  Serial.print( " green: " );
  Serial.println( this->_greenCurrent );
  
  analogWrite( this->_backLightPin, this->_backLightCurrent );
  analogWrite( this->_buttonBackLightPin, this->_buttonBackLightCurrent );
  analogWrite( this->_redPin, this->_redCurrent );
  analogWrite( this->_bluePin, this->_blueCurrent );
  analogWrite( this->_greenPin, this->_greenCurrent );
  analogWrite( this->_statusPin, Active( ) );
}

bool Light::ButtonPressed( ) {
  // with INPUT_PULLUP value is false when button is pressed
  if(! digitalRead( _buttonPin ) )
    return true;
  else return false;
}

