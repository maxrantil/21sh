#include "ft_21sh.h"

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

static int token_loop(char **scan, int ret) //retname scan to s
{
	while (**scan)
	{
		if (strchr("<|;", **scan) && (*scan)++) //took away '&'
			break ;
		else if (**scan == '>' && (*scan)++)
		{
			if (**scan == '>' && (*scan)++)
				ret = '#';
			break ;
		}
		else
		{
			ret = 'a';
			while (**scan && !ft_isspace(*scan) && !strchr("<|&;>", **scan))
				(*scan)++;
			break ;
		}
	}
	return (ret);
}

int	token_get(char **ptr_to_line, char **token, char **end_q)
{
	char	*scan;
	int		ret;

	scan = *ptr_to_line;
	scan = skip_whitespaces(scan);
	if (*scan == '\0')
		return (0);
	if (token)
		*token = scan;
	ret = *scan;
	ret = token_loop(&scan, ret);
	if (end_q)
		*end_q = scan;
	scan = skip_whitespaces(scan);
	*ptr_to_line = scan;
	return (ret);
}
