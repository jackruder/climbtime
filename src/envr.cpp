#include <envr.h> 

#ifndef _ARDUINO_H_
#define _ARDUINO_H_ 
#include <Arduino.h>
#endif /* ifndef _ARDUINO_H_ */
/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
bool measure_environment( float *temperature, float *humidity, DHT_nonblocking sensor)
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > envrReadDelay)
  {
    if( sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

