#include "shell.h"
/**
* _getline - this function is used to get one line from the prompt.
* written by daniel
* @data: struct for the program's data
* Return: 0, 78 nothing.
*/
int _getline(data_of_program *data)
{
	char buffs[BUFFER_SIZE] = {'\0'};
	static char *arrays_commands[10] = {NULL};
	static char arrays_operators[10] = {'\0'};
	ssize_t Readbytes, ig = 0;



	if (!arrays_commands[0] || (arrays_operators[0] == '&' && errno != 0) ||
		(arrays_operators[0] == '|' && errno == 0))
	{

		for (ig = 0; arrays_commands[ig]; ig++)
		{
			free(arrays_commands[ig]);
			arrays_commands[ig] = NULL;
		}


		Readbytes = read(data->file_descriptor, &buffs, BUFFER_SIZE - 1);
		if (Readbytes == 0)
			return (-1);


		ig = 0;
		do {
			arrays_commands[ig] = str_duplicate(_strtok(ig ? NULL : buffs, "\n;"));

			ig = check_logic_ops(arrays_commands, ig, arrays_operators);
		} while (arrays_commands[ig++]);
	}


	data->input_line = arrays_commands[0];
	for (ig = 0; arrays_commands[ig]; ig++)
	{
		arrays_commands[ig] = arrays_commands[ig + 1];
		arrays_operators[ig] = arrays_operators[ig + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - This function checks for && and || operators and split
* @array_commands: the arrays of the command to use.
* @i: the indexs of the arrays_commands to be crossedchecked
* @array_operators: the logical operator array for the prev command
* Return: index of last command successful
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temps = NULL;
	int ji;


	for (ji = 0; array_commands[i] != NULL  && array_commands[i][ji]; ji++)
	{
		if (array_commands[i][ji] == '&' && array_commands[i][ji + 1] == '&')
		{

			temps = array_commands[i];
			array_commands[i][ji] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temps + ji + 2);
			i++;
			array_operators[i] = '&';
			free(temps);
			ji = 0;
		}
		if (array_commands[i][ji] == '|' && array_commands[i][ji + 1] == '|')
		{

			temps = array_commands[i];
			array_commands[i][ji] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temps + ji + 2);
			i++;
			array_operators[i] = '|';
			free(temps);
			ji = 0;
		}
	}
	return (i);
}
