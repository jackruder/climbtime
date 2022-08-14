#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <matrix.h>
#endif

void draw_display(bool new_envr, int dclock, int oldclock, struct tmrTemplate tmr, struct tmrProg prog, enum tmrPhase intPhase, float temperature, float humidity, RGBmatrixPanel matrix) {

    if (dclock != oldclock) {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      draw_tmr(tmr, prog, intPhase, dclock, matrix);
      draw_envr(temperature, humidity, matrix);
    
    }  else {
      if (new_envr) {
      	draw_envr(temperature, humidity, matrix);
        new_envr = false;
      }
    }
}



void draw_envr(float temperature, float humidity, RGBmatrixPanel matrix) {
      matrix.setTextSize(1);     // size 1 == 8 pixels high
      matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
      matrix.setTextColor(matrix.Color333(2,2,7));
      matrix.setCursor(16, 1);
      matrix.print( (int)temperature);
      matrix.print("C, ");
      matrix.print((int)humidity);
      matrix.println( "%" );
}

void draw_tmr(struct tmrTemplate tmr, struct tmrProg prog, enum tmrPhase intPhase, int dclock, RGBmatrixPanel matrix) {
  matrix.setCursor(2,12);
  switch (intPhase) {    
    case TMRPREP:
      matrix.setTextColor(matrix.Color333(7,2,7));
      break;
    case TMRHI:
      matrix.setTextColor(matrix.Color333(1,7,1));
      break;
    case TMRLOW:
      matrix.setTextColor(matrix.Color333(7,4,1));
      break;
    case TMRREPREST:
      matrix.setTextColor(matrix.Color333(7,1,1));
      break;
      
    case TMRSETREST:
      matrix.setTextColor(matrix.Color333(7,7,1));
      break;
   
    case TMRCOOL:
      matrix.setTextColor(matrix.Color333(0,7,7));
      break;
      
    case TMRPAUSE:
      matrix.setTextColor(matrix.Color333(7,7,7));
      break;
  }
      
      matrix.print(dclock);
      matrix.setCursor(22,12);
      matrix.setTextColor(matrix.Color333(7,7,7));
      matrix.print(prog.rep);
      matrix.print("/");
      matrix.print(tmr.reps); 
      matrix.print("-");
      matrix.print(prog.set);
      matrix.print("/"); 
      matrix.print(tmr.sets);
}

