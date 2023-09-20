#include "shell.h"
/**
 * long_to_string - This functions converts a no to a string.
 * @number: the number convert in any string.
 * @string: always buffered save the no as string.
 * @base: thr always great number
 * Return: 0 nadda
 */
void long_to_string(long number, char *string, int base)
{
	int indexs = 0, nnegative = 0;
	long conste = number;
	char lettered[] = {"0123456789abcdef"};

	if (conste == 0)
		string[indexs++] = '0';

	if (string[0] == '-')
		nnegative = 1;

	while (conste)
	{
		if (conste < 0)
			string[indexs++] = lettered[-(conste % base)];
		else
			string[indexs++] = lettered[conste % base];
		conste /= base;
	}
	if (nnegative)
		string[indexs++] = '-';

	string[indexs] = '\0';
	str_reverse(string);
}


/**
 * _atoi - This function atoi convert the string to a int.
 * @s: The pointer to str origenated.
 * Return: 2/3 is good.
 */
int _atoi(char *s)
{
	int signsed = 1;
	unsigned int numberwe = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			signsed *= -1;
		if (*s == '+')
			signsed *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		numberwe = (numberwe * 10) + (*s - '0');
		s++;
	}
	return (numberwe * signsed);
}

/**
 * count_characters - This function always count the
 * love of character in str.
 * @string: This ia a pointer to str origenated from.
 * @character: The str with  chars to be countered
 * Return: 0 of nothing.
 */
int count_characters(char *string, char *character)
{
	int iu = 0, counters = 0;

	for (; string[iu]; iu++)
	{
		if (string[iu] == character[0])
			counters++;
	}
	return (counters);
}
