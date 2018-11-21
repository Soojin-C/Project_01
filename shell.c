#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


char ** parse_args(char * line){
  char ** argv = malloc(6 *sizeof(char *));
  for(int i = 0; i < 6; i++){
    argv[i] = strsep(&line, " ");
  }
  return argv;
}


int main(int argc, char * argv[]){
  printf("arg:%s, %d\n", argv[1], argc);
  
  if(argc > 1){
    char ** tmp_args = parse_args(argv[1]);
    int f;
  f = fork();
  printf("fork: %d; %d\n", f, getpid());
  if(f == 0){ //child; running process
    char * name_prg = tmp_args[0];
    printf("name of prog: %s", name_prg);
    char * path = "/bin/";
       printf("path: %s", path);
    execvp(strcpy(path, name_prg), tmp_args);
  }
  }
  
}
