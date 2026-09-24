#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main (int argc, char *argv[])
{

   int clock;
   clock = uptime();
   //"Up" in Spanish: Arriba
   printf("Arriba %d clock ticks \n", clock);

   exit(0);

}
