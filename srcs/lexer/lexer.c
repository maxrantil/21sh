#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

size_t	ft_strcspn(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_strsep(char **str_ptr, const char *delim)
{
	char	*begin;
	char	*end;

	begin = *str_ptr;
	if (begin == NULL)
		return (NULL);
	end = begin + ft_strcspn(begin, delim);
	if (*end)
	{
		*end++ = '\0';
		*str_ptr = end;
	}
	else
		*str_ptr = NULL;
	return (begin);
}

//make funtion greater_then()

int	get_token(char **next_token)
{
	char	*token;
	int		ret;
	
	token = *next_token;
	token = skip_whitespaces(token);
	if (*token == '\0')
		return (0);
	ret = *token;
	while (*token)
	{
		if (strchr("<|&;", *token))
		{
			token++;
			break ;
		}
		else if (*token == '>')
		{
			token++;
			if (*token == '>')
			{
				ret = '#';
				token++;
			}
			break ;
		}
		else
		{
			ret = 'a';
			while (*token && !strchr(" \t\r\n\v", *token) && !strchr("<|&;>", *token))
				token++;
			break ;
		}
	}
	token = skip_whitespaces(token);
	*next_token = token;
	return (ret);
}

char *gettoken(char **str)
{
	char *token;

	if (!str || !*str)
		return (NULL);
	
	token = strdup(ft_strsep(str, "<|&;"));
	return (token);
}
int main()
{
	
	char str[] = "this is a pipe | and this is a < redirection";
	char *str_dup = (char *)malloc(sizeof(char) * strlen(str) + 1);
	if (!str_dup)
		return (0);
	strcpy(str_dup, str);
	/* char **arr = (char **)malloc(sizeof(char *) * (5 + 1));
	if (!arr)
		return (0);
	str_dup = str;
	int x;
	x = 0;
	printf("str_dup = %s\n", str_dup);
	while (str_dup)
	{
		printf("hello world\n");
		arr[x] = strdup(ft_strsep(&str_dup, "<|&;"));
		printf("arr: %s\n", arr[x]);
		printf("str: %s\n", str_dup);
		x++;
	}
	arr[x] = NULL;
	x = 0;
	while (arr[x])
	{
		printf("token: %s\n", arr[x]);
		x++;
	} */

	printf("token: %s\n", gettoken(&str_dup));
	printf("token: %s\n", gettoken(&str_dup));
	return (0);
	/* printf("[%c] %s\n", get_token(&str), str);
	printf("[%c] %s\n", get_token(&str), str); */
	/* printf("%s\n", str); */
}