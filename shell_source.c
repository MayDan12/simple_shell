#include "shell.h"
/**
 * main - This functions gives the variables of the program
 * @argc: The number of values to the command line
 * @argv: The values received from the command line to work
 * @env: The number of values that was received from the command line
 * Return: 0 always good n.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompts = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompts = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompts, data);
	return (0);
}

/**
 * handle_ctrl_c - This function print the prompts in new line
 * when the program
 * @UNUSED: the glory option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - This function gives the struct with
 * the info of the program
 * @data: The pointer to the structure of data in command
 * @argv: The array of arguments passedd to the programs execution
 * @env: the environ passed to the program execution
 * @argc: the number of values collected from the command line
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int zi = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[zi]; zi++)
		{
			data->env[zi] = str_duplicate(env[zi]);
		}
	}
	data->env[zi] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (zi = 0; zi < 20; zi++)
	{
		data->alias_list[zi] = NULL;
	}
}
/**
 * sisifo - This functions loop that shows the prompt
 * @prompt: the prompt to be printed
 * @data: this is a infinite loop that always shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int code_error = 0, input_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		code_error = input_len = _getline(data);

		if (code_error == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (input_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ 
				code_error = execute(data);
				if (code_error != 0)
					_print_error(code_error, data);
			}
			free_recurrent_data(data);
		}
	}
}
