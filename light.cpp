#include "Light.h"

Light::Light( ) {
  Serial.println( "Light::Light" );
  pinMode( this->_buttonBackLightPin, OUTPUT );
  pinMode( this->_backLightPin, OUTPUT );
  pinMode( this->_statusPin, OUTPUT );
  pinMode( this->_buttonPin, INPUT_PULLUP );

  this->_backLightCurrent = 255;
  this->_buttonBackLightCurrent = 255;

  WriteOutput( );
}

void Light::SwitchOn( ) {
  Serial.println("Light::SwitchOn switching lights on");
  this->_backLightCurrent = 255;
  this->_buttonBackLightCurrent = 255;

  // first lastupdate will be in the future to enable smooth delay
  this->_timeOfLastUpdate = millis( ) + this->_delayBeforeDimming;
}

void Light::Update( ) {
  unsigned long currentMillis = millis();

/*  Serial.print( "Active: " );
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
    
    this->_timeOfLastUpdate = millis( );
    WriteOutput( );
  }
}

bool Light::Active( ) {
//  Serial.println("Light::Active checking if light is alerady active");
/* Serial.print( "backlight: " );
Serial.println( this->_backLightCurrent ); */

  if( _backLightCurrent != this->_backLightNormal ||
      _buttonBackLightCurrent != this->_buttonBackLightNormal )
        return true;
  else
    return false;
}

void Light::WriteOutput( ) {
/*  Serial.print( "backlight: " );
  Serial.print( this->_backLightCurrent );
  */
  analogWrite( this->_backLightPin, this->_backLightCurrent );
  analogWrite( this->_buttonBackLightPin, this->_buttonBackLightCurrent );
  analogWrite( this->_statusPin, Active( ) );
}

bool Light::ButtonPressed( ) {
  // with INPUT_PULLUP value is false when button is pressed
  if(! digitalRead( _buttonPin ) )
    return true;
  else return false;
}

