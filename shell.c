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
  if(argc > 1){
    char ** tmp_args = parse_args(argv[1]);
  }
  int f;
  f = fork();
  if(f == 0){ //child; running process
    execvp
  }
}
