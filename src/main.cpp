#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <matrix.h>
#endif /* ifndef _MATRIX_H_ */

#ifndef _INT_TIMER_H_
#define _INT_TIMER_H_
#include <int_timer.h>
#endif

#ifndef _BUTTON_IO_H
#define _BUTTON_IO_H
#include <button_io.h>
#endif /* ifndef _BUTTON_IO_H */

#ifndef _PINDEF_H_
#define _PINDEF_H_
#include <pindef.h>
#endif /* ifndef _PINDEF_H_ */

#ifndef _ARDUINO_H_
#define _ARDUINO_H_
#include <Arduino.h>
#endif /* ifndef _ARDUINO_H_ */

#ifndef _ENVR_H_
#define _ENVR_H_
#include <envr.h>
#endif /* ifndef _ENVR_H_ */
/* Uncomment according to your sensortype. */

float temperature;
float humidity;
int dclock;
int oldclock;

// Timer Control
enum tmrPhase intPhase;
struct tmrProg prog;
struct tmrTemplate tmr;
int pause;
unsigned long pausedFor;
struct pauseState pState;
unsigned long tmrMilli;

bool suffer;
// Button IO
struct buttonStates bState;

RGBmatrixPanel matrix(matA, matB, matC, matD, matCLK, matLAT, matOE, false, 64);
DHT_nonblocking dht_sensor(dhtSensorPin, DHT_SENSOR_TYPE);

/*
 * Initialize the serial port.
 */
void setup() {
  tmr = defaultIntTimer1;
  dclock = 0;
  Serial.begin(9600);
  matrix.begin();
  while (!dht_sensor.measure(&temperature, &humidity))
    ; // init readings

  pinMode(buttonG, INPUT_PULLUP);
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(buttonR, INPUT_PULLUP);
}

/*
 * Main program loop.
 */
void loop() {

  read_button_states(&bState);
  bool envr_update = measure_environment(&temperature, &humidity, dht_sensor);

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */

  draw_display(envr_update, dclock, oldclock, tmr, prog, intPhase, temperature,
               humidity, matrix);

  if (suffer) { // run the interval timer clock
    oldclock = dclock;
    tmrMilli = doIntTimer(&tmr, &prog, &intPhase, &suffer, &pause, &pState);
    if (pause == 0) { // running
      if (bState.y == LOW) {
        pause = 1; // pause the time
      }
      dclock = (int)(tmrMilli / 1000);
    }

    if (pause == 3) { // paused
      if (bState.g == LOW) {
        pause = 2; // resume the timer
      }
      pausedFor = tmrMilli;
    }

  } else { // check for start
    if (bState.g == LOW) {
      suffer = true;
      intPhase = TMRPREP;
    }
  }
}
