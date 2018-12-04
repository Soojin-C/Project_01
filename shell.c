#include "shell.h"

/*======== void spaces_clean() ==========
  Inputs: char * line
  Returns: Nothing

  Removes the spaces in the beginning and at the end of the inputted line.

================================*/
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

/*======== char ** parse_args() ==========
	Inputs:  char * line, char * delim
	Returns: Array of strings where each entry was previously separated by a delim

	If line contains multiple arguments separated by delim, this function will put each argument into an array of strings

	====================*/
char ** parse_args(char * line, char * delim){
  char ** tmp_argv = malloc(100 *sizeof(char *));
  int i = 0;
  spaces_clean(line);
  while(line){
    tmp_argv[i] = strsep(&line, delim);
    spaces_clean(tmp_argv[i]);
    i++;
  }
  tmp_argv[i] = NULL;
  return tmp_argv;
}

/*======== void fork_launch() ==========
  Inputs: char ** args
  Returns: NONE

  Takes in an array of arguments and uses execvp to execute commands
  If cd command is called: chdir() moves into another directory
  If exit command is called: exits program
  Other commands: forks process and execvp.

================================================*/
void fork_launch(char ** args){
  int f;
  int * status;

  if(strcmp(args[0], "cd") == 0){
    chdir(args[1]);
  }

  else if(strcmp(args[0], "exit") == 0){
    exit(0);
  }

  else{
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

}

/*======== void fork_launch2() ==========
  Inputs: char ** args, int out, int in
  Returns: NONE

  Same function as fork_launch() but sets stdout back to 1 and stdin back to 0, used for redirection

================================================*/
void fork_launch2(char ** args, int out, int in){
  int f;
  int * status;

  if(strcmp(args[0], "cd") == 0){
    chdir(args[1]);
  }

  else if(strcmp(args[0], "exit") == 0){
    exit(0);
  }

  else{
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

}

/*======== void run_shell() ==========
Inputs: NONE
Returns: NONE

  Prints the SHELL$ heading
  Gets the input line from stdin
  Parses the input line on ;
  4 cases are considered before forking:
    * Redirection using >
    * Redirection using <
    * Piping using |
    * All other commands
===============================================*/
void run_shell(){
  signal(SIGINT, sighandler);
  char * line;
  int size;
  char * input = malloc (sizeof(char*) * 100);
  char ** args = malloc (sizeof(char*) * 100);

  //1. Getting input line from stdin
  int * status;
  wait(status);
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
    if (strchr(arg, '>') != NULL) { //redirection for >
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
      close(fd);
      free(cmds);
    }
    else if(strchr(arg, '<') != NULL){ //redirection for <
      char * fnc = strsep(&arg, "<");
      char **cmds = parse_args(fnc, " ");
      while(arg[0] == ' '){
        arg++;
      }
      //if(strcmp(cmds[0], "")){
      //  return;
      //}
      int fd = open(arg, O_WRONLY | O_CREAT, 0666);
      int x = dup(0);
      dup2(fd, 0);
      fork_launch2(cmds, 1, x);
      arg = args[++i];
      close(fd);
      free(cmds);
    }
    else if(strchr(arg, '|') != NULL){ //simple piping
      char ** cmds = parse_args(arg, "|");
      FILE * file1 = popen(cmds[0], "r");
      FILE * file2 = popen(cmds[1], "w");
      char inputpath[256];
      while(fgets(inputpath, sizeof(inputpath), file1)){
        fprintf(file2, "%s", inputpath);
      }
      pclose(file1);
      pclose(file2);
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

//Will exit on keyboard interrupt signal
static void sighandler(int signo){
  if (signo == SIGINT){
    while(1){
      exit(0);
    }
  }
}

/*========int main()========
Inputs: NONE
Outputs: 0

While loop to keep shell running.
=========================*/
int main(){

  signal(SIGINT, sighandler);
  while(1){
    run_shell(); //runnning shell
  }
  return 0;

}
