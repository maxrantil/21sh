#ifndef PARSER_H
# define PARSER_H

# include "ft_21sh.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

#define COUNT 10
#define EXEC 1
#define PIPE 2
#define REDIROVER 3 // >
#define REDIRAPP 4 // >>
#define REDIRIN 5 // <
#define AMP 6
#define SEMI 7

typedef struct s_node
{
	int				type;
	char			*arg[100];
	struct s_node	*command;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

int		peek(char **ptr_to_str, char *toks);
int		get_token(char **ptr_to_str, char **token, char **end_q);
t_node	*create_node(int type, t_node *sub_cmd, t_node *left, t_node *right);
t_node	*parse_redirection(t_node *node, char **str);
t_node *parse_exec(char **ptr_to_str);
t_node	*parse_pipe(char **ptr_to_str);
t_node	*parse_line(char **ptr_to_str);
void	exec_tree(t_node *node);
void	exec_pipe_node(t_node *node);
int		fork_check(void);
void	exec_pipe_node(t_node *node);
int		open_check(char *filename, int mode);
void	redirection_file(t_node *node);
void	rec_print_tree(t_node *root, int lvl);
void	print_tree(t_node *root);
int		open_read_check(char *filename);
void	input_file_read(char *filename);
int		dup2_check(int file_fd);

#endif
