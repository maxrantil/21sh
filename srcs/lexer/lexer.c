#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (&((char *)s)[i]);
	return (NULL);
}

static int	ft_isspace(const char *str) //take away
{
	if ((*str >= 9 && *str <= 13) || *str == 32)
		return (1);
	return (0);
}

static char	*skip_whitespaces(char *ptr) // take away
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

static char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = (char *)malloc(sizeof(char) * len + 1);
	if (!ss)
		return (NULL);
	while (len--)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}


int	peek(char **ps, char *es, char *toks)
{
	char *p;

	p = *ps;
	while (p < es && ft_isspace((const char *)p))
		p++;
	*ps = p;
	return (*p && ft_strchr(toks, *p));
}

//make funtion greater_then()
int	get_token(char **next_token, char **token, char **end_q)
{
	char	*p;
	int		ret;
	
	p = *next_token;
	p = skip_whitespaces(p);
	if (*p == '\0')
		return (0);
	if (token)
		*token = p;
	ret = *p;
	while (*p)
	{
		if (strchr("<|&;", *p))
		{
			p++;
			break ;
		}
		else if (*p == '>')
		{
			p++;
			if (*p == '>')
			{
				ret = '#';
				p++;
			}
			break ;
		}
		else
		{
			ret = 'a';
			while (*p && !ft_isspace(p) && !strchr("<|&;>", *p))
				p++;
			break ;
		}
	}
	if (end_q)
		*end_q = p;
	p = skip_whitespaces(p);
	*next_token = p;
	return (ret);
}

typedef struct s_node
{
	int				type;
	char			*exec[15];
	char			*symbol[15];
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

t_node *parse_exec(char **str)
{
	char *token;
	char *end_q;
	size_t	t = 0;
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	memset(node, 0, sizeof(t_node));
	while (**str && !peek(str, *str + strlen(*str), "<|&>#;"))
	{
		int ret = get_token(str, &token, &end_q);
		if (ret == 'a')
		{
			node->type = 1;
			node->exec[t] = ft_strsub(token, 0, end_q - token);
			t++;
		}	
	}
	node->exec[t] = NULL;
	return (node);
}

t_node *parse_symbol(t_node *root, char **str)
{
	char *token;
	char *end_q;
	size_t	y = 0;
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	memset(node, 0, sizeof(t_node));

	while (peek(str, *str + strlen(*str), "<|&>#;"))
	{
		int ret = get_token(str, &token, &end_q);
		if (ret == '|' || ret == '&' || ret == ';' || ret == '#' || ret == '<' || ret == '>')
		{
			node->type = 2;
			node->symbol[y] = ft_strsub(token, 0, end_q - token);


			y++;
		}	
	}
	node->symbol[y] = NULL;
	return (node);
}

int main()
{
	char	*str = "ls -la -F | grep a.out";
	t_node	*node;
	
	node = parse_exec(&str);
	for (int i = 0; node->exec[i]; i++)
	{
		printf("arg[%d]: %s\n", i, node->exec[i]);
	}
	node = parse_symbol(node, &str);
	for (int i = 0; node->symbol[i]; i++)
	{
		printf("symbol: %s\n", node->symbol[i]);
	}
	node = parse_exec(&str);
	for (int i = 0; node->exec[i]; i++)
	{
		printf("arg[%d]: %s\n", i, node->exec[i]);
	}
	return (0);
}