# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 11:46:34 by achiu             #+#    #+#              #
#    Updated: 2024/09/16 08:14:56 by fiftyblue        ###   ########.fr        #
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
			get_next_line.c \
			ft_freematrix.c ft_strs_count.c ft_strjoin_with_sep.c add_str_to_strs.c \
			ft_strcmp.c ft_isnbr.c \
			err_printf.c ft_nbr.c ft_char.c ft_hex.c \

# PRNT_SRC	= ft_printf ft_nbr ft_char ft_hex
# IS_SRC		= ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace ft_isnbr
# MEM_SRC		= ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_bzero ft_calloc
# PUT_SRC		= ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
# TO_SRC		= ft_atoi ft_itoa ft_tolower ft_toupper
# STR_SRC		= ft_strchr ft_strcpy ft_strdup ft_striteri ft_strjoin ft_split ft_strlcat ft_strcmp \
# 			ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr
# ADD_SRC		= get_next_line ft_freematrix ft_strs_count ft_strjoin_with_sep add_str_to_strs

# SRC_FILES	= \
# 			$(addprefix ft_is/, $(addsuffix .c, $(SRC_FILES))) \
# 			$(addprefix ft_printf/, $(addsuffix .c, $(PRNT_SRC))) \
# 			$(addprefix ft_mem/, $(addsuffix .c, $(MEM_SRC))) \
# 			$(addprefix ft_put/, $(addsuffix .c, $(PUT_SRC))) \
# 			$(addprefix ft_to/, $(addsuffix .c, $(TO_SRC))) \
# 			$(addprefix ft_str/, $(addsuffix .c, $(STR_SRC))) \
# 			$(addprefix ft_add/, $(addsuffix .c, $(ADD_SRC)))

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