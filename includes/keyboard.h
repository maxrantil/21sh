/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/14 15:22:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "ft_21sh.h"
# include <termcap.h> //control if all these are needed
# include <term.h> //same same
# include <curses.h> //same same
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <ctype.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# define DEL		0
# define BCK		1
# define CTRL_C		3
# define CTRL_D		4
# define D_QUO	34
# define S_QUO	39
# define ESCAPE     27
# define ENTER      10
# define DOWN		261
# define UP			262
# define LEFT       263
# define RIGHT      264
# define BACKSPACE	127
# define TAB		9

# define PROMPT "$> "
# define MINI_PROMPT "> "

# define BUFFSIZE   2048

typedef struct s_term
{
	int		ch;
	char	inp[BUFFSIZE];
	char	quote;
	t_vec	v_history;
	ssize_t	q_qty;
	ssize_t	ws_col;
	ssize_t	ws_row;
	ssize_t	index;
	ssize_t	bytes;
	ssize_t	c_col;
	ssize_t	c_row;
	ssize_t	start_row;
	ssize_t	total_row;
	ssize_t	prompt_len;
	ssize_t	m_prompt_len;
	char	**nl_addr;
	char	*input_cpy;
	ssize_t	total_row_cpy;
}			t_term;

void	ft_init(t_term *t);
t_term	*ft_input_cycle(t_term *t);
void	ft_restart_cycle(t_term *t);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(ssize_t col, ssize_t row);
void	ft_run_capability(char *cap);
void	ft_window_size(t_term *t);
void	ft_init_signals(void);
int		ft_get_linenbr(void);
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row);

/*				History				*/
void	ft_history(t_term *t);
void	ft_history_get(t_term *t);
void	ft_history_write_to_file(t_term *t);
void	ft_history_trigger(t_term *t, ssize_t his);

/*		    Cursor Movement			*/
void	ft_opt_mv(t_term *t);
void	ft_line_mv(t_term *t);
void	ft_word_mv(t_term *t);

/*		  Printing to Display		*/
ssize_t	ft_display_row(t_term *t, ssize_t c_row);
void	ft_print_trail(t_term *t);

/*		   New Line Mangement		*/
void	ft_shift_nl_addr(t_term *t, int num);
ssize_t	get_last_non_prompt_line(t_term *t);
ssize_t	ft_get_prompt_len(t_term *t, ssize_t row);
void	nl_addr_reset(t_term *t);
void	ft_remove_nl_addr(t_term *t, ssize_t row);
void	ft_reset_nl_addr(t_term *t);
char	*ft_is_prompt_line(t_term *t, ssize_t row);
void	nl_terminal_size(t_term *t);
void	ft_add_nl_last_row(t_term *t, ssize_t pos);
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos);

/*		     Quote Handling 		*/
void	ft_quote_handling(t_term *t, char ch);
void	ft_quote_decrement(t_term *t, int num);

/*		        Deletion	 		*/
ssize_t	ft_row_lowest_line(t_term *t);
void	ft_delete(t_term *t);
void	ft_backspace(t_term *t);
void	ft_deletion_shift(t_term *t, int mode);

/*		       Insertion	 		*/
int		ft_get_input(void);
void	ft_insertion(t_term *t);
void	ft_arrow_input(t_term *t);
void	ft_esc_parse(t_term *t);
void	ft_create_prompt_line(t_term *t, ssize_t loc);

ssize_t	ft_display_row_v2(t_term *t, ssize_t c_row);

#endif
