#include "shell.h"

//clean out line by getting rid of bad spaces
void spaces_clean(char * line){
  int count = 0;
  for(int i = 0; line[i]; i++){
    //if(count == 0 && line[count] == ' '){
      if(count > 0 & count < strlen(line)-1 || line[i] != ' ' ){
        line[count++] = line[i];
      }
    //}
  }
  line[count] = '\0';
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

void fork_launch2(char ** args, int out, int in){
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
    if (out != 1){//sets stdout to 1
      dup2(out, 1);
    }
    if (in != 0){//sets stdin to 0
      dup2(in, 0);
    }
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
  char *arg = *args; //reference to first arg in args
  //printf("%s\n", arg );

  //3. Forking and Launching SHELL
  int i = 0;
  while(arg){
    if (strchr(arg, '>')) { //redirection for >
      char * fnc = strsep(&arg, ">");
      char **cmds = parse_args(fnc, " ");
      while(arg[0] == ' '){
        arg++;
      }
      int fd = open(arg, O_WRONLY | O_CREAT, 0666);
      int x = dup(1);
      dup2(fd, 1);
      fork_launch2(cmds, x, 0);
      arg = args[++i];
      free(cmds);
    }
    else if(strchr(arg, '<')){ //redirection for <
      char * fnc = strsep(&arg, "<");
      char **cmds = parse_args(fnc, " ");
      while(arg[0] == ' '){
        arg++;
      }
      if(strcmp(cmds[0], "")){
        return;
      }
      int fd = open(arg, O_WRONLY | O_CREAT, 0666);
      int x = dup(0);
      dup2(fd, 0);
      fork_launch2(cmds, 1, x);
      arg = args[++i];
      free(cmds);
    }
    else{ //all else
      char **cmds = parse_args(arg, " ");
      fork_launch(cmds);
      arg = args[++i];
      free(cmds);
    }

  }
  free(args);

}


int main(){


  while(1){
    run_shell(); //runnning shell
  }

  return 0;

}
