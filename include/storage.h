#ifndef _EEPROM_H_
#define _EEPROM_H_
#include <EEPROM.h>
#endif /* ifndef _EEPROM_H_ */

#ifndef _INT_TIMER_H_
#define _INT_TIMER_H_
#include <int_timer.h>
#endif /* ifndef _INT_TIMER_H_*/

// 4KB storage
const unsigned int eepromSize;
const unsigned int tmrTemp tmrTemplateSize;
const unsigned int numDefaultTimers = 4;

tmrTemplate getTemplate(int index);
void storeTemplate(int index, struct tmrTemplate data);

struct tmrTemplate defaultIntTimer1 { // 7 on 3 off 3 min rest
  7,                                  // Num Sets
      7,                              // Num Reps
      180000ul,                       // Rest between sets
      false,                          // Start with high intensity
      7000ul,                         // Hi Work
      1000ul,                         // Low work
      2000ul,                         // Rep rest
      10000ul,                        // Prepare time
      50000ul                         // cooldown time
};

struct tmrTemplate defaultIntTimer2 { // 7 : 53 eric horst
  5,                                  // Num Sets
      1,                              // Num Reps
      50000ul,                        // Rest between sets
      false,                          // Start with high intensity
      7000ul,                         // Hi Work
      3000ul,                         // Low work
      0ul,                            // Rep rest
      20000ul,                        // Prepare time
      50000ul                         // cooldown time
};

struct tmrTemplate defaultIntTimer3 { // EMOM 15 mins
  15,                                 // Num Sets
      1,                              // Num Reps
      0ul,                            // Rest between sets
      false,                          // Start with high intensity
      60000ul,                        // Hi Work
      0ul,                            // Low work
      0ul,                            // Rep rest
      20000ul,                        // Prepare time
      50000ul                         // cooldown time
};

struct tmrTemplate defaultIntTimer4 { // MAX HANGS
  6,                                  // Num Sets
      1,                              // Num Reps
      149000ul,                       // Rest between sets
      false,                          // Start with high intensity
      60000ul,                        // Hi Work
      1000ul,                         // Low work
      0ul,                            // Rep rest
      20000ul,                        // Prepare time
      50000ul                         // cooldown time
};
struct tmrTemplate tmrDefaults[numDefaultTimers] = {
    defaultIntTimer1, defaultIntTimer2, defaultIntTimer3, defaultIntTimer4};
