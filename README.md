# CC SHELL
* By Fiona Cai and Soojin Choi

## Features:  
* Forks and executes inputted commands.  
* Parses multiple commands with `;`
* Redirection with `>` and `<`
* Simple piping with `|`
* Will exit on keyboard interrupt signal

## Bugs:  
* Limited to 100 arguments
* Simple piping also executes the first command and prints out the result after the pipe result
* Multiple redirections does not work properly

## Wanted to implement but could not:
* Redirection with `>>`, `<<`, `2>`, `2>>`, `&>`

## Function Headers
### shell.c
```
/*======== char ** parse_args() ==========
	Inputs:  char * line, char * delim
	Returns: Array of strings where each entry was previously separated by a delim

	If line contains multiple arguments separated by delim, this function will put each argument into an array of strings
	====================*/

/*======== void spaces_clean() ==========  
  Inputs: char * line
  Returns: Nothing  

  Removes the spaces in the beginning and at the end of the inputted line.  
================================*/  

/*======== void fork_launch() ==========  
  Inputs: char ** args
  Returns: NONE  

  Takes in an array of arguments and uses execvp to execute commands
  If cd command is called: chdir() moves into another directory  
  If exit command is called: exits program
  Other commands: forks process and execvp.  
================================================*/  

/*======== void fork_launch2() ==========  
  Inputs: char ** args, int out, int in
  Returns: NONE  

  Same function as fork_launch() but sets stdout back to 1 and stdin back to 0, used for redirection   
================================================*/

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

/*========static void sighandler(){========
	Inputs: int signo
	Outputs: NONE

	Will exit on keyboard interrupt signal
=========================*/

/*========int main()========
  Inputs: NONE
  Outputs: 0

  While loop to keep shell running.
=========================*/

```
