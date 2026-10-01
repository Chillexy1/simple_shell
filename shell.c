#include "shell.h"
/*
*Author: Chillexy Steven  
*Program: WinMingle Community C Training
*Description: simple shell implementation
*/
int main(int argc, char *argx[])
{
	int i = 1, k = 0, m = 0, l = 0, count = 0, path_count = 0, found = 0, found_env = 0;
	int line_number = 0;
	char *cmd = NULL, *token, s[50], *env = "PATH", *terminate = "exit", *path, *path_cpy, *terminal = "env";
	char **argv, **dir, **shell;
	char *error = ": No such file or directory\n";
	size_t len = 0;
	extern char **environ;
	(void)argc;
	while (1)
	{
		if (isatty(0)) /* interactive mode check */
		{
			write(1, "($) ", 4);
		}
		if (getline(&cmd, &len, stdin) == -1) /* check if command failed */
		{
			if (feof(stdin) != 0) /* on success */
			{
				write(1, "\n", 1);
				free(cmd);
				exit(EXIT_SUCCESS);
			}
			else /*if it fails */
			{
				perror("");
				free(cmd);
				free(argv);
				exit(EXIT_FAILURE);
			}
		}
		line_number++;
		str(line_number, s);
		/* implement a varible that keeps track of how many argument the user inputed */
		i = 0;
		count = 0;
		while (cmd[i])
		{
			if (cmd[i] != ' ' && cmd[i] != '\n')
			{
				count++;
				while (cmd[i] != ' ' && cmd[i] != '\n' && cmd[i])
					i++;
			}
			i++;
		}
		argv = malloc(sizeof(*argv) * (count + 1)); /* build our custom argv */
		if (argv == NULL)
		{
			perror("");
			free(cmd);
			exit(EXIT_FAILURE);
		}
		token = strtok(cmd, " \n");
		i = 0;
		while (token)
		{
			argv[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		argv[i] = NULL;
		if (argv[0] == NULL)/*skip every process and continue from the start if input is null */
		{
			free(argv);
			continue;
		}
		/* implement functions/commands around argv[0]*/
		while (argv[0])
		{
			/* implement the exit function */
			k = 0;
			while (argv[0][k] == terminate[k] && argv[0][k] && terminate[k])
				k++;
			if (argv[0][k] == terminate[k])
			{
				free(cmd);
				free(argv);
				return (0);
			}
			/*___end___of___exit____function___*/
			/* implemnet the env button */
			i = 0;
			found_env = 0;
			while (argv[0][i] == terminal[i] && argv[0][i] && terminal[i])/*compare strings equality*/
				i++;
			if (argv[0][i] == terminal[i])
			{
				found_env = 1;
				l = 0;
				while (environ[i])
				{
					write(1, environ[i], _strlen(environ[i]));
					write(1, "\n",1);
					i++;
				}
			}
			/*____end___of___env___implementation___*/
			break;
		}
		if (found_env)/* this block also includes the env implementation cause wthout it we get double output of the environment*/
		{
			continue;
		}
		/*___end___of_____argv[0]____commands____implementation_____*/
		/* extract path from environ */
		i = 0;
		k = 0;
		while (environ[i])
		{
			while (environ[i][k] == env[k])
			{	
				k++;
				if (environ[i][k] == env[k])
				{
					path = environ[i] + 5;
					break;
				}
			}
			i++;
		}	
		/*____end___of__path___extraction_____*/
		/* process to get the number of directories in the path folder */
		i = 0;
		path_count = 0;
		while (path[i] != '\0')
		{
			if (path[i] == ':')
			{
				path_count++;
			}
			i++;
			if (path[i] == '\0')
				path_count++;
		}
		/*__end__of___process___*/
		path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
		if (path_cpy == NULL)
		{
			perror("");
			free(argv);
			exit(EXIT_FAILURE);
		}
		/* manually copy path strings to path_cpy */
		i = 0;
		k = 0;
		while (path[i])
		{
			path_cpy[k] = path[i];
			k++;
			i++;
		}
		path_cpy[k] = '\0';
		/*___end___of___path___copy___*/
		/* tokenize the path */
		dir = malloc(sizeof(*dir) * (path_count + 1));
		if (dir == NULL)
		{
			perror("");
			free(argv);
			free(path_cpy);
			exit(EXIT_FAILURE);
		}
		token = strtok(path_cpy, ":");
		i = 0;
		while (token)
		{
			dir[i] = token;
			token = strtok(NULL, ":");
			i++;
		}
		dir[i] = NULL;
		/*___end____of___tokenization___*/
		shell = malloc(sizeof(*shell) * (path_count + 2));
		if (shell == NULL)
		{
			perror("");
			free(argv);
			free(path_cpy);
			free(dir);
			exit(EXIT_FAILURE);
		}
		/* implement condition if first command does not contain a slash(/) */
		i = 0;
		found = 0;
		while (dir[i])
		{
			shell[i] = malloc(sizeof(*shell[i]) * (_strlen(dir[i]) +  _strlen(argv[0]) + 2));
			if (shell[i] == NULL)
			{
				free(dir);
				free(path_cpy);
				free(argv);
				exit(EXIT_FAILURE);

			}
			/*manually concates path with slash(/) and argv */
			l = 0;
			m = 0;
			while (dir[i][m])
			{
				shell[i][l] = dir[i][m];
				l++;
				m++;
			}
			shell[i][l] = '/';
			l++;
			k = 0;
			while (argv[0][k])
			{
				shell[i][l] = argv[0][k];
				l++;
				k++;
			}
			shell[i][l] = '\0';
			/*____end____of___concatenation_____*/
			/* executes file if it's executable */
			if (access(shell[i], X_OK) == 0)
			{
				found = 1;
				exec_command(shell[i], argv);
				free(shell[i]);
				free(path_cpy);
				free(dir);
				free(shell);
				break;
			}
			/*___end____of___execution___*/
			i++;

		}
		/*__end__of__command___not___containing___slash___implementation__*/
		/* print error message if file not executable */
		if(!found && access(argv[0], X_OK) == -1)
		{
			write(2, argx[0], _strlen(argx[0]));
			write(2,": ", 2 );
			write(2, s, _strlen(s));
			write(2,": ", 2 );
			write(2, argv[0], _strlen(argv[0]));
			write(2, error, _strlen(error));
			free(path_cpy);
			free(dir);
			free(shell);
		}
		/*_____end___of___error___implementation___*/
		/* execute file if first  command is executable */
		if (access(argv[0], X_OK) == 0 && !found)
		{
			exec_command(argv[0], argv);
			free(path_cpy);
			free(argv);
			free(shell);
		}
		/*_____end___of___first____command___implementation____*/
	}
	return (0);
}
