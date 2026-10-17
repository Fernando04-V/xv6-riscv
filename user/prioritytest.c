#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;

  printf("initial priority: %d\n", getpriority());

  // Valid set
  printf("setpriority(10) returned %d\n", setpriority(10));
  printf("priority now: %d\n", getpriority());

  // Invalid sets should fail and leave the priority unchanged
  printf("setpriority(-1) returned %d\n", setpriority(-1));
  printf("setpriority(50) returned %d\n", setpriority(50));
  printf("priority after invalid calls: %d (should still be 10)\n",
         getpriority());

  // Child should inherit the parent's priority
  pid = fork();
  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }
  if(pid == 0){
    printf("child: priority = %d (should be 10)\n", getpriority());
    pause(300);   // stay alive so you can run ps
    exit(0);
  }

  printf("parent: priority = %d, child pid = %d\n", getpriority(), pid);
  wait(0);
  exit(0);

}
