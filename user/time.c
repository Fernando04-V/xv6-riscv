#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

int
main (int argc, char *argv[])
{

  if (argc < 2){
    printf("None\n");
    exit(1);
  }


  int start = uptime();

  int pid = fork();

  if(pid == 0){
    exec(argv[1], &argv[1]);
    exit(1);
  }


  int status;
  struct rusage ru;

  wait2(&status, &ru);

  int end = uptime();
  
  int cput = ru.cputime;
  int time_elapsed = end - start;
  int cpup = (cput / time_elapsed) * 100;


  printf("Elpased time: %d ticks | CPU time: %d | %d CPU\n", time_elapsed, cput, cpup);



}
