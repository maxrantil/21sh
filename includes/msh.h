/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/02 11:06:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <dirent.h>
# include <sys/stat.h>
# if __linux__
# include <sys/types.h>
# include <sys/wait.h>
# endif

# define MAX_PATHLEN 1024
# define MAX_NAME 256
# define HASH_SIZE 25

typedef struct s_msh
{
	char	**args;
	char	**env;
	char	**temp_env;
	char	**paths;
	char	*cl;
}			t_msh;

typedef struct s_builtin {
	char				*program;
	int					(*function)(t_msh *msh);
	struct s_builtin	*next;
}						t_builtin;

/* Function Declarations for builtin */
int		msh_cd(t_msh *msh);
int		msh_echo(t_msh *msh);
int		msh_env(t_msh *msh);
int		msh_setenv(t_msh *msh);
int		msh_unsetenv(t_msh *msh);
int		msh_exit(t_msh *msh);
char	*extract_key(char *key_value);

/* Hash table */
size_t	hash_function(char *program);
void	initialize_ht(t_builtin **ht);

/* Parser */
int		parser(t_msh *msh);
size_t	count_arguments(char *str);
char	**get_arguments(char *str, size_t argc);
void	strip_quotes(char **args);
void	expansions(t_msh *msh);
size_t	find_matching_quote(char *str, char quote);

/* Main */
void	init(t_msh *msh);
void	free_mem(t_msh *msh, t_builtin **ht,ssize_t code);

/* Change envirionment variables */
char	*get_env_value(char **env, char *var);
char	**update_env_underscore(t_msh *msh);
char	**update_pwd(t_msh *msh, char *oldcwd);
char	**set_env_var(char **env, char *key, char *value);
char	**unset_env_var(char **env, char *key);
void	get_dollar(t_msh *msh, char *dollar, size_t i);
void	tilde(t_msh *msh, size_t i);
void	loop_setenv(t_msh *msh, char *arg);

/* Utils */
int		msh_launch(t_msh *msh);
void	print_error(char *arg, int i);

#endif
