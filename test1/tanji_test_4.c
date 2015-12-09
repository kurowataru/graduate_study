#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/resource.h>
#define M 100
#define N 100
#define Q 10
#define P 1000
#define S 1
#define R1 2000000
#define R2 20000000
#define BUFSIZE 100
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
  }
}

int main(int argc,char **argv){
  int mat1[M][N],mat2[M][N],mat3[M][N],mat4[M][N],mat5[M][N];
  int i,j,k,l,m,n,pid[PNUM];
  int fd,rc,rc2[PNUM],sum,mode;
  char buff[BUFSIZE],buff2[PNUM][BUFSIZE];
  struct timeval s,e,rs,re;
  FILE *perfile;
  int sc_return;
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
      gettimeofday(&s,NULL);
      int pid = getpid();
      sc_return = syscall(323,&pid);
      printf("calcpid:%d start\n",pid);
      /*if(mode){
        char buff[20];  
        sprintf(buff,"%d",pid);
        char command[50] = "ionice -c 1 -n 0 -p ";
        strcat(command, buff);
        int state = system(command);
        printf("%s\n",command);
      }*/
      for(l=0;l<Q;l++){
        switch(l){
          case 0:
            fd = open("tempfile1_0.txt",O_RDONLY);
            break;
          case 1:
            fd = open("tempfile1_1.txt",O_RDONLY);
            break;
          case 2:
            fd = open("tempfile1_2.txt",O_RDONLY);
            break;
          case 3:
            fd = open("tempfile1_3.txt",O_RDONLY);
            break;
          case 4:
            fd = open("tempfile1_4.txt",O_RDONLY);
            break;
          case 5:
            fd = open("tempfile1_5.txt",O_RDONLY);
            break;
          case 6:
            fd = open("tempfile1_6.txt",O_RDONLY);
            break;
          case 7:
            fd = open("tempfile1_7.txt",O_RDONLY);
            break;
          case 8:
            fd = open("tempfile1_8.txt",O_RDONLY);
            break;
          case 9:
            fd = open("tempfile1_9.txt",O_RDONLY);
            break;
          default:
            break;
        }
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

        gettimeofday(&e,NULL);
        fprintf(perfile,"%lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);
        fflush(perfile);
        close(fd);
        printf("%d\n",l+1);
      }
      gettimeofday(&e,NULL);

      printf("user time = %lf\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

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

