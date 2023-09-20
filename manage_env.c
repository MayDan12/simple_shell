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

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[ti] + key_lengthed + 1);
		}
	}
	/* returns NULL if did not find it */
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

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{/* If key already exists */
			it_new_keys = 0;
			/* free the entire variable, it is new created below */
			free(data->env[ti]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[ti] = str_concat(str_duplicate(key), "=");
	data->env[ti] = str_concat(data->env[ti], value);

	if (it_new_keys)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
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

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_lengthed = str_length(key);

	for (ti = 0; data->env[ti]; ti++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[ti], key_lengthed) &&
		 data->env[ti][key_lengthed] == '=')
		{/* if key already exists, remove them */
			free(data->env[ti]);

			/* move the others keys one position down */
			ti++;
			for (; data->env[ti]; ti++)
			{
				data->env[ti - 1] = data->env[ti];
			}
			/* put the NULL value at the new end of the list */
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
