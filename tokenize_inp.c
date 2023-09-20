#include "shell.h"
/**
 * tokenize - This funtct separate the string ing a design delim
 * @data:  THe pointers to the s program datas.
 * Return: 0 always and the array of the different parts of string
 */
void tokenize(data_of_program *data)
{
	char *limiter = " \t";
	int di, rj, countered = 2, lengthed;

	lengthed = str_length(data->input_line);
	if (lengthed)
	{
		if (data->input_line[lengthed - 1] == '\n')
			data->input_line[lengthed - 1] = '\0';
	}

	for (di = 0; data->input_line[di]; di++)
	{
		for (rj = 0; limiter[rj]; rj++)
		{
			if (data->input_line[di] == limiter[rj])
				countered++;
		}
	}

	data->tokens = malloc(countered * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	di = 0;
	data->tokens[di] = str_duplicate(_strtok(data->input_line, limiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[di++])
	{
		data->tokens[di] = str_duplicate(_strtok(NULL, limiter));
	}
}
