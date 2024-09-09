# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/09/08 17:56:22 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= \
			minishell.c free_address.c \
			signal.c \
			env.c \
			token.c lexer.c parse.c visualize.c \
			node_pipe.c node_cmd.c node_redir.c \
			exec.c exec_cmd.c exec_export.c exec_unset.c exec_cd.c exec_others.c executable_cmd.c \
			var.c splits_by_var.c \

OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft
# RL			= -L/usr/l ocal/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory -lncurses
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

