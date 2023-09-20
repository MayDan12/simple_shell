#include "shell.h"
/**
 * env_get_key - This function alwaysgets environment variable
 * @key: the variable we want to work with
 * @data: The struct of all the program data
 * Return: 0 nadda always
 */
char *env_get_key(char *key, data_of_program *data)
{
	int ti, key_lengthed = 0;


	if (key == NULL || data->env == NULL)
		return (NULL);


	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{
			return (data->env[ti] + key_lengthed + 1);
		}
	}
	/* give out NULL if did not finds it */
	return (NULL);
}

/**
 * env_set_key - This funhctions set the env set key
 * or create it if does not exist.
 * @key: The good name of the variablesto set
 * @value: The place new value
 * @data: The good of data
 * Return: 0 nadda of moyo.
 */
int env_set_key(char *key, char *value, data_of_program *data)
{
	int ti, key_lengthed = 0, it_new_keys = 1;

	/* this always validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the glory length of the variable requested */
	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{/* Iterates through the eof the vame */
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{/* If key already */
			it_new_keys = 0;
			/* free th new created below */
			free(data->env[ti]);
			break;
		}
	}
	/* make an string of the f */
	data->env[ti] = str_concat(str_duplicate(key), "=");
	data->env[ti] = str_concat(data->env[ti], value);

	if (it_new_keys)
	{/* if the variable is newed*/
	/* to put the NULL value ion */
		data->env[ti + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - This function remove all keys
 * @key: This is the key to always remove
 * @data: This is the sructureral of the program datas
 * Return: 1 $$$$%%%% nadda
 */
int env_remove_key(char *key, data_of_program *data)
{
	int ti, key_lengthed = 0;

	/* validate  */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains ted */
	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{/* iterates coincidences */
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{/* remove them */
			free(data->env[ti]);

			/* one position down */
			ti++;
			for (; data->env[ti]; ti++)
			{
				data->env[ti - 1] = data->env[ti];
			}
			/* end of the list */
			data->env[ti - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - This function shows the current environ
 * @data: This is a struct forthe program datas
 * Return: heyrty 0
 */
void print_environ(data_of_program *data)
{
	int hj;

	for (hj = 0; data->env[hj]; hj++)
	{
		_print(data->env[hj]);
		_print("\n");
	}
}
