#ifndef _INT_TIMER_H_
#define _INT_TIMER_H_
#include <int_timer.h>
#endif

#ifndef _ARDUINO_H_
#define _ARDUINO_H_
#include <Arduino.h>
#endif /* ifndef _ARDUINO_H_ */

struct tmrTemplate intervalTimer(int numSets, int numReps, float setRest,
                                 bool hiFirst, float hiLength, float lowLength,
                                 float repRest, float prepare, float cool) {
  struct tmrTemplate tmp {
    numSets, numReps, (unsigned long)(1000. * setRest), hiFirst,
        (unsigned long)(1000. * hiLength), (unsigned long)(1000. * lowLength),
        (unsigned long)(1000. * repRest), (unsigned long)(1000. * prepare),
        (unsigned long)(1000. * cool)
  };
  return tmp;
}

unsigned long doIntTimer(struct tmrTemplate *intTimer,
                         struct tmrProg *intProgress, enum tmrPhase *intPhase,
                         bool *sufferingover, int *pause,
                         struct pauseState *pState) {
  static unsigned long start = millis();
  static unsigned long phaseStart = start;
  unsigned long elapsed = millis() - start;
  unsigned long phaseElapsed = millis() - phaseStart;

  if (*pause == 1) { // pause
    *pState = {elapsed, phaseElapsed, *intPhase};
    *intPhase = TMRPAUSE;
    *pause = 3;
  } else if (*pause == 2) { // resume
    start = millis() - pState->elapsed;
    phaseStart = millis() - pState->phaseElapsed;
    elapsed = pState->elapsed;
    phaseElapsed = pState->phaseElapsed;
    *intPhase = pState->intPhase;
    *pause = 0;
  }

  switch (*intPhase) {
  case TMRPREP:
    if (elapsed < intTimer->prepare) {    // in prep phase
      return intTimer->prepare - elapsed; // show time to start
    } else {

      if (intTimer->hiFirst) { // start exercise
        *intPhase = TMRHI;
      } else {
        *intPhase = TMRLOW;
      }

      intProgress->set = 1;
      intProgress->rep = 1;

      // play a ding sound
    }
    break;

  case TMRHI:
    if (phaseElapsed < intTimer->hiLength) { // in exercise
      return intTimer->hiLength - phaseElapsed;
    } else { // switch phases

      if (intTimer->hiFirst) { // we must switch to low then
        *intPhase = TMRLOW;

      } else { // we must have come from LOW, end this rep
        if (intProgress->rep == intTimer->reps) { // this was the last rep in
                                                  // set
          if (intProgress->set ==
              intTimer->sets) { // this was the last rep of the last set
            *intPhase = TMRCOOL;
            intProgress->rep = 0;
            intProgress->set++;

          } else { // last rep of not the last set, move to set rest
            *intPhase = TMRSETREST;
          }

        } else { // mid-set, so rest
          *intPhase = TMRREPREST;
        }
      }
    }

    break;
  case TMRLOW:
    if (phaseElapsed < intTimer->lowLength) { // in exercise
      return intTimer->lowLength - phaseElapsed;
    } else { // switch phases

      if (!intTimer->hiFirst) { // we must switch to high then
        *intPhase = TMRHI;

      } else { // we must have come from LOW, end this rep
        if (intProgress->rep == intTimer->reps) { // this was the last rep in
                                                  // set
          if (intProgress->set ==
              intTimer->sets) { // this was the last rep of the last set
            *intPhase = TMRCOOL;
            intProgress->rep = 0;
            intProgress->set++;

          } else { // last rep of not the last set, move to set rest
            *intPhase = TMRSETREST;
          }

        } else { // mid-set, so rest
          *intPhase = TMRREPREST;
        }
      }
    }
    break;

  case TMRREPREST:
    if (phaseElapsed < intTimer->repRest) {
      return intTimer->repRest - phaseElapsed;
    } else {
      // SHOULD NEVER BE HERE ON THE LAST REP OF SET
      if (intProgress->rep == intTimer->reps) {
        // BAD
        return 0xFFFFFFFF;
      }

      if (intTimer->hiFirst) { // start exercise
        *intPhase = TMRHI;
      } else {
        *intPhase = TMRLOW;
      }

      intProgress->rep++;
    }
    break;
  case TMRSETREST:
    if (phaseElapsed < intTimer->setRest) {
      return intTimer->setRest - phaseElapsed;
    } else {
      // SHOULD NEVER BE HERE ON THE LAST SET
      if (intProgress->set == intTimer->sets) {
        // BAD
        return 0xFFFFFFFF;
      }

      if (intTimer->hiFirst) { // start exercise
        *intPhase = TMRHI;
      } else {
        *intPhase = TMRLOW;
      }

      intProgress->rep = 1;
      intProgress->set++;
    }
    break;
  case TMRCOOL:
    if (phaseElapsed < intTimer->cool) {
      return intTimer->cool - phaseElapsed;
    } else {
      *sufferingover = true;
    }

  case TMRPAUSE:
    break;
  }

  phaseStart = millis(); // restart start next phase timer
  return phaseStart; // TODO remove this statement, have each case handle return
}
