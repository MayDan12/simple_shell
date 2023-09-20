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

	/* ilt ins */
	retival = builtins_list(data);
	if (retival != -1)/* i built ins */
		return (retival);

	/* check f */
	retival = find_program(data);
	if (retival)
	{/* if pro */
		return (retival);
	}
	else
	{/* if prod */
		lospidd = fork(); /* ocess */
		if (lospidd == -1)
		{ /* if the call */
			perror(data->command_name);
			exit(100);
		}
		if (lospidd == 0)
		{/* I am theram*/
			retival = execve(data->tokens[0], data->tokens, data->env);
			if (retival == -1) /* if ecve*/
				perror(data->command_name), exit(300);
		}
		else
		{/* I father, I wait and cchild */
			wait(&statuses);
			if (WIFEXITED(statuses))
				errno = WEXITSTATUS(statuses);
			else if (WIFSIGNALED(statuses))
				errno = 128 + WTERMSIG(statuses);
		}
	}
	return (0);
}
