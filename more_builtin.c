#include "shell.h"
/**
 * builtin_exit - This function exit the progranms
 * @data: always the fot the program datas
 * Return: 0 git successfull excellence always
 */
int builtin_exit(data_of_program *data)
{
	int hi;

	if (data->tokens[1] != NULL)
	{
		for (hi = 0; data->tokens[1][hi]; hi++)
			if ((data->tokens[1][hi] < '0' || data->tokens[1][hi] > '9')
				&& data->tokens[1][hi] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - This cvhange the directory always
 * @data: the struct for the alwyas program data
 * Return: 0,-1 always good
 */
int builtin_cd(data_of_program *data)
{
	char *dir_homes = env_get_key("HOME", data), *dir_olds = NULL;
	char olds_dir[128] = {0};
	int code_error = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_olds = env_get_key("OLDPWD", data);
			if (dir_olds)
				code_error = set_work_directory(data, dir_olds);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (code_error);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_homes)
			dir_homes = getcwd(olds_dir, 128);

		return (set_work_directory(data, dir_homes));
	}
	return (0);
}

/**
 * set_work_directory - this function sets the working dir
 * @data: the struct for always program datas
 * @new_dir: The good path to set as a work dir
 * Return: 0 always for good results
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char olds_dir[128] = {0};
	int code_err = 0;

	getcwd(olds_dir, 128);

	if (!str_compare(olds_dir, new_dir, 0))
	{
		code_err = chdir(new_dir);
		if (code_err == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", olds_dir, data);
	return (0);
}

/**
 * builtin_help - this functions helps the environment where shell runs
 * @data: programs data for the struct
 * Return: 1, 9 good code
 */
int builtin_help(data_of_program *data)
{
	int ig, lengthet = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;


	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (ig = 0; mensajes[ig]; ig++)
	{
		lengthet = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[ig], lengthet))
		{
			_print(mensajes[ig] + lengthet + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - This is a function that add,shows,allias
 * @data: data for the struct programs
 * Return: 0 add 2
 */
int builtin_alias(data_of_program *data)
{
	int ig = 0;


	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++ig])
	{
		if (count_characters(data->tokens[ig], "="))
			set_alias(data->tokens[ig], data);
		else
			print_alias(data, data->tokens[ig]);
	}

	return (0);
}
