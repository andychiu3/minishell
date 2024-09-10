# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/09/11 08:59:52 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c exec.c
LEXER_SRC	= lexer.c token.c var.c splits_by_var.c
PARSER_SRC	= parse.c node_pipe.c node_cmd.c node_redir.c
BUILIN_SRC	= exec_export.c exec_unset.c exec_cd.c
CMD_SRC		= executable_cmd.c exec_others.c exec_cmd.c
REDIR_SRC	= exec_redir.c
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
CFLAGS		= -Wall -Wextra -Werror -Ilibft -Iincludes -fsanitize=address
# RL			= -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory -lncurses
# RL			= -L/usr/local/opt/readline/lib -lreadline -lhistory
RL_M2chip	= -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -lhistory
# -fsanitize=address

LIBFT		= libft/libft.a
LIBFT_MAKE	= make -C libft/

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
# $(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL_M2chip)
			# $(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL)
			
			
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

