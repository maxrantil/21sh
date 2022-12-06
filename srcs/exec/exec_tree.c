#include "ft_21sh.h"

/* static int	exec_args(t_node *n, t_shell *sh, t_hash **ht)
{
	t_hash	*tmp;
	size_t	index;

	// expansions(n, sh);
	strip_quotes(n, sh);
	index = hash_function(n->arg[0]);
	tmp = ht[index];
	while (tmp)
	{
		if (ft_strcmp(n->arg[0], tmp->program) == 0)
		{
			sh->env = env_underscore(n, sh);
			return (tmp->function(n, sh));
		}
		tmp = tmp->next;
	}
	return (exec_21sh(n, sh, ht));
} */


static size_t	num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

static int	exec_args(t_node *n, t_shell *sh/* , t_hash **ht */)
{
	size_t	i;

	strip_quotes(n, sh);
	i = 0;
	
	while (i < num_builtins())
	{
		if (!ft_strcmp(n->arg[0], g_builtin_str[i]))
			return (g_builtin_func[i](n, sh));
		i++;
	}
	return (exec_21sh(n, sh/* , ht */));
}


int	exec_tree(t_node *n, t_shell *sh/* , t_hash **ht */)
{
	if (!n)
		return (1);
	if (n->type == EXEC && n->arg)
		return (exec_args(n, sh/* , ht */));
	else if (n->type == PIPE)
		exec_pipe_node(n, sh/* , ht */);
	else if (n->type == REDIROVER || n->type == REDIRAPP)
		redirection_file(n, sh/* , ht */);
	else if (n->type == REDIRIN) 		//here we need to change to fork like redirection_file
	{
		if (fork_wrap() == 0)
		{
			input_file_read(n->arg[1]);
			exit(EXIT_SUCCESS);
		}
		wait(0);
	}
	else if (n->type == FILEAGG)
		check_file_aggregations(n, sh/* , ht */);
	else if (n->type == AMP)
	{
		if (fork_wrap() == 0)
		{
			// exec_tree(n->left, sh, ht);
			execve(n->arg[0], n->arg, sh->env); //this is 42sh shit, make better error handling etc
			exit(EXIT_SUCCESS);
		}
	}
	else if (n->type == SEMI)
	{
		exec_tree(n->left, sh/* , ht */);
		exec_tree(n->right, sh/* , ht */);
	}
	return (1);
}
