# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achiu <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 10:37:56 by achiu             #+#    #+#              #
#    Updated: 2024/07/30 10:38:03 by achiu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			=
OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft

LIBFT		= libft/libft.a
LIBFT_MAKE	= make -C libft/

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
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

