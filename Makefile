# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/09/13 11:29:04 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c
LEXER_SRC	= lexer.c quote_utils.c token.c var.c splits_by_var.c
PARSER_SRC	= parse.c node_pipe.c node_cmd.c node_redir.c
BUILIN_SRC	= builtin.c export.c unset.c cd.c pwd.c exit.c echo.c exec_env.c
CMD_SRC		= exec_cmd.c execve_.c executable_cmd.c
REDIR_SRC	= exec_redir.c pipe.c heredoc.c
DEBUG_SRC	= visualize.c
ENV_SRC		= env.c
SIG_SRC		= signal.c
UTILS_SRC	= free_address.c

SRC_FILES	= \
			$(addprefix srcs/, $(SRC)) \
			$(addprefix srcs/lexer/, $(LEXER_SRC)) \
			$(addprefix srcs/parser/, $(PARSER_SRC)) \
			$(addprefix srcs/buildin/, $(BUILIN_SRC)) \
			$(addprefix srcs/cmd/, $(CMD_SRC)) \
			$(addprefix srcs/redir/, $(REDIR_SRC)) \
			$(addprefix srcs/debug/, $(DEBUG_SRC)) \
			$(addprefix srcs/env/, $(ENV_SRC)) \
			$(addprefix srcs/sig/, $(SIG_SRC)) \
			$(addprefix srcs/utils/, $(UTILS_SRC)) \

OBJ			= $(SRC_FILES:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft -Iincludes
CPPFLAGS	= -I$(RL_M2)/include
LDFLAGS		= -L$(RL_M2)/lib -lreadline
# -fsanitize=address
# -lhistory -lncurses

# readline path may differ cuz install in different way in different system
# RL_PATH		= /usr/local/opt/readline
RL_M2		= /opt/homebrew/opt/readline
# RL			= /Users/achiu/local/

# RL2			= -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory -lncurses
# RL			= -L/usr/local/opt/readline/lib -lreadline -lhistory
# RL1			= -L/Users/achiu/local/lib -I/Users/achiu/local/include -lreadline -lhistory -lncurses

LIBFT		= libft/libft.a
LIBFT_MAKE	= make -C libft/

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)
			# $(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL1)
			
$(LIBFT):
			$(LIBFT_MAKE)

clean:
			rm -rf $(OBJ)
			# $(LIBFT_MAKE) clean

fclean: 	clean
			rm -rf $(NAME)
			# rm -rf $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re

