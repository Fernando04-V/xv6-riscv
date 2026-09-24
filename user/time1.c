#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main (int argc, char *argv[])
{

  //Base case if the user does not enter a command line
  if(argc < 2){
     printf("Please enter a command. Now exiting\n");
     exit(1);
   }


  int start = uptime();


  //Creating the parent and child process
  int pid = fork();


  if(pid == 0){
    exec(argv[1], &argv[1]); //Passing on the assembeled arguements to pass to exec & executing this in the child. Doing argv[0] and argv[1] 
    exit(1);
  }

  wait(0);

  int end = uptime();

  printf("start: %d\n", start);
  printf("end: %d\n", end);
  printf("Elapsed Time: %d\n", end - start);



   exit(0);

}
