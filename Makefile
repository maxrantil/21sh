# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2023/01/10 10:32:12 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
SHELL := /bin/bash
GREEN = \033[32m
GREEN_BACKGROUND = \033[42m
WHITE_BACKGROUND = \033[47m
VIOLET_BACKGROUND = \033[0;45m
YELLOW_BACKGROUND = \033[0;43m
WHITE = \033[37m
YELLOW = \033[33m
BLACK = \033[30m
VIOLET = \033[35m
RESET = \033[0m
RED = \033[31m
CYAN = \033[36m
BOLD = \033[1m

#PRINTING TOOLS
ERASE_LINE = \033[K
UP = A
DOWN = B
RIGHT = C
LEFT = D
MOVE = \033[
C_INVISIBLE = \033[?25l
C_VISIBLE = \033[?25h

MAKEFLAGS	+= --no-print-directory

NAME		=	21sh
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra
CFLAGS		+=	-Wunreachable-code -Wtype-limits
CFLAGS		+=	-Wpedantic
CFLAGS		+=	-O3

LEAK_CHECK	=	-g
#LEAK_CHECK	+=	-fsanitize=address

UNAME		= $(shell uname)
ifeq ($(UNAME), Darwin)
TERMCAP		=	-ltermcap
CFLAGS		+= 	-Werror
endif
ifeq ($(UNAME), Linux)
TERMCAP		=	-lncurses
endif

SOURCES 	= 	srcs
AGG			= 	aggregation/
BUILTIN		= 	builtin/
ERROR		= 	error/
EXEC		= 	exec/
EXPANSIONS	= 	expansions/
KEYBOARD	= 	keyboard/
MAIN		= 	main/
PARSER		= 	parser/
UTILS		= 	utils/
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	ft_21sh \
				keyboard

FILES 		=	$(AGG)check_file_aggregations \
				$(AGG)check_filename_fd \
				$(AGG)check_operator_errors \
				$(AGG)open_check \
				$(AGG)redirect_aggregate \
				$(AGG)syntax_error_msg \
				$(BUILTIN)env_getvalue \
				$(BUILTIN)env_underscore \
				$(BUILTIN)pwd_update \
				$(BUILTIN)env_key_extract \
				$(BUILTIN)setenv_loop \
				$(BUILTIN)setenv_var \
				$(BUILTIN)sh_cd \
				$(BUILTIN)sh_echo \
				$(BUILTIN)sh_env \
				$(BUILTIN)sh_exit \
				$(BUILTIN)sh_history \
				$(BUILTIN)sh_unsetenv \
				$(BUILTIN)sh_setenv \
				$(BUILTIN)unsetenv_var \
				$(ERROR)error_redir \
				$(ERROR)exec_error \
				$(ERROR)sh_error_print \
				$(EXEC)check_paths \
				$(EXEC)exec_21sh \
				$(EXEC)exec_pipe_node \
				$(EXEC)exec_tree \
				$(EXEC)fork_wrap \
				$(EXEC)input_file_read \
				$(EXEC)redirection_file \
				$(EXPANSIONS)expansions_tilde \
				$(EXPANSIONS)fill_env \
				$(EXPANSIONS)find_matching_quote \
				$(EXPANSIONS)get_full_env_name \
				$(EXPANSIONS)loop_conversions_quotes \
				$(EXPANSIONS)remove_backslash \
				$(EXPANSIONS)strip_quotes_double \
				$(EXPANSIONS)strip_quotes_single \
				$(EXPANSIONS)update_arg_dollar \
				$(EXPANSIONS)expansions_dollar \
				$(EXPANSIONS)expansions \
				$(KEYBOARD)ft_add_nl_last_row \
				$(KEYBOARD)ft_add_nl_mid_row \
				$(KEYBOARD)ft_alt_mv \
				$(KEYBOARD)ft_arrow_input \
				$(KEYBOARD)ft_backspace \
				$(KEYBOARD)ft_bslash_escape_check \
				$(KEYBOARD)ft_copy \
				$(KEYBOARD)ft_create_prompt_line \
				$(KEYBOARD)ft_ctrl \
				$(KEYBOARD)ft_cut \
				$(KEYBOARD)ft_delete \
				$(KEYBOARD)ft_deletion_shift \
				$(KEYBOARD)ft_delim_fetch \
				$(KEYBOARD)ft_end_cycle \
				$(KEYBOARD)ft_get_file \
				$(KEYBOARD)ft_esc_parse \
				$(KEYBOARD)ft_quote_flag_reset \
				$(KEYBOARD)ft_get_input \
				$(KEYBOARD)ft_get_prompt_len \
				$(KEYBOARD)ft_getline_nbr \
				$(KEYBOARD)ft_heredoc_handling \
				$(KEYBOARD)ft_history_add_command \
				$(KEYBOARD)ft_history_get \
				$(KEYBOARD)ft_history_reset_nl \
				$(KEYBOARD)ft_history_trigger \
				$(KEYBOARD)ft_history_write_to_file \
				$(KEYBOARD)ft_history \
				$(KEYBOARD)ft_init_signals \
				$(KEYBOARD)ft_init_term \
				$(KEYBOARD)ft_input_cycle \
				$(KEYBOARD)ft_insertion \
				$(KEYBOARD)ft_is_prompt_line \
				$(KEYBOARD)ft_len_lowest_line \
				$(KEYBOARD)ft_line_down \
				$(KEYBOARD)ft_line_mv \
				$(KEYBOARD)ft_line_up \
				$(KEYBOARD)ft_mv_prompt_len \
				$(KEYBOARD)ft_nl_removal \
				$(KEYBOARD)ft_paste \
				$(KEYBOARD)ft_print_input \
				$(KEYBOARD)ft_print_trail \
				$(KEYBOARD)ft_putc \
				$(KEYBOARD)ft_quote_decrement \
				$(KEYBOARD)ft_quote_flag_check \
				$(KEYBOARD)ft_quote_handling \
				$(KEYBOARD)ft_remove_nl_addr \
				$(KEYBOARD)ft_reset_nl_addr \
				$(KEYBOARD)ft_restart_cycle \
				$(KEYBOARD)ft_row_lowest_line \
				$(KEYBOARD)ft_run_capability \
				$(KEYBOARD)ft_set_new_cur_pos \
				$(KEYBOARD)ft_setcursor \
				$(KEYBOARD)ft_shift_insert \
				$(KEYBOARD)ft_shift_nl_addr \
				$(KEYBOARD)ft_trigger_nl \
				$(KEYBOARD)ft_window_size \
				$(KEYBOARD)ft_word_mv \
				$(MAIN)check_heredoc \
				$(MAIN)get_env \
				$(MAIN)init \
				$(MAIN)main \
				$(MAIN)print_banner \
				$(PARSER)add_to_args \
				$(PARSER)exec_is_quote_somewhere \
				$(PARSER)look_for_redir \
				$(PARSER)mv_tok_and_line \
				$(PARSER)node_create \
				$(PARSER)parse_exec \
				$(PARSER)parse_line \
				$(PARSER)parse_pipe \
				$(PARSER)parse_redirection \
				$(PARSER)peek \
				$(PARSER)redir_node_add_args \
				$(PARSER)tok_get \
				$(UTILS)dup2_wrap \
				$(UTILS)free_mem \
				$(UTILS)ft_disable_raw_mode \
				$(UTILS)ft_enable_raw_mode \
				$(UTILS)reset_fds \
				$(UTILS)tree_free \
				$(UTILS)tree_print \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
O_PATHS		=	$(addsuffix .o, $(addprefix $(OBJECTS)/,$(FILES)))
LIBS		= 	libft/libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ???$(RESET)" || (printf "$@ $(RED)$(BOLD)???$(RESET)\n\n" | printf "$(C_VISIBLE)" && exit 1)

all: libft $(NAME)

$(NAME): libft/libft.a $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(TERMCAP) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@printf "$(C_VISIBLE)"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)/$(AGG)
	@mkdir -p $(OBJECTS)/$(BUILTIN)
	@mkdir -p $(OBJECTS)/$(ERROR)
	@mkdir -p $(OBJECTS)/$(EXEC)
	@mkdir -p $(OBJECTS)/$(EXPANSIONS)
	@mkdir -p $(OBJECTS)/$(KEYBOARD)
	@mkdir -p $(OBJECTS)/$(MAIN)
	@mkdir -p $(OBJECTS)/$(PARSER)
	@mkdir -p $(OBJECTS)/$(UTILS)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS):	$(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)
	@make pbar

libft:
	@make -C $(LIBRARIES)
	@if [ "$(FOO)" = "" ]; then $(MAKE) FOO=bar; fi

clean:
	@make -C $(LIBRARIES) clean
	@if [ -d $(OBJECTS) ]; then rm -rf $(OBJECTS); printf "$(NAME):		$(RED)$(OBJECTS)/ was deleted$(RESET)\n"; fi

fclean: clean
	@make -C $(LIBRARIES) fclean
	@if [ -f $(LIBS) ]; then rm $(LIBS); fi
	@if [ -f $(NAME) ]; then rm -f $(NAME); printf "$(NAME):		$(RED)executable was deleted$(RESET)\n"; fi

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(shell find $(OBJECTS) -name '*.o')))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(GREEN)$(LOADED_COUNT)$(RESET) / $(BOLD)$(GREEN)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT); i++)); do\
		printf "$(GREEN_BACKGROUND) $(RESET)" ;\
	done ;
	@for ((i = 1; i <= 100 - ($(LOADED_COUNT) * 100 / $(SOURCE_COUNT)); i++)); do\
		printf "$(WHITE_BACKGROUND) $(RESET)" ;\
	done ;
	@printf "$(GREEN_BACKGROUND)$(BOLD)$(WHITE)$(MOVE)55$(LEFT)[$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT))).$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))%%]$(MOVE)54$(RIGHT)$(RESET)\n"

.PHONY: all libft clean fclean re
