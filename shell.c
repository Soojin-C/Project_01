#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//clean out line by getting rid of bad spaces
char * spaces_clean(char * line){
  int i = 0;
  if(line[i] == ' '){
    while(line[i] == ' '){
      i++;
    }
  }
  return &line[i];
}

//counting number of arguments in a line given a delimiter
int num_args(char * line, char * delim){
  char * line2 = malloc(strlen(line) * sizeof(char*));
  strcpy(line2, line);
  int i = 0;
  while(line2){
    strsep(&line2, delim);
    i++;
  }
  return i;
}


char ** parse_args(char * line, char * delim){
  char ** tmp_argv = malloc(100 *sizeof(char *));
  int i = 0;
  while(line){
    tmp_argv[i] = strsep(&line, delim);
    tmp_argv[i] = spaces_clean(tmp_argv[i]);
    i++;
  }
  tmp_argv[i] = NULL;
  return tmp_argv;
}

void fork_launch(char ** args){
  int f;
  int * status;

  f = fork();

  if(f == 0){ //child; running process
    char * name_prg = args[0];
    char path[] = "/bin/";
    execvp(strcpy(path, name_prg), args);
  }
  else {
    wait(status);
  }

}

void run_shell(){
  char * line;
  int size;
  char * input = malloc (sizeof(char*) * 100);
  char ** args = malloc (sizeof(char*) * 100);
  //1. Getting input line from stdin
  printf("SHELL$ ");
  line = fgets(input, 100, stdin);
  if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')){
    input[strlen (input) - 1] = '\0';
  }

  //2. Parsing the input line
  args = parse_args(input, ";");
  size = num_args(input, ";");
  
  //3. Forking and Launching SHELL
  for(int i = 0; i < size; i++){
    char ** arg = parse_args(args[i], " ");
    fork_launch(arg);
  }

}


int main(){

  while(1){
    run_shell(); //runnning shell
  }

  return 0;

}
