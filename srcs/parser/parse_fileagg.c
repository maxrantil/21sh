#include "ft_21sh.h"

t_node	*parse_fileagg(t_node *n, char **ptr_to_line)
{
	char *token;
	char *end_q;

	if (token_get(ptr_to_line, &token, &end_q) != 'a' && '&' != *token)
	{
		ft_putstr_fd("fileagg syntax error near unexpected token `", 2); // make better error handling for `echo hello >`
		ft_putchar_fd(*token, 2);
		ft_putendl_fd("'", 2);
		tree_free(n);
		return (NULL);
	}
	ft_printf("1token: %s\n", token);
	if (ft_strcspn("<>", token) && ft_strchr(token, '&'))
	{
		n = node_create(FILEAGG, n, NULL);
		// add_to_args(&n->arg, ft_strsub(token, 0, (size_t)((end_q - token)));
		add_to_args(&n->arg, ft_strdup(token));
		token_get(ptr_to_line, &token, &end_q);
		// token_get(ptr_to_line, &token, &end_q);
	}
	return (n);
}
