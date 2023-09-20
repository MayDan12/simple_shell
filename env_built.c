#include "shell.h"
/**
 * builtin_env - The funct shows the shell running
 * @data: programdata for all
 * Return: rweturn all u can return
 */
int builtin_env(data_of_program *data)
{
	int in;
	char cpnames[50] = {'\0'};
	char *vars_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (in = 0; data->tokens[1][in]; in++)
		{/* checks if exists a char = */
			if (data->tokens[1][in] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				vars_copy = str_duplicate(env_get_key(cpnames, data));
				if (vars_copy != NULL)
					env_set_key(cpnames, data->tokens[1] + in + 1, data);

				/* print the environ */
				print_environ(data);
				if (env_get_key(cpnames, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(cpnames, vars_copy, data);
					free(vars_copy);
				}
				return (0);
			}
			cpnames[in] = data->tokens[1][in];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * @data: always the struct for the programs data
 * Return: 00 okays
 */
int builtin_set_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - %$$$$###############&&&&&&&&..
 * @data: struct for the program's data.
 * Return: void always
 */
int builtin_unset_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
