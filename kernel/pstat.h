#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "types.h"

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct rusage {
   uint cputime;
};


struct pstat {
  int pid;
  enum procstate state;
  uint64 size;
  int ppid;
  char name[16];
};


#endif
