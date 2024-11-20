# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/11/16 10:33:38 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell
LEXER_SRC	= lexer quote_utils token
PARSER_SRC	= parse node_pipe node_cmd node_redir heredoc_input
OP_SRC		= exec_redir pipe trunc_append input_heredoc
BUILIN_SRC	= builtin export export_utils unset cd pwd exit echo exec_env builtin_err_cases
CMD_SRC		= exec_cmd execve_ executable_cmd refresh_cmd
DEBUG_SRC	= visualize
SETUP_SRC	= env init_flags
SIG_SRC		= signal waitpid_status
VAR_SRC		= var splits_by_var
UTILS_SRC	= free_address errmsg check_var_rm_quote expand_path lexer_for_var \
			panic consume_stdin option

SRC_FILES	= \
			$(addprefix srcs/, $(addsuffix .c, $(SRC))) \
			$(addprefix srcs/lexer/, $(addsuffix .c, $(LEXER_SRC))) \
			$(addprefix srcs/parser/, $(addsuffix .c, $(PARSER_SRC))) \
			$(addprefix srcs/exec/operator/, $(addsuffix .c, $(OP_SRC))) \
			$(addprefix srcs/exec/cmd/buildin/, $(addsuffix .c, $(BUILIN_SRC))) \
			$(addprefix srcs/exec/cmd/, $(addsuffix .c, $(CMD_SRC))) \
			$(addprefix srcs/debug/, $(addsuffix .c, $(DEBUG_SRC))) \
			$(addprefix srcs/setup/, $(addsuffix .c, $(SETUP_SRC))) \
			$(addprefix srcs/sig/, $(addsuffix .c, $(SIG_SRC))) \
			$(addprefix srcs/var/, $(addsuffix .c, $(VAR_SRC))) \
			$(addprefix srcs/utils/, $(addsuffix .c, $(UTILS_SRC))) \

OBJ			= $(patsubst src/%, objs/%, $(SRC_FILES:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft -Iincludes
CPPFLAGS	= -I$(RL_PATH)/include
LDFLAGS		= -L$(RL_PATH)/lib -lreadline
# -fsanitize=address
# -lhistory -lncurses

# readline PATH may differ cuz install in different way in different system
ARCH		= $(shell uname -m)
ifeq ($(ARCH),arm64)
RL_PATH		= /opt/homebrew/opt/readline
else ifeq ($(ARCH),x86_64)
RL_PATH		= /usr/local/opt/readline
endif
# RL_PATH			= /Users/achiu/local/

LIBFT		= libft/libft.a
LIBFT_MAKE	= make -C libft/

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)
			
$(LIBFT):
			$(LIBFT_MAKE)

clean:
			rm -rf $(OBJ)
			$(LIBFT_MAKE) clean

fclean: 	clean
			rm -rf $(NAME)
			rm -rf $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re

