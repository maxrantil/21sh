/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/15 14:14:53 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "vec.h"
# include "keyboard.h"
# include <dirent.h>
# include <sys/stat.h>

/* from lexer */
# include <stdio.h>
# include <stdlib.h>

# if __linux__
# include <sys/types.h>
# include <sys/wait.h>
# endif

# define MAX_PATHLEN 1024
# define MAX_NAME 256
# define HASH_SIZE 25

/* from lexer */
# define COUNT 10
# define EXEC 1
# define PIPE 2
# define REDIROVER 3 // >
# define REDIRAPP 4 // >>
# define REDIRIN 5 // <
# define AMP 6
# define SEMI 7

typedef struct s_msh
{
	t_vec	v_temp;
	char	**args; //take away
	char	**env;
	char	**temp_env;
	char	**paths;
	char	*cl; // take away
}			t_msh;

typedef struct s_node
{
	int				type;
	char			*arg[100];
	struct s_node	*command;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_builtin {
	char				*program;
	int					(*function)(t_node *node, t_msh *msh);
	struct s_builtin	*next;
}
						t_builtin;

/* Builtin */
char	*env_getvalue(char **env, char *var);
char	*env_key_extract(char *key_value);
char	**env_underscore(t_msh *msh);
int		msh_cd(t_node *node, t_msh *msh);
int		msh_echo(t_node *node, t_msh *msh);
int		msh_env(t_node *node, t_msh *msh);
int		msh_setenv(t_node *node, t_msh *msh);
int		msh_unsetenv(t_node *node, t_msh *msh);
int		msh_exit(t_node *node, t_msh *msh);
char	**pwd_update(t_msh *msh, char *oldcwd);
void	setenv_loop(t_msh *msh, char *arg, int flag_temp);
char	**setenv_var(char **env, char *key, char *value);
char	**unsetenv_var(char **env, char *key);

/* Hash table */
size_t	hash_function(char *program);
void	hash_init(t_builtin **ht);

/* Parser */
// size_t	count_arguments(char *str);
// void	expansions(t_msh *msh);
// ssize_t	find_matching_quote(char *str, char quote);
// char	**get_arguments(char *str, size_t argc);
// void	get_dollar(t_msh *msh, char *dollar, size_t i);
// int		parser(t_msh *msh);
// void	strip_quotes(char **args);
// void	tilde(t_msh *msh, size_t i);
int		peek(char **ptr_to_str, char *toks);
int		token_get(char **ptr_to_str, char **token, char **end_q);
t_node	*node_create(int type, t_node *sub_cmd, t_node *left, t_node *right);
t_node	*parse_redirection(t_node *node, char **str);
t_node	*parse_exec(char **ptr_to_str);
t_node	*parse_pipe(char **ptr_to_str);
t_node	*parse_line(char **ptr_to_str);

/* Main */
void	init(t_msh *msh);
void	free_mem(t_msh *msh, t_builtin **ht,ssize_t code);
void	tree_free(t_node *node);

/* Utils */
void	hash_print(t_builtin **ht);
int		msh_launch(t_node *node, t_msh *msh);
void	print_error(char *arg, int i);
void	tree_print(t_node *root);

/* Lexer */
char	*lexer(char *str);

/* Exec */
int		exec_tree(t_node *node, t_msh *msh, t_builtin **ht);
void	exec_pipe_node(t_node *node);
int		fork_check(void);
void	exec_pipe_node(t_node *node);
void	redirection_file(t_node *node);
void	rec_print_tree(t_node *root, int lvl);
void	input_file_read(char *filename);
int		dup2_check(int file_fd);

#endif
