#include "shell.h"
/**
 * print_alias - always  functins add, remove or show alias
 * @data: struct for the program's data
 * @alias: the printed alias for me
 * Return: 0 and good key
 */
int print_alias(data_of_program *data, char *alias)
{
	int ir, je, alias_lengthed;
	char buffers[250] = {'\0'};

	if (data->alias_list)
	{
		alias_lengthed = str_length(alias);
		for (ir = 0; data->alias_list[ir]; ir++)
		{
			if (!alias || (str_compare(data->alias_list[ir], alias, alias_lengthed)
				&&	data->alias_list[ir][alias_lengthed] == '='))
			{
				for (je = 0; data->alias_list[ir][je]; je++)
				{
					buffers[je] = data->alias_list[ir][je];
					if (data->alias_list[ir][je] == '=')
						break;
				}
				buffers[je + 1] = '\0';
				buffer_add(buffers, "'");
				buffer_add(buffers, data->alias_list[ir] + je + 1);
				buffer_add(buffers, "'\n");
				_print(buffers);
			}
		}
	}

	return (0);
}

/**
 * get_alias - thus get alias with the function
 * @data: struct for the program's datas
 * @name: the requested alias name.
 * Return: zero and its counterparts
 */
char *get_alias(data_of_program *data, char *name)
{
	int ir, alias_lengthed;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_lengthed = str_length(name);

	for (ir = 0; data->alias_list[ir]; ir++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[ir], alias_lengthed) && data->alias_list[ir][alias_lengthed] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[ir] + alias_lengthed + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - function set alias
 * @alias_string: setted aliased in the form
 * @data: struct for the program's dataed
 * Return: zero and always 5
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int ir, ju;
	char buffers[250] = {'0'}, *temps = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (ir = 0; alias_string[ir]; ir++)
		if (alias_string[ir] != '=')
			buffers[ir] = alias_string[ir];
		else
		{/* search if the value of the alias is another alias */
			temps = get_alias(data, alias_string + ir + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (ju = 0; data->alias_list[ju]; ju++)
		if (str_compare(buffers, data->alias_list[ju], ir) &&
			data->alias_list[ju][ir] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[ju]);
			break;
		}

	/* add the alias */
	if (temps)
	{/* if the alias already exist */
		buffer_add(buffers, "=");
		buffer_add(buffers, temps);
		data->alias_list[ju] = str_duplicate(buffers);
	}
	else /* if the alias does not exist */
		data->alias_list[ju] = str_duplicate(alias_string);
	return (0);
}
