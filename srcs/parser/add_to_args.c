#include "ft_21sh.h"

static char	**malloc_wrap(size_t size)
{
	char	**arr;

	arr = (char **)malloc(size);
	if (!arr)
	{
		ft_putendl_fd("error: malloc", 2);
		exit(1);
	}
	return (arr);
}

void 	add_to_args(char ***array, char *str)
{
	int 	i;
	char	**new_array;

	if (!str)
		return ;
	if (*array == NULL)
	{
		*array = malloc_wrap(sizeof(char *) * 2);
		(*array)[0] = str;
		(*array)[1] = NULL;
		return ;
	}
	i = 0;
	while ((*array)[i])
		i++;
	new_array = malloc_wrap(sizeof(char *) * (i + 2));
	i = 0;
	while ((*array)[i])
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free(*array);
	*array = new_array;
}