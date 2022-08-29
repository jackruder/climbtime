
enum tmrPhase { // phases of a interval workout
  TMRPREP,
  TMRHI,
  TMRLOW,
  TMRREPREST,
  TMRSETREST,
  TMRCOOL,
  TMRPAUSE
};

struct tmrTemplate { //timer settings
  int sets;
  int reps;
  unsigned long setRest;
  bool hiFirst;
  unsigned long hiLength;
  unsigned long lowLength;
  unsigned long repRest;
  unsigned long prepare;
  unsigned long cool;
}; 


struct tmrProg {
  int set; // the current set, 0 for preparation, sets+1 for cool
  int rep; // the current rep, rep+1 for set rest;

};

struct pauseState { 
  unsigned long elapsed;
  unsigned long phaseElapsed;
  enum tmrPhase intPhase;
  unsigned long timeLeft;
};

unsigned long doIntTimer(unsigned long *start, unsigned long *phaseStart, struct tmrTemplate *intTimer, struct tmrProg *intProgress, enum tmrPhase *intPhase, bool *sufferingover, int *pause, struct pauseState *pState);



