#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);



  printf("pid\tstate\t\tsize\tppid\tname\tpriority\tage\n");
  for (i=0; i<nprocs; i++) {

     int age = 0;
     if(uproc[i].state == RUNNABLE){
     age = uptime() - (int)uproc[i].readytime;
    }

    state = states[uproc[i].state];
    printf("%d\t%s\t%ld\t%d\t%s\t%d\t%d\n", uproc[i].pid, state,
                   uproc[i].size, uproc[i].ppid, uproc[i].name, uproc[i].priority, age);
  }

  exit(0);
}
