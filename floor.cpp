#include "Floor.h"

Floor::Floor( ) {
  Serial.println( "Floor::Floor" );
  pinMode( this->_redPin, OUTPUT );
  pinMode( this->_greenPin, OUTPUT );
  pinMode( this->_bluePin, OUTPUT );

  this->_redCurrent = 0;
  this->_greenCurrent = 0;
  this->_blueCurrent = 128;

  WriteOutput( );
}

void Floor::SwitchOn( ) {
  Serial.println("Floor::SwitchOn switching floor lights on");
  this->_redCurrent = 255;
  this->_greenCurrent = 255;
  this->_blueCurrent = 255;

  // first lastupdate will be in the future to enable smooth delay
  this->_timeOfLastUpdate = millis( ) + this->_delayBeforeDimming;
}

void Floor::Update( ) {
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

bool Floor::Active( ) {
//  Serial.println("Floor::Active checking if light is alerady active");
/* Serial.print( "red: " );
Serial.println( this->_redCurrent );
Serial.print( "green: " );
Serial.println( this->_greenCurrent );
Serial.print( "blue: " );
Serial.println( this->_blueCurrent ); */

  if( _redCurrent != this->_redNormal ||
      _greenCurrent != this->_greenNormal ||
      _blueCurrent != this->_blueNormal )
        return true;
  else
    return false;
}

void Floor::WriteOutput( ) {
/* Serial.print( " red: " );
  Serial.print( this->_redCurrent );
  Serial.print( " blue: " );
  Serial.print( this->_blueCurrent );
  Serial.print( " green: " );
  Serial.println( this->_greenCurrent );
  */
  analogWrite( this->_redPin, this->_redCurrent );
  analogWrite( this->_bluePin, this->_blueCurrent );
  analogWrite( this->_greenPin, this->_greenCurrent );
}


