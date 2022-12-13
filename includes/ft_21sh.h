/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/13 15:07:35 by rvuorenl         ###   ########.fr       */
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

typedef struct s_hash
{
	char			*program;
	int				hits;
	struct s_hash	*next;
}					t_hash;

typedef struct s_shell
{
	struct termios	orig_termios;
	struct termios	raw;
	t_vec			v_tmp_env;
	t_hash			**ht;
	char			**temp_env;
	char			**env;
	char			**paths;
	char			*cl;
	char			*terminal_name;
}					t_shell;

typedef struct s_node
{
	int				type;
	char			**arg;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

/* Aggregation */
void	check_file_aggregations(t_node *n, t_shell *sh);
int		check_filename_fd(char *filename);
int		check_operator_errors(int old, int file_fd, char *filename, char *oper);
int		dup2_wrap(int file_fd, int old_fd);
int		open_check(char *filename, int mode);
int		redirect_aggregate(int old_fd, char *target, char *operator);
int		syntax_error_msg(int exit_code);

/* Builtin */
char	*env_getvalue(char **env, char *var);
char	*env_key_extract(char *key_value);
char	**env_underscore(t_node *n, t_shell *sh);
int		sh_cd(t_node *n, t_shell *sh);
int		sh_echo(t_node *n, t_shell *sh);
int		sh_env(t_node *n, t_shell *sh);
int		sh_exit(t_node *n, t_shell *sh);
int		sh_hash(t_node *n, t_shell *sh);
int		sh_setenv(t_node *n, t_shell *sh);
int		sh_unsetenv(t_node *n, t_shell *sh);
char	**pwd_update(t_shell *sh, char *oldcwd);
void	setenv_loop(t_shell *sh, char *arg, int flag_temp);
char	**setenv_var(char **env, char *key, char *value);
char	**unsetenv_var(char **env, char *key);

/* Error */
t_node	*exec_error(t_node *n, int type);
void	sh_error_print(char *arg, int i);

/* Exec */
int		check_paths(t_shell *sh);
int		exec_21sh(t_node *n, t_shell *sh);
void	exec_pipe_node(t_node *n, t_shell *sh);
int		exec_tree(t_node *n, t_shell *sh);
int		fork_wrap(void);
void	input_file_read(t_node *n, t_shell *sh);
void	redirection_file(t_node *n, t_shell *sh);
void	strip_quotes(t_node *n, t_shell *sh);

/* Expansions */
void	expansions_dollar(t_node *n, t_shell *sh, char *dollar, size_t i);
void	expansions_tilde(t_node *n, t_shell *sh, size_t i);
void	expansions(t_node *n, t_shell *sh);
ssize_t	find_matching_quote(char *str, char quote);
void	fill_env(char **tmp, char **cont, size_t *env_len, char *str);
void	loop_conversions_quotes(t_node *n, t_shell *sh);
void	remove_backslash(char *str);
size_t	strip_quotes_double(char **str, size_t quote1);
size_t	strip_quotes_single(char *str, size_t quote1);
size_t	update_arg_dollar(int i, char **str, size_t *len, size_t *q2);

/* Hash table */
size_t	hash_function(char *program);
void	hash_init(t_shell *sh);
void	hash_print(t_hash **ht);
void	init_ht_struct(t_shell *sh, char *str);

/* Main */
char	*ft_heredoc(t_term *t);
char	**get_env(char **env);
void	init(t_shell *sh, t_term *t);
void	print_banner(void);
void	tree_free(t_node *n);

/* Parser */
void	add_to_args(char ***array, char *str);
int		check_for_fileagg(char *tok);
t_node	*error_redir(t_node *n, char **ptr_to_line);
int		get_fd_before(char *tok);
void	mv_tok_and_line(char **tok, char ***ptr_to_line, int len);
t_node	*node_create(int type, t_node *left, t_node *right);
t_node	*parse_exec(char **ptr_to_line);
t_node	*parse_line(char **ptr_to_line);
t_node	*parse_pipe(char **ptr_to_line);
t_node	*parse_redirection(t_node *n, char **ptr_to_line);
int		peek(char **ptr_to_line, char *toks);
void	redir_node_add_args(t_node *n, char ***ptr_to_line, \
char **tok, int len);
int		tok_get(char **ptr_to_line, char **tok, char **end_q);

/* Utils */
void	free_mem(t_node *n, t_shell *sh, ssize_t code);
void	ft_disable_raw_mode(t_shell *sh);
void	ft_enable_raw_mode(t_shell *sh);
void	reset_fds(char *terminal_name);
void	tree_print(t_node *root);

typedef int			(*t_fptr)(t_node *n, t_shell *sh);

static const char	*g_builtin_str[] __attribute__((unused)) = {
	"cd",
	"echo",
	"env",
	"exit",
	"hash",
	"setenv",
	"unsetenv"
};

static const t_fptr	g_builtin_func[] = {
	&sh_cd,
	&sh_echo,
	&sh_env,
	&sh_exit,
	&sh_hash,
	&sh_setenv,
	&sh_unsetenv
};

#endif
