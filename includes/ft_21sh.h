/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 15:40:05 by rvuorenl         ###   ########.fr       */
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

# if __linux__
# include <sys/types.h>
# include <sys/wait.h>
# endif

/* Exec Node */
# define EXEC 1
/* | */
# define PIPE 2
/* > */
# define REDIROVER 3
/* >> */
# define REDIRAPP 4
/* < */
# define REDIRIN 5
/* >& */
# define FILEAGG 6
/* & */
# define AMP 7
/* ; */
# define SEMI 8
/* Tree Print */
# define COUNT 10
/* Hash Table */
# define HASH_SIZE 25
/* Unix */
# define MAX_PATHLEN 1024

typedef struct s_msh
{
	t_vec	v_tmp_env;
	char	**temp_env;
	char	**env;
	char	**paths;
	char	*cl;
}			t_shell;

typedef struct s_node
{
	int				type;
	char			**arg;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct	s_hash
{
	char			*program;
	int				(*function)(t_node *n, t_shell *sh);
	struct s_hash	*next;
}					t_hash;

/* Aggregation */
void	check_file_aggregations(char *full, char *filename);
int		check_filename_fd(char *filename);
void	check_operator_errors(int file_fd, char *filename, char *operator);
int		dup2_check2(int file_fd, int old_fd);
int		get_redirected_fd(char *full);
char	*get_redirect_operator(char *full);
int		get_target_fd(char *filename);
char	*get_target_file(char *full, char *filename, size_t oper_len);
int		open_check(char *filename, int mode);
void	syntax_error_msg(int exit_code);

/* Builtin */
char	*env_getvalue(char **env, char *var);
char	*env_key_extract(char *key_value);
char	**env_underscore(t_node *n, t_shell *sh);
int		msh_cd(t_node *n, t_shell *sh);
int		msh_echo(t_node *n, t_shell *sh);
int		msh_env(t_node *n, t_shell *sh);
int		msh_setenv(t_node *n, t_shell *sh);
int		msh_unsetenv(t_node *n, t_shell *sh);
int		msh_exit(t_node *n, t_shell *sh);
char	**pwd_update(t_shell *sh, char *oldcwd);
void	setenv_loop(t_shell *sh, char *arg, int flag_temp);
char	**setenv_var(char **env, char *key, char *value);
char	**unsetenv_var(char **env, char *key);

/* Error */
void	error_print(char *arg, int i);

/* Exec */
void	check_file_aggregations(char *full, char *filename);
int		dup2_check(int file_fd);
int		exec_21sh(t_node *n, t_shell *sh, t_hash **ht);
void	exec_pipe_node(t_node *n, t_shell *sh, t_hash **ht);
int		exec_tree(t_node *n, t_shell *sh, t_hash **ht);
int		fork_wrap(void);
void	input_file_read(char *filename);
void	redirection_file(t_node *n, t_shell *sh, t_hash **ht);
void	strip_quotes(char **args);

/* Expansions */
void	expansions_dollar(t_node *n, t_shell *sh, char *dollar, size_t i);
void	expansions_tilde(t_node *n, t_shell *sh, size_t i);
void	expansions(t_node *n, t_shell *sh);

/* Hash table */
size_t	hash_function(char *program);
void	hash_init(t_hash ***ht);

/* Lexer */
char	*lexer(char *str);

/* Main */
void	free_mem(t_node *n, t_shell *sh, t_hash **ht,ssize_t code);
void	init(t_shell *sh, t_term *t, t_hash ***ht);
// void	init(t_shell *sh, t_term *t, t_hash ***ht, int argc, char **argv);
void	tree_free(t_node *n);

/* Parser */
// size_t	count_arguments(char *str);
// char	**get_arguments(char *str, size_t argc);
// int		parser(t_shell *sh);
void 	add_to_args(char ***array, char *str);
t_node	*node_create(int type, t_node *left, t_node *right);
t_node	*parse_exec(char **ptr_to_line);
t_node	*parse_line(char **ptr_to_line);
t_node	*parse_pipe(char **ptr_to_line);
t_node	*parse_redirection(t_node *n, char **ptr_to_line);
int		peek(char **ptr_to_line, char *toks);
int		token_get(char **ptr_to_line, char **token, char **end_q);

/* Utils */
void	hash_print(t_hash **ht);
void	tree_print(t_node *root);

#endif
