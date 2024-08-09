# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/08/08 19:44:06 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			= minishell.c signal.c token.c lexer.c
OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft -fsanitize=address
# RL			= -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory -lncurses
# RL			= -L/usr/local/opt/readline/lib -lreadline
# RL_M2chip	= -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -lhistory

LIBFT		= libft/libft.a
LIBFT_MAKE	= make -C libft/

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			# $(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL_M2chip)
			# $(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
			
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

