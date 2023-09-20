#include "shell.h"
/**
 * execute - This function execute a command.
 * @data: the pointers that leads to the program data
 * Return: -1 if failed nadda.
 */
int execute(data_of_program *data)
{
	int retival = 0, statuses;
	pid_t lospidd;

	/* check for program in built ins */
	retival = builtins_list(data);
	if (retival != -1)/* if program was found in built ins */
		return (retival);

	/* check for program file system */
	retival = find_program(data);
	if (retival)
	{/* if program not found */
		return (retival);
	}
	else
	{/* if program was found */
		lospidd = fork(); /* create a child process */
		if (lospidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(100);
		}
		if (lospidd == 0)
		{/* I am the child process, I execute the program*/
			retival = execve(data->tokens[0], data->tokens, data->env);
			if (retival == -1) /* if error when execve*/
				perror(data->command_name), exit(300);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&statuses);
			if (WIFEXITED(statuses))
				errno = WEXITSTATUS(statuses);
			else if (WIFSIGNALED(statuses))
				errno = 128 + WTERMSIG(statuses);
		}
	}
	return (0);
}
