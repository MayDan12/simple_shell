#include "shell.h"
/**
 * _print - This function df writes a array of chars
 * @string: This is a pointer to a array of chars
 * Return: The good one.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _printe - This function writes a fg array of chars
 * @string: This is a ypointer to the array of chars
 * Return: 0 alwyas fail.
 * On error, -1 is returned.
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - This functions writes an array of chars
 * @data: a pointer to uthe program's data'
 * @errorcode: the code of error to print
 * Return: -1 if failed.
 */
int _print_error(int errorcode, data_of_program *data)
{
	char d_as_love[10] = {'\0'};

	long_to_string((long) data->exec_counter, d_as_love, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_as_love);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_as_love);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_as_love);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
