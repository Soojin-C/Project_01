#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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

  int f;
  char * input = malloc (sizeof(char*));
  //printf("arg:%s, %d\n", argv[1], argc);

  if ( argc == 1){

    printf("arg:%s, %d\n", argv[1], argc);
    //char * input = malloc (sizeof(char*));
    printf("SHELL$ ");
    fgets(input, 100, stdin);
    //scanf("%s", input);
    if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')){
      input[strlen (input) - 1] = '\0';
    }
    printf("%s\n", input);

    //execlp( "./a.out", "a.out" , (char *) NULL );

  }

  //if(argc > 1){
    int * status;
    //wait(status);
    char ** tmp_args = parse_args(input);

    printf("done parse %s, %s, %s \n", tmp_args[0], tmp_args[1], tmp_args[2]);
    f = fork();
    //printf("fork: %d; %d\n", f, getpid());

    if(f == 0){ //child; running process
      char * name_prg = tmp_args[0];
      //printf("name of prog: %s", name_prg);
      char path[] = "/bin/";
      //printf("path: %s", path);
      execvp(strcpy(path, name_prg), tmp_args);

    }

    else {

      wait(status);
      /*
      char * input = malloc (sizeof(char*));
      //sleep (1);
      printf("SHELL$ ");
      scanf("%s", input);
      printf("%s\n", input);
      */

      execlp( "./a.out", "a.out" ,(char *) NULL );

    }

  //}
  return 0;

}
