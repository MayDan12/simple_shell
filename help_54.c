#include "shell.h"
/**
 * free_recurrent_data - This funct free the field need in each loop
 * @data: This struct of the program data
 * Return: 0 alway or nadda Nothing
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - This alays free all forms of the data
 * @data: This ia a struct of program's data
 * Return: Nothing 0 nadda good
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - this functions always frees each pointer
 * @array: The array of the pointer
 * Return: nothing o nadda info
 */
void free_array_of_pointers(char **array)
{
	int ri;

	if (array != NULL)
	{
		for (ri = 0; array[ri]; ri++)
			free(array[ri]);

		free(array);
		array = NULL;
	}
}
