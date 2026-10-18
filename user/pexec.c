#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int prio;

  if(argc < 3){
    fprintf(2, "usage: pexec priority command [args...]\n");
    exit(1);
  }

  prio = atoi(argv[1]);
  if(setpriority(prio) < 0){
    fprintf(2, "pexec: invalid priority %d (must be 0-49)\n", prio);
    exit(1);
  }

  exec(argv[2], &argv[2]);
  fprintf(2, "pexec: exec %s failed\n", argv[2]);
  exit(1);
}
