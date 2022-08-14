#ifndef _RGBMATRIXPANEL_H_
#define _RGBMATRIXPANEL_H_ 
#include "RGBmatrixPanel.h"
#endif /* ifndef  */

#ifndef _INT_TIMER_H_
#define _INT_TIMER_H_
#include <int_timer.h>
#endif

void draw_display(bool new_envr, int dclock, int oldclock, struct tmrTemplate tmr, struct tmrProg prog, enum tmrPhase intPhase, float temperature, float humidity, RGBmatrixPanel matrix);
void draw_envr(float temperature, float humidity, RGBmatrixPanel matrix);
void draw_tmr(struct tmrTemplate tmr, struct tmrProg prog, enum tmrPhase intPhase, int dclock, RGBmatrixPanel matrix);
