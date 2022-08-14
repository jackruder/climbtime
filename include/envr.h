#ifndef _PINDEF_H_
#define _PINDEF_H_
#include <pindef.h>
#endif /* ifndef _PINDEF_H_ */

#ifndef _DHT_NONBLOCKING_H_
#define _DHT_NONBLOCKING_H_
#include <dht_nonblocking.h>
#endif

#define DHT_SENSOR_TYPE DHT_TYPE_22

const unsigned long envrReadDelay = 2000ul;
/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
bool measure_environment( float *temperature, float *humidity, DHT_nonblocking sensor);
