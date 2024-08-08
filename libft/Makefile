# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 11:46:34 by achiu             #+#    #+#              #
#    Updated: 2024/08/07 11:41:50 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRC			=  \
			ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c\
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_bzero.c ft_calloc.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c \
			ft_strchr.c ft_strcpy.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_split.c ft_strlcat.c  \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_printf.c ft_nbr.c ft_char.c ft_hex.c \
			get_next_line.c \
			ft_freematrix.c \
				
OBJ			= ${SRC:.c=.o}

SRC_BONUS	=  \
			ft_lstnew.c ft_lstsize.c ft_lstlast.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstmap.c \
			
OBJ_BONUS	= ${SRC_BONUS:.c=.o}

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

all:		 ${NAME}

${NAME}:	${OBJ} ${OBJ_BONUS}
			ar rcs ${NAME} ${OBJ} ${OBJ_BONUS}

bonus:		${OBJ_BONUS}
			ar rcs ${NAME} ${OBJ_BONUS}

clean: 		
			rm -f ${OBJ} ${OBJ_BONUS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re

# ft_split.c ft_strtrim.c ft_substr.c ft_calloc.c ft_bzero.c ft_memset.c ft_strlen.c ft_strchr.c
# ft_itoa.c ft_calloc.c ft_bzero.c ft_memset.c