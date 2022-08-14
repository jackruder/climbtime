//#ifndef _BUTTON_IO_H
//#define _BUTTON_IO_H 
#include <button_io.h>
//#endif /* ifndef _BUTTON_IO_H */

#ifndef _PINDEF_H_
#define _PINDEF_H_
#include <pindef.h>
#endif /* ifndef _PINDEF_H_ */

void read_button_states(struct buttonStates *s) {
  s->g = digitalRead(buttonG);
  s->y = digitalRead(buttonY);
  s->r = digitalRead(buttonR);
}
