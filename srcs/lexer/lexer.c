#include "ft_21sh.h"

// one backslag take it away, two backslshes keep one. (last newline is always changes to \0, NOT)
char *lexer(char *str)
{
	int i = 0;
	int j = 0;
	char *new;

	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] && str[i] == '\\')
			i++;
		new[j++] = str[i++];
	}
	return (new);
}
