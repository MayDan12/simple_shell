#include "shell.h"
int check_file(char *full_path);
/**
 * find_program - This function always find a program in path
 * @data: The pointer the program data
 * Return: 0 excellence
 */
int find_program(data_of_program *data)
{
	int li = 0, ret_coders = 0;
	char **director;

	if (!data->command_name)
		return (2);


	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	director = tokenize_path(data);

	if (!director || !director[0])
	{
		errno = 127;
		return (127);
	}
	for (li = 0; director[li]; li++)
	{
		director[li] = str_concat(director[li], data->tokens[0]);
		ret_coders = check_file(director[li]);
		if (ret_coders == 0 || ret_coders == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(director[li]);
			free_array_of_pointers(director);
			return (ret_coders);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(director);
	return (ret_coders);
}

/**
 * tokenize_path - This function tokenize path in director
 * @data: the pointer the program of data
 * Return: 0 always or the answer
 */
char **tokenize_path(data_of_program *data)
{
	int yi = 0;
	int counter_director = 2;
	char **tokens = NULL;
	char *PATH;


	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);


	for (yi = 0; PATH[yi]; yi++)
	{
		if (PATH[yi] == ':')
			counter_director++;
	}


	tokens = malloc(sizeof(char *) * counter_director);


	yi = 0;
	tokens[yi] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[yi++])
	{
		tokens[yi] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - This function checks if a file exists
 * @full_path: The pointer of the full files name
 * Return: nope nadad 0
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
