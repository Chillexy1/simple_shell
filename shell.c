#include "main.h"
#include <stdio.h>
/*
 *Author: Chillexy Steven
 *Program: WinMingle Community C Training
 *Description: simple shell implementation
 */
int simple_shell(int argc, char *argx[])
{
	int i = 1, k = 0, m = 0, l = 0, count = 0;
	int path_count = 0, found = 0, found_env = 0;
	int line_number = 0, status = 0, set = 0;
	char *cmd, *token, s[50], *env = "PATH";
	char *terminate = "exit", *path, *path_cpy, *terminal = "env";
	char **argv = NULL, **dir, **shell, **new_env, **unsetenv;
	char *error = ": No such file or directory\n";
	int found_variable = 0, setenv = 0, unset_var = 0, unset = 0;
	extern char **environ;
	int setenv_len, env_len = 0, found_unset = 0, unset_len = 0;
	int own_memory = 0;
	char *setenv_content, *old_memory, *env_strings, *new_env_string;
	(void)argc;
	/*initialize memory ownership flag*/
	i = 0;
	while (environ[i])
		i++; /*length of environ entries*/
	env_strings = malloc(sizeof(*env_strings) * i);
	if (env_strings == NULL)
	{
		free(argv);
		exit(EXIT_FAILURE);
	}
	k = 0;
	while (k < i)
	{
		env_strings[k] = 0; /*initialize entries to 0*/
		k++;
	}
	/*^^END__OF__OWNNERSHIP__INITIALLIZATION__FLAG*/
	while (1)
	{
		if (isatty(0)) /* if its an iteractive mode */
			write(1, "($) ", 4);
		cmd = my_getline(); /*COMMAND LINE ARGUMENT implementation*/
		if (cmd == NULL)
		{
			if (isatty(0))
				write(1, "\n", 1); /*CTRL + D implementaton*/
			/*environment ckean up process*/
			i = 0;
			while (environ[i])
			{
				if (env_strings[i])
					free(environ[i]);
				i++;
			}
			if (own_memory)
				free(environ);
			free(env_strings);
			free(argv);
			argv = NULL;
			/*__END__OF__ENVIRONMENT__CLEANUP__*/
			exit(EXIT_SUCCESS);
		}

		line_number++;
		str(line_number, s); /*converts linenumber to strings*/
		/* implement a varible that keeps track of how many argument the
		 * user inputed */
		i = 0;
		count = 0;
		while (cmd[i])
		{
			if (cmd[i] != ' ' && cmd[i] != '\n')
			{
				count++;
				while (cmd[i] != ' ' && cmd[i] != '\n' &&
				       cmd[i])
					i++;
			}
			i++;
		}
		argv = malloc(sizeof(*argv) *
			      (count + 1)); /* build our custom argv */
		if (argv == NULL)
		{
			perror("");
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
		if (argv[0] == NULL) /*empty command implementaton*/
		{
			free(argv);
			argv = NULL;
			continue;
		}
		/* implemnet the env button */
		k = 0;
		i = 0;
		found_env = 0;
		while (k < count)
		{
			while (argv[k][i] == terminal[i] && argv[k][i] &&
			       terminal[i]) /*compare strings equality*/
				i++;
			if (argv[k][i] == terminal[i])
			{
				if (count != 1)
				{
					break;
				}
				found_env = 1;
				l = 0;
				while (environ[l])
				{
					write(1, environ[l],
					      _strlen(environ[l]));
					write(1, "\n", 1);
					l++;
				}
			}
			break;
			k++;
		}
		/*____end___of___env___implementation___*/
		/* implement the exit function */
		k = 0;
		i = 0;
		while (i < count)
		{
			while (argv[i][k] == terminate[k] && argv[i][k] &&
			       terminate[k])
				k++;
			if (argv[i][k] ==
			    terminate[k]) /*if exit comparison is true*/
			{
				if (count == 2)
				{
					k = 0;
					while (argv[i + 1][k])
					{
						if (argv[i + 1][k] >= '0' &&
						    argv[i + 1][k] <= '9')
						{
							status = status * 10 +
								 (argv[i + 1]
								      [k] -
								  '0');
						}
						k++;
					}
					/*enviroment clean up process*/
					l = 0;
					while (environ[l])
					{
						if (env_strings[l])
							free(environ[l]);
						l++;
					}
					if (own_memory)
						free(environ);
					free(env_strings);
					free(argv);
					/*__END__OF__ENVIRONMENT__CLEANUP__*/
					return (status);
				}
				/*enviroment clean up process*/
				l = 0;
				while (environ[l])
				{
					if (env_strings[l])
						free(environ[l]);
					l++;
				}
				if (own_memory)
					free(environ);
				free(env_strings);
				free(argv);
				/*__END__OF__ENVIRONMENT__CLEANUP__*/
				return (0);
			}
			i++;
		}
		/*___end___of___exit____function___*/
		if (found_env) /* this block also includes the env
				  implementation cause wthout it we get double
				  output of the environment*/
		{
			free(argv);
			continue;
		}
		/*setenv and unset implementaton*/
		i = 0;
		k = 0;
		m = 0;
		unset = 0;
		unset_var = 0;
		while (i < count)
		{
			while (argv[0][k] && "setenv"[k] &&
			       argv[0][k] == "setenv"[k]) /*compare arguments to
							     setenv string*/
				k++;
			while (argv[0][m] && "unsetenv"[m] &&
			       argv[0][m] ==
				       "unsetenv"[m]) /*compare arguments to
							 unsetenv strings*/
				m++;
			set = 0;
			setenv = 0;
			if (argv[0][k] == '\0' &&
			    "setenv"[k] == '\0') /*checks if string matches with
						    argument*/
			{
				setenv = 1; /*represents setenv matches first
					       argument*/
				if (count !=
				    3) /*check if wrong arguments are paased*/
				{
					set = 1;
					break;
				}
			}
			else if (argv[0][m] == '\0' &&
				 "unsetenv"[m] ==
					 '\0') /*check if unsetenv matches with
						  aegument*/
			{
				unset_var = 1;
				if (count != 2)
				{
					unset = 1;
					break;
				}
			}
			i++;
		}
		if (unset_var && !unset) /*condition to take if unsetenv
					    correspond with argv[0]*/
		{
			/*loop through environ and compare it with unsetenv
			 * variable*/
			l = 0;
			found_unset = 0;
			env_len = 0;
			while (environ[l])
			{
				/*compare environ with unsetenv variable*/
				i = 0;
				while (environ[l][i] && argv[1][i] &&
				       environ[l][i] == argv[1][i])
					i++;
				if (environ[l][i] == '=' && argv[1][i] == '\0')
				{
					found_unset = 1;
					unset_len = env_len;
					break;
				}
				/*__end__of__comparison__between__unsetenv__and__environ__*/
				env_len++;
				l++;
			}
			/*end__of__unsetenv__environ__loop__serach__*/
		}
		if (found_unset && unset_var && !unset)
		{
			/*process to allocate enough memory for the pointer of
			 * char*/
			k = 0;
			while (environ[k])
				k++;
			unsetenv = malloc(sizeof(*unsetenv) * (k + 1));
			if (unsetenv == NULL)
			{
				free(argv);
				exit(EXIT_FAILURE);
			}
			new_env_string = malloc(sizeof(*new_env_string) * k);
			if (new_env_string == NULL)
			{
				free(unsetenv);
				free(argv);
				exit(EXIT_FAILURE);
			}
			/*end__of__pointer__char__memory__allocation__*/
			if (env_strings[unset_len])
				free(environ[unset_len]);
			k = 0;
			m = 0;
			while (environ[k])
			{
				if (k == unset_len)
				{
					k++;
					continue;
				}
				unsetenv[m] = environ[k];
				new_env_string[m] = env_strings[k];
				m++;
				k++;
			}
			unsetenv[m] = NULL;
			if (own_memory)
				free(environ);
			free(env_strings);
			environ = unsetenv;
			env_strings = new_env_string;
			own_memory = 1;
			free(argv);
			argv = NULL;
			continue;
		}
		else if (!found_unset && unset_var && !unset)
		{
			write(2, argx[0], _strlen(argx[0]));
			write(2, ": ", 2);
			write(2, s, _strlen(s));
			write(2, ": ", 2);
			write(2, "Error", 5);
			write(2, ": ", 2);
			write(2, argv[1], _strlen(argv[1]));
			write(2, ": ", 2);
			write(2, "Invalid environment",
			      _strlen("invalid environment"));
			write(1, "\n", 1);
			free(argv);
			argv = NULL;
			continue;
		}
		if (unset) /*error message if unsetenv arguments not meant*/
		{
			write(2, argx[0], _strlen(argx[0]));
			write(2, ": ", 2);
			write(2, s, _strlen(s));
			write(2, ": ", 2);
			write(2, "Usage", _strlen("Usage"));
			write(2, ": ", 2);
			write(2, argv[0], _strlen(argv[0]));
			write(2, ": ", 2);
			write(2, "VARIABLE", _strlen("VARIABLE"));
			write(1, "\n", 1);
			free(argv);
			argv = NULL;
			continue;
		}
		if (setenv && !set) /*condition if argument matches setenv and
				       count is == 3*/
		{
			/*loop through environ*/
			l = 0;
			found_variable = 0;
			while (environ[l])
			{
				/*search for comparison between environ and
				 * argv[2]*/
				k = 0;
				while (environ[l][k] && argv[1][k] &&
				       environ[l][k] == argv[1][k])
					k++;
				if (environ[l][k] == '=' &&
				    argv[1][k] ==
					    '\0') /*if comparison matches the
						     available environ strings*/
				{
					found_variable = 1;
					break;
				}
				l++;
			}
			/*__end__of__comparison__search__*/
		}
		if (found_variable && setenv &&
		    !set) /*condition if argumments matches environ variable*/
		{
			/*implement condition if setenv variable matches with
			 * argv[1]*/
			setenv_len = (_strlen(argv[1]) + _strlen(argv[2]) +
				      2); /*length of new strings*/
			setenv_content =
				malloc(sizeof(*setenv_content) * setenv_len);
			if (setenv_content == NULL)
			{
				free(argv);
				argv = NULL;
				exit(EXIT_FAILURE);
			}
			/*allocation process of new string*/
			k = 0;
			while (argv[1][k])
			{
				setenv_content[k] =
					argv[1][k]; /*allocate argv[1]*/
				k++;
			}
			setenv_content[k] =
				'='; /*concatenates '=' to the new memory*/
			k++;
			m = 0;
			while (argv[2][m]) /*concat argv[2]/value to the new
					      allocated memory*/
			{
				setenv_content[k + m] = argv[2][m];
				m++;
			}
			setenv_content[k + m] = '\0';
			old_memory = environ[l];
			if (env_strings[l])
				free(old_memory);
			environ[l] =
				setenv_content; /*make the old memory points to
						   the new allocated memory*/
			/*__end__of__new_string__allocation*/
			env_strings[l] = 1;
			free(argv);
			argv = NULL;
			continue;
		}
		/*__end_of_setenv__variable__match__implementation__*/
		else if (!found_variable && setenv &&
			 !set) /*create new variable with value if varible not
				  found in environment*/
		{
			setenv_len = (_strlen(argv[1]) + _strlen(argv[2]) +
				      2); /*length of new strings*/
			setenv_content =
				malloc(sizeof(*setenv_content) * setenv_len);
			if (setenv_content == NULL)
			{
				free(argv);
				argv = NULL;
				exit(EXIT_FAILURE);
			}
			/*allocation process of new string*/
			k = 0;
			while (argv[1][k])
			{
				setenv_content[k] =
					argv[1][k]; /*allocate argv[1]*/
				k++;
			}
			setenv_content[k] =
				'='; /*concatenates '=' to the new memory*/
			k++;
			m = 0;
			while (argv[2][m]) /*concat argv[2]/value to the new
					      allocated memory*/
			{
				setenv_content[k + m] = argv[2][m];
				m++;
			}
			setenv_content[k + m] = '\0';
			/*__end__of__new_string__allocation*/
			/*expand environ to accomodate new pointer*/
			l = 0;
			env_len = 0;
			while (environ[l])
			{
				env_len++; /*number of environ elements*/
				l++;
			}
			new_env = malloc(sizeof(*new_env) * (env_len + 2));
			if (new_env == NULL)
			{
				free(setenv_content);
				free(argv);
				argv = NULL;
				exit(EXIT_FAILURE);
			}
			new_env_string = malloc(
				sizeof(*new_env_string) *
				(env_len + 1)); /*new memory ownership array*/
			if (new_env_string == NULL)
			{
				free(setenv_content);
				free(new_env);
				free(argv);
				argv = NULL;
				exit(EXIT_FAILURE);
			}
			i = 0;
			/*allocates environ to new_env*/
			while (environ[i])
			{
				new_env[i] = environ[i];
				i++;
			}
			new_env[i] = setenv_content; /*concatenate the newly
							allocated stings*/
			new_env[i + 1] = NULL;
			i = 0;
			while (i < env_len)
			{
				new_env_string[i] =
					env_strings[i]; /*copies ownership
							   flag*/
				i++;
			}
			new_env_string[i] = 1;
			if (own_memory)
				free(environ);
			free(env_strings);
			environ = new_env; /*make environ points to the new
					      allocated pointer*/
			env_strings = new_env_string;
			own_memory = 1;
			/*__end__of__expansion__*/
			free(argv);
			argv = NULL;
			continue;
		}
		if (set) /*error output if wrong setenv
		    arguments are passed*/
		{
			write(2, argx[0], _strlen(argx[0]));
			write(2, ": ", 2);
			write(2, s, _strlen(s));
			write(2, ": ", 2);
			write(2, "Usage", _strlen("Usage"));
			write(2, ": ", 2);
			write(2, argv[0], _strlen(argv[0]));
			write(2, ": ", 2);
			write(2, "VARIABLE", _strlen("VARIABLE"));
			write(2, ": ", 2);
			write(2, "VALUE", _strlen("VALUE"));
			write(1, "\n", 1);
			free(argv);
			argv = NULL;
			continue;
		}
		/*__end__of__setenv__and__unsetenv__implementation*/
		/*implement condition if setenv variable not
		 * found*/
		/*__end__of__variable__condition__not_found__*/
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
		/* process to get the number of directories in
		 * the path folder
		 */
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
		/* implement condition if first command does not
		 * contain a slash(/) */
		i = 0;
		found = 0;
		while (dir[i])
		{
			shell[i] = malloc(
				sizeof(*shell[i]) *
				(_strlen(dir[i]) + _strlen(argv[0]) + 2));
			if (shell[i] == NULL)
			{
				free(dir);
				free(path_cpy);
				free(argv);
				free(shell);
				exit(EXIT_FAILURE);
			}
			/*manually concates path with slash(/)
			 * and argv */
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
				free(argv);
				argv = NULL;
				break;
			}
			else
				free(shell[i]);
			/*___end____of___execution___*/
			i++;
		}
		/*__end__of__command___not___containing___slash___implementation__*/
		/* print error message if file not executable */
		if (!found && access(argv[0], X_OK) == -1)
		{
			write(2, argx[0], _strlen(argx[0]));
			write(2, ": ", 2);
			write(2, s, _strlen(s));
			write(2, ": ", 2);
			write(2, argv[0], _strlen(argv[0]));
			write(2, error, _strlen(error));
			free(path_cpy);
			free(dir);
			free(shell);
			free(argv);
			argv = NULL;
			continue;
		}
		/*_____end___of___error___implementation___*/
		/* execute file if first  command is executable
		 */
		if (!found && access(argv[0], X_OK) == 0)
		{
			exec_command(argv[0], argv);
			free(path_cpy);
			free(dir);
			free(shell);
			free(argv);
		}
		/*_____end___of___first____command___implementation____*/
	}
	return (0);
}
