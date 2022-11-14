# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/11/14 13:45:33 by mrantil          ###   ########.fr        #
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
CFLAGS		+=	-Wpedantic -Wconversion
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
PARSER		= 	parser/
HASH_TABLE	=	hash_table/
BUILTIN		= 	builtin/
MAIN		= 	main/
UTILS		= 	utils/
KEYBOARD	= 	keyboard/
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	ft_21sh

FILES 		= 	$(BUILTIN)builtin_cd \
				$(BUILTIN)builtin_echo \
				$(BUILTIN)builtin_env \
				$(BUILTIN)builtin_exit \
				$(BUILTIN)builtin_unsetenv \
				$(BUILTIN)builtin_setenv \
				$(BUILTIN)extract_key \
				$(BUILTIN)loop_setenv \
				$(BUILTIN)set_env_var \
				$(BUILTIN)unset_env_var \
				$(BUILTIN)update_pwd \
				$(MAIN)free_mem \
				$(MAIN)init \
				$(MAIN)main \
				$(HASH_TABLE)hash_function \
				$(HASH_TABLE)initialize_ht \
				$(PARSER)get_dollar \
				$(PARSER)tilde \
				$(PARSER)expansions \
				$(PARSER)count_arguments \
				$(PARSER)get_arguments \
				$(PARSER)strip_quotes \
				$(PARSER)parser \
				$(PARSER)find_matching_quote \
				$(UTILS)msh_launch \
				$(UTILS)get_env_value \
				$(UTILS)print_error \
				$(UTILS)update_env_underscore \
				$(KEYBOARD)ft_add_nl_last_row \
				$(KEYBOARD)ft_add_nl_mid_row \
				$(KEYBOARD)ft_arrow_input \
				$(KEYBOARD)ft_backspace \
				$(KEYBOARD)ft_create_prompt_line \
				$(KEYBOARD)ft_delete \
				$(KEYBOARD)ft_deletion_shift \
				$(KEYBOARD)ft_display_row \
				$(KEYBOARD)ft_esc_parse \
				$(KEYBOARD)ft_get_input \
				$(KEYBOARD)ft_get_prompt_len \
				$(KEYBOARD)ft_history_get \
				$(KEYBOARD)ft_history_trigger \
				$(KEYBOARD)ft_history_write_to_file \
				$(KEYBOARD)ft_history \
				$(KEYBOARD)ft_init_signals \
				$(KEYBOARD)ft_init \
				$(KEYBOARD)ft_input_cycle \
				$(KEYBOARD)ft_insertion \
				$(KEYBOARD)ft_is_prompt_line \
				$(KEYBOARD)ft_line_mv \
				$(KEYBOARD)ft_opt_mv \
				$(KEYBOARD)ft_print_trail \
				$(KEYBOARD)ft_getline_nbr \
				$(KEYBOARD)ft_putc \
				$(KEYBOARD)ft_quote_decrement \
				$(KEYBOARD)ft_quote_handling \
				$(KEYBOARD)ft_remove_nl_addr \
				$(KEYBOARD)ft_reset_nl_addr \
				$(KEYBOARD)ft_row_lowest_line \
				$(KEYBOARD)ft_run_capability \
				$(KEYBOARD)ft_setcursor \
				$(KEYBOARD)ft_shift_nl_addr \
				$(KEYBOARD)ft_window_size \
				$(KEYBOARD)ft_word_mv \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
O_PATHS		=	$(addsuffix .o, $(addprefix $(OBJECTS)/,$(FILES)))
LIBS		= 	libft/libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✓$(RESET)" || (printf "$@ $(RED)$(BOLD)✘$(RESET)\n\n" | printf "$(C_VISIBLE)" && exit 1)

all: libft $(NAME)

$(NAME): libft/libft.a $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(TERMCAP) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@printf "$(C_VISIBLE)"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)/$(PARSER)
	@mkdir -p $(OBJECTS)/$(BUILTIN)
	@mkdir -p $(OBJECTS)/$(HASH_TABLE)
	@mkdir -p $(OBJECTS)/$(MAIN)
	@mkdir -p $(OBJECTS)/$(UTILS)
	@mkdir -p $(OBJECTS)/$(KEYBOARD)
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
