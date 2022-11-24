#include "libft.h"

char	*ft_skip_whitespaces(char *ptr)
{
	if (!ptr)
		return (NULL);
	while (*ptr && ft_isspace((const char *)ptr))
		ptr++;
	return (ptr);
}
