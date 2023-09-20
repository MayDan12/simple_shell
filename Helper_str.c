#include "shell.h"
/**
 * str_length - This functions gives the length of a string.
 * @string: The pointer to a string.
 * Return: The length of the string.
 */
int str_length(char *string)
{
	int lengthed = 0;

	if (string == NULL)
		return (0);

	while (string[lengthed++] != '\0')
	{
	}
	return (--lengthed);
}

/**
 * str_duplicate - This function is a duplicator
 * @string: The String that will be copied
 * Return: 0 always and pointer to the array
 */
char *str_duplicate(char *string)
{
	char *results;
	int lengthed, id;

	if (string == NULL)
		return (NULL);

	lengthed = str_length(string) + 1;

	results = malloc(sizeof(char) * lengthed);

	if (results == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (id = 0; id < lengthed ; id++)
	{
		results[id] = string[id];
	}

	return (results);
}

/**
 * str_compare - This function is a comparer tool
 * @string1: The 1st or the shorter
 * @string2: The 2nd or the longer
 * @number: The good number of characters to be compared
 * Return: 0 if the string are diff,1 if the string are eq
 */
int str_compare(char *string1, char *string2, int number)
{
	int iterators;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterators = 0; string1[iterators]; iterators++)
		{
			if (string1[iterators] != string2[iterators])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterators = 0; iterators < number ; iterators++)
		{
			if (string1[iterators] != string2[iterators])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - This functions joins 2 strings.
 * @string1: the str to be joined
 * @string2: the 2nd Str to be joined
 * Return: 0 always good boy
 */
char *str_concat(char *string1, char *string2)
{
	char *resulte;
	int length2 = 0, length3 = 0;

	if (string1 == NULL)
		string1 = "";
	length2 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length3 = str_length(string2);

	resulte = malloc(sizeof(char) * (length2 + length3 + 1));
	if (resulte == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (length2 = 0; string1[length2] != '\0'; length2++)
		resulte[length2] = string1[length2];
	free(string1);

	/* copy of string2 */
	for (length3 = 0; string2[length3] != '\0'; length3++)
	{
		resulte[length3] = string2[length3];
		length3++;
	}

	resulte[length2] = '\0';
	return (resulte);
}


/**
 * str_reverse - This function reverses a string.
 * @string: The pointer to a string.
 * Return: Okay -1 void.
 */
void str_reverse(char *string)
{

	int si = 0, lengthed = str_length(string) - 1;
	char holds;

	while (si < lengthed)
	{
		holds = string[si];
		string[si++] = string[lengthed];
		string[lengthed--] = holds;
	}
}
