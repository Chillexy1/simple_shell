#include "shell.h"
/*
*Author: Chillexy Steven   
*Program: WinMingle Community C Training
*Description: creates a child and parent process and executes if executable
*/
void exec_command(char *dir, char *command[])	
{
	int status;
	extern char **environ;
	pid_t pid;
	pid = fork();
	if (pid == -1)/* if process failed */
	{
		perror("");
		_exit(EXIT_FAILURE);
	}
	else if(pid == 0)/* child process */
	{
		if (execve(dir, command, environ) == -1)
		{
			perror("");
		}
	}
	
	else /* parent process */
	{
		wait(&status);
	}
}
