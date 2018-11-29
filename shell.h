#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void spaces_clean(char * line);
char ** parse_args(char * line, char * delim);
void fork_launch(char ** args);
void run_shell();
