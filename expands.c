#include "shell.h"
/**
 * expand_variables - This function expands variable
 * @data: The is pointer to struct of program data *
 * Return: yet love 0
 */
void expand_variables(data_of_program *data)
{
	int ti, hj;
	char lines[BUFFER_SIZE] = {0}, expansions[BUFFER_SIZE] = {'\0'}, *temps;

	if (data->input_line == NULL)
		return;
	buffer_add(lines, data->input_line);
	for (ti = 0; lines[ti]; ti++)
		if (lines[ti] == '#')
			lines[ti--] = '\0';
		else if (lines[ti] == '$' && lines[ti + 1] == '?')
		{
			lines[ti] = '\0';
			long_to_string(errno, expansions, 10);
			buffer_add(lines, expansions);
			buffer_add(lines, data->input_line + ti + 2);
		}
		else if (lines[ti] == '$' && lines[ti + 1] == '$')
		{
			lines[ti] = '\0';
			long_to_string(getpid(), expansions, 10);
			buffer_add(lines, expansions);
			buffer_add(lines, data->input_line + ti + 2);
		}
		else if (lines[ti] == '$' && (lines[ti + 1] == ' ' || lines[ti + 1] == '\0'))
			continue;
		else if (lines[ti] == '$')
		{
			for (hj = 1; lines[ti + hj] && lines[ti + hj] != ' '; hj++)
				expansions[hj - 1] = lines[ti + hj];
			temps = env_get_key(expansions, data);
			lines[ti] = '\0', expansions[0] = '\0';
			buffer_add(expansions, lines + ti + hj);
			temps ? buffer_add(lines, temps) : 1;
			buffer_add(lines, expansions);
		}
	if (!str_compare(data->input_line, lines, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(lines);
	}
}

/**
 * expand_alias - This function always expanses aliasfr
 * @data: the pointers a struct ofprogram data
 * Return: n0 nadda 09 i
 */
void expand_alias(data_of_program *data)
{
	int ti, hj, was_expanded = 0;
	char lines[BUFFER_SIZE] = {0}, expansions[BUFFER_SIZE] = {'\0'}, *temps;

	if (data->input_line == NULL)
		return;

	buffer_add(lines, data->input_line);

	for (ti = 0; lines[ti]; ti++)
	{
		for (hj = 0; lines[ti + hj] && lines[ti + hj] != ' '; hj++)
			expansions[hj] = lines[ti + hj];
		expansions[hj] = '\0';

		temps = get_alias(data, expansions);
		if (temps)
		{
			expansions[0] = '\0';
			buffer_add(expansions, lines + ti + hj);
			lines[ti] = '\0';
			buffer_add(lines, temps);
			lines[str_length(lines)] = '\0';
			buffer_add(lines, expansions);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(lines);
	}
}

/**
 * buffer_add - This function always appends a string at the end buffer
 * @buffer: the buffer to always be filled
 * @str_to_add: the str to be copied in y the buffer
 * Return: 0 alwya nadda
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int lengthed, ti;

	lengthed = str_length(buffer);
	for (ti = 0; str_to_add[ti]; ti++)
	{
		buffer[lengthed + ti] = str_to_add[ti];
	}
	buffer[lengthed + ti] = '\0';
	return (lengthed + ti);
}
