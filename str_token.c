#include "shell.h"
/**
 * _strtok - This finction separates the  strings with delim
 * @line: This is a pointer to array we get in getline.
 * @delim: This is the characters we take off string in part.
 * Return: 0 always good boy excellent
*/
char *_strtok(char *line, char *delim)
{
	int ij;
	static char *strf;
	char *copystrs;

	if (line != NULL)
		strf = line;
	for (; *strf != '\0'; strf++)
	{
		for (ij = 0; delim[ij] != '\0'; ij++)
		{
			if (*strf == delim[ij])
			break;
		}
		if (delim[ij] == '\0')
			break;
	}
	copystrs = strf;
	if (*copystrs == '\0')
		return (NULL);
	for (; *strf != '\0'; strf++)
	{
		for (ij = 0; delim[ij] != '\0'; ij++)
		{
			if (*strf == delim[ij])
			{
				*strf = '\0';
				strf++;
				return (copystrs);
			}
		}
	}
	return (copystrs);
}
