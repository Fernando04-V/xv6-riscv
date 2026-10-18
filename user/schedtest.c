#include "kernel/types.h"
#include "user/user.h"

#define WORK 300000000UL // raise if jobs finish too fast, lower if too slow
#define MAXKIDS 8

void
work(void)
{

  volatile unsigned long i; // volatile so the loop isn't optimized away
  for(i = 0; i < WORK; i++)
    ;
}

int
main(int argc, char *argv[])
{
 int prios[MAXKIDS] = {0, 5, 10};
 int n = 3;
 int i, pid;
 int start;
 char *args[] = {"ps", 0};
 if(argc > 1){
   n = argc - 1;
   if(n > MAXKIDS)
      n = MAXKIDS;
    for(i = 0; i < n; i++)
      prios[i] = atoi(argv[i + 1]);
    }

    start = uptime();
    setpriority(49); // parent outranks the children while it forks them

    for(i = 0; i < n; i++){
      pid = fork();
      if(pid < 0){
      printf("fork failed\n");
      exit(1);
     }

     if(pid == 0){
      setpriority(prios[i]);
      work();
      printf("priority %d finished at tick %d\n", prios[i], uptime() - start);
      exit(0);
     }
  }

  // Let the children start spinning, then show the process table.
  // ps inherits priority 49, so it gets the CPU even under strict priority.
  pause(20);
  pid = fork();
  if(pid == 0){
   exec("ps", args);
   printf("exec ps failed\n");
   exit(1);
  }
  for(i = 0; i < n + 1; i++)
   wait(0);
  exit(0);
}
