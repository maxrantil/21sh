#include "parser.h"

// one backslag take it away, two backslshes keep one. last newline is always changes to \0
char *lexer(char *str)
{
	int i = 0;
	int j = 0;
	char *new;

	new = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		new[j++] = str[i++];
	}
	new[j - 1] = '\0';
	return (new);
}
