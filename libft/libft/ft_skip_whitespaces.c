#include "libft.h"

char	*ft_skip_whitespaces(char *ptr)
{
	while (*ptr && ft_isspace((const char *)ptr))
		ptr++;
	return (ptr);
}
