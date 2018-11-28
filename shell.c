#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char ** parse_sem(char * line){
  char ** tmp_argv = malloc(6 *sizeof(char *));
  for(int i = 0; i < 6; i++){
    tmp_argv[i] = strsep(&line, ";");
    printf("%s\n", tmp_argv[i] );
  }
  return tmp_argv;
}

char ** parse_args(char ** args){
  char ** argv = malloc(sizeof(args));
  for(int j = 0; j < sizeof(args); j++){
    argv[j] = strsep(args, " ");
    //printf("%s\n", argv[j]);
  }
  return argv;
}


int main(int argc, char * argv[]){

  int f;
  char * input = malloc (sizeof(char*));

  if ( argc == 1){

    printf("SHELL$ ");
    fgets(input, 100, stdin);
    if ((strlen(input) > 0) && (input[strlen (input) - 1] == '\n')){
      input[strlen (input) - 1] = '\0';
    }

  }

  //if(argc > 1){
    int * status;
    char ** tmp_args = parse_sem(input);
    //printf("%s, %s\n", tmp_args[0], tmp_args[1] );
    for(int i = 0; i < sizeof(tmp_args); i++){
      //printf("%s\n", tmp_args[i]);
      char ** final_args = malloc(sizeof(tmp_args));
      final_args = parse_args(&tmp_args[i]);
    //  printf("%s\n", final_args[0]);
      f = fork();

      if(f == 0){ //child; running process
        char * name_prg = final_args[0];
        char path[] = "/bin/";
        execvp(strcpy(path, name_prg), final_args);
      }
      else {
        if() //if theres more to tmpargs then 
        wait(status);
        execlp( "./a.out", "a.out" ,(char *) NULL );

      }
    }



  //}
  return 0;

}
