#include "shell.h"

//clean out line by getting rid of bad spaces
void spaces_clean(char * line){
  char* i = line;
  char* j = &line[strlen(line)-1];
  if(*i == ' '){
    i++;
  }
  if(*j == ' '){
    j--;
  }
}


char ** parse_args(char * line, char * delim){
  char ** tmp_argv = malloc(100 *sizeof(char *));
  int i = 0;
  while(line){
    tmp_argv[i] = strsep(&line, delim);
    spaces_clean(tmp_argv[i]);
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
    if(execvp(args[0], args) == -1){
      printf("%s: Command not found try again. \n", args[0] );
    }
    exit(0);
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
  args = parse_args(line, ";");
  char *arg = *args;

  //3. Forking and Launching SHELL
  int i = 0;
  while(arg){
    char **cmds = parse_args(arg, " ");
    fork_launch(cmds);
    arg = args[++i];
    free(cmds);

  }
  free(args);

}


int main(){

  while(1){
    run_shell(); //runnning shell
  }

  return 0;

}
