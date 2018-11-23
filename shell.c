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
  //printf("arg:%s, %d\n", argv[1], argc);

  if ( argc == 1){

 printf("arg:%s, %d\n", argv[1], argc);
 char * input = malloc (sizeof(char*));
 printf("SHELL$ ");
 scanf("%s", input);
 printf("%s\n", input);

 execlp( "./a.out", "a.out" , input ,(char *) NULL );

   }

  if(argc > 1){
    char ** tmp_args = parse_args(argv[1]);

    if (f){

      int * status;

      printf("done parse\n");
      f = fork();
      printf("fork: %d; %d\n", f, getpid());

      wait(status);
      char * input = malloc (sizeof(char*));
      printf("SHELL$ ");
      scanf("%s", input);
      printf("%s\n", input);

      execlp( "./a.out", "a.out" , input ,(char *) NULL );
    }

  if(f == 0){ //child; running process
    char * name_prg = tmp_args[0];
    printf("name of prog: %s", name_prg);
    char path[] = "/bin/";
    printf("path: %s", path);
    execvp(strcpy(path, name_prg), tmp_args);
    //return 0;

  }
  }

  return 0;

}
