#include "ft_21sh.h"

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

static int token_loop(char **p, int ret) //retname p to s
{
	while (**p)
	{
		if (strchr("<|&;", **p) && (*p)++)
			break ;
		else if (**p == '>' && (*p)++)
		{
			if (**p == '>' && (*p)++)
				ret = '#';
			break ;
		}
		else
		{
			ret = 'a';
			while (**p && !ft_isspace(*p) && !strchr("<|&;>", **p))
				(*p)++;
			break ;
		}
	}
	return (ret);
}

int	token_get(char **ptr_to_str, char **token, char **end_q)
{
	char	*p; //rename to scan
	int		ret;

	p = *ptr_to_str; //rename to inputptr
	p = skip_whitespaces(p);
	if (*p == '\0')
		return (0);
	if (token)
		*token = p;
	ret = *p;
	ret = token_loop(&p, ret);
	if (end_q)
		*end_q = p;
	p = skip_whitespaces(p);
	*ptr_to_str = p;
	return (ret);
}
