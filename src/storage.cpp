#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <storage.h>
#endif

#ifndef _EEPROM_H_
#define _EEPROM_H_
#include <EEPROM.h>
#endif /* ifndef _EEPROM_H_ */

#ifndef _INT_TIMER_H_
#define _INT_TIMER_H_
#include <int_timer.h>
#endif /* ifndef _INT_TIMER_H_*/

const unsigned int eepromSize = EEPROM.length();

/*
void storeDefaults(int addr_begin) {
  for (int i = 0; i < numDefaultTimers; i++) {
    int address = addr_begin + i * sizeof(tmrTemplate);
    EEPROM.put(address, tmrDefaults[i]);
  }
}
*/

tmrTemplate getTemplate(int index) {
  struct tmrTemplate data;
  EEPROM.get(index * sizeof(tmrTemplate), data);
  return data;
}

void storeTemplate(int index, struct tmrTemplate data) {
  EEPROM.put(index * sizeof(tmrTemplate), data);
} // TODO CHECK MEMORY BOUNDS
