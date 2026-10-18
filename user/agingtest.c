#include "kernel/types.h"
#include "user/user.h"

#define WORK 100000000UL   // tune so one job takes a few seconds
#define MAXKIDS 8

void
work(void)
{
  volatile unsigned long i;
  for(i = 0; i < WORK; i++)
    ;
}

int
main(int argc, char *argv[])
{
  int prios[MAXKIDS] = {0, 10, 10, 10};
  int n = 4;
  int i, pid, arrival, first;

  if(argc > 1){
    n = argc - 1;
    if(n > MAXKIDS)
      n = MAXKIDS;
    for(i = 0; i < n; i++)
      prios[i] = atoi(argv[i + 1]);
  }

  setpriority(49);   // parent outranks children while it forks them

  for(i = 0; i < n; i++){
    arrival = uptime();
    pid = fork();
    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }
    if(pid == 0){
      first = uptime();             // first instruction = first time scheduled
      setpriority(prios[i]);
      work();
      printf("prio %d: response %d, turnaround %d\n",
             prios[i], first - arrival, uptime() - arrival);
      exit(0);
    }
  }
  for(i = 0; i < n; i++)
    wait(0);
  exit(0);
}
