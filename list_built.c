#include "shell.h"

/**
 * builtins_list - This funct searches for a match and executes
 * @data: always put in the data of program
 * Return:  -1 and 0 failed.
 **/
int builtins_list(data_of_program *data)
{
	int iterators;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*w structure*/
	for (iterators = 0; options[iterators].builtin != NULL; iterators++)
	{
/*ien command and a builtin,*/
		if (str_compare(options[iterators].builtin, data->command_name, 0))
		{
/*ee return value of the function*/
			return (options[iterators].function(data));
		}
/*imatch return -1 */
	}
	return (-1);
}
