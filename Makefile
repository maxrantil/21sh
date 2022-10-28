# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/10/28 11:55:42 by mrantil          ###   ########.fr        #
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

TERMCAP		=	-lntermcap

MAKEFLAGS	+= --no-print-directory

NAME		=	minishell
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra
CFLAGS		+= 	-Werror
#CFLAGS		+=	-Wunreachable-code -Wtype-limits 
#CFLAGS		+=	-Wpedantic
CFLAGS		+=	-O3

LEAK_CHECK	=	-g
#LEAK_CHECK	+=	-fsanitize=address

SOURCES 	= 	srcs
PARSER		= 	parser/
BUILTIN		= 	builtin/
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	msh

FILES 		= 	$(BUILTIN)builtin_cd \
				$(BUILTIN)builtin_echo \
				$(BUILTIN)builtin_unsetenv \
				$(BUILTIN)builtin_setenv \
				$(BUILTIN)builtins_env_exit \
				init \
				main \
				msh_launch \
				hash_table \
				$(PARSER)parser_changedollar \
				$(PARSER)parser_changetilde \
				$(PARSER)parser_changevar \
				$(PARSER)parser_count_arguments \
				$(PARSER)parser_get_arguments \
				$(PARSER)parser_strip_quotes \
				$(PARSER)parser \
				tools_env_var \
				tools_error \
				tools \
				update_env_var \
				
H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
C_PATHS 	= 	$(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS		=	$(addsuffix .o, $(addprefix $(OBJECTS)/,$(FILES)))
LIBS		= 	libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✓$(RESET)" || (printf "$@ $(RED)$(BOLD)✘$(RESET)\n\n" | printf "$(C_VISIBLE)" && exit 1)

all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@printf "$(C_VISIBLE)"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)/$(PARSER)
	@mkdir -p $(OBJECTS)/$(BUILTIN)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS):	$(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)
	@make pbar

libft:
	@make -C $(LIBRARIES)
	@cp $(LIBRARIES)/$(LIBS) .

clean:
	@make -C $(LIBRARIES) clean
	@rm -rf $(OBJECTS)
	@printf "$(NAME):	$(RED)$(OBJECTS) was deleted$(RESET)\n"

fclean: clean
	@make -C $(LIBRARIES) fclean
	@rm -f $(LIBS)
	@rm -f $(NAME)
	@printf "$(NAME):	$(RED)binary was deleted$(RESET)\n"

re: fclean all

	@printf "$(C_INVISIBLE)"
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
