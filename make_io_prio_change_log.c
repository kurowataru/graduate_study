#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#define ARRAYSIZE 1000

int main(int argc,char **argv){
  int pid_log[ARRAYSIZE];
  unsigned long cputime_log[ARRAYSIZE];
  int flag_log[ARRAYSIZE];
  int array_index;
  FILE *fd;
  int tmp;
  int i;

  fd = fopen(argv[1],"w");
  
  tmp = syscall(324,pid_log,cputime_log,flag_log,&array_index);

  for(i = 0;i < array_index;i++){
    fprintf(fd,"pid = %d prio changed to flag %d,cputime = %ld\n",pid_log[i],flag_log[i],cputime_log[i]);
  }
  fclose(fd);

  return 0;
}
