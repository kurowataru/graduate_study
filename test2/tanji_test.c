#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/resource.h>
#define M 100
#define N 100
#define Q 10
#define P 10000
#define S 10
#define R1 200
#define R2 2000
#define BUFSIZE 1000000
#define PNUM 7 
void readfile(char *filename,char *buff2,FILE *perfile){
  int p,q,fd2,rc2;
  struct timeval s,e;
  for(q=0;q<S;q++){
    gettimeofday(&s,NULL);
    fd2 = open(filename,O_RDONLY);
    for(p=0;p<R2;p++){
      rc2 = read(fd2,buff2,BUFSIZE);
    }
    close(fd2);
    gettimeofday(&e,NULL);
    fprintf(perfile,"rt = %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);
    fflush(perfile);
    system("sysctl -w vm.drop_caches=3");
  }
}

int main(int argc,char **argv){
  int mat1[M][N],mat2[M][N],mat3[M][N],mat4[M][N],mat5[M][N];
  int i,j,k,l,m,n,pid[PNUM];
  int fd,rc,rc2[PNUM],sum,mode;
  char buff[BUFSIZE],buff2[PNUM][BUFSIZE];
  struct timeval s,e,rs,re;
  FILE *perfile;
  perfile = fopen(argv[2],"w");
  mode = atoi(argv[1]);
  for(i=0;i<M;i++)
    for(j=0;j<N;j++){
      mat1[i][j] = i+j;
      mat2[i][j] = i-j;
      mat3[i][j] = i*j;
      mat4[i][j] = (i+j)*2;
    }

  for(m=0;m<PNUM && (pid[m] = fork())>0;m++);

  if(m==PNUM){
    for(  m = 0 ; m < PNUM ; m++ ){
      wait();
    }
  } else if( pid[m] == 0){   
    if(m==0){
      int pid = getpid();
      printf("calcpid:%d start\n",pid);
      if(mode){
        char buff[20];  
        sprintf(buff,"%d",pid);
        char command[50] = "ionice -c 1 -n 0 -p ";
        strcat(command, buff);
        int state = system(command);
        printf("%s\n",command);
      }
      fd = open("tempfile1.txt",O_RDONLY);
      for(l=0;l<Q;l++){
        gettimeofday(&s,NULL);
        for(n=0;n<R1;n++) {
          rc = read(fd,buff,BUFSIZE);
        }
        for(n=0;n<P;n++){
          for(i=0;i<M;i++){
            for(j=0;j<N;j++){
              mat5[i][j]=0;
              for(k=0;k<N;k++) mat5[i][j] += mat1[i][k] * mat2[k][j];
            }
          }
        }

        //if((l+1)%10==0){
        gettimeofday(&e,NULL);
        fprintf(perfile,"%lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);
        fflush(perfile);
        close(fd);
        printf("%d\n",l+1);
        system("sysctl -w vm.drop_caches=3");
        fd = open("tempfile1.txt",O_RDONLY);
        //}
      }
      gettimeofday(&e,NULL);

      printf("user time = %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);


      close(fd);
      fclose(perfile);
      printf("calcpid:%d exit\n",pid);
      exit(0);
    }else if(m==1){
      int pid = getpid();
      printf("pid:%d start\n",pid);
      readfile("tempfile2.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);        
      exit(0);
    }else if(m==2){
      int pid = getpid();
      printf("pid:%d start\n",pid);
      readfile("tempfile3.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);        
      exit(0);
    }else if(m==3){
      int pid = getpid();
      printf("pid:%d start\n",pid);
      readfile("tempfile4.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);        
      exit(0);
    }else if(m==4){
      int pid = getpid();
      printf("pid:%d start\n",pid);                
      readfile("tempfile5.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);        
      exit(0);
    }else if(m==5){
      int pid = getpid();
      printf("pid:%d start\n",pid);
      readfile("tempfile6.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);
      exit(0);
    }else if(m==6){
      int pid = getpid();
      printf("pid:%d start\n",pid);
      readfile("tempfile7.txt",buff2[m],perfile);
      printf("pid:%d exit\n",pid);        
      exit(0);
    }       

  }

  return 0;
}

