# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achiu <achiu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 11:46:34 by achiu             #+#    #+#              #
#    Updated: 2024/10/14 16:10:12 by achiu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

PRNT_SRC	= err_printf ft_nbr ft_char ft_hex
IS_SRC		= ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace ft_isnbr
MEM_SRC		= ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_bzero ft_calloc
PUT_SRC		= ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
TO_SRC		= ft_atoi ft_itoa ft_tolower ft_toupper
STR_SRC		= ft_strchr ft_strcpy ft_strdup ft_striteri ft_strjoin ft_split ft_strlcat ft_strcmp \
			ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr
LST_SRC		= ft_lstnew ft_lstsize ft_lstlast ft_lstadd_front ft_lstadd_back \
			ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
ADD_SRC		= get_next_line ft_freematrix ft_strs_count ft_strjoin_with_sep add_str_to_strs \
			ft_replace_str add_str_with_nextline space_or_tab

SRC_FILES	= \
			$(addprefix ft_is/, $(addsuffix .c, $(IS_SRC))) \
			$(addprefix ft_printf/, $(addsuffix .c, $(PRNT_SRC))) \
			$(addprefix ft_mem/, $(addsuffix .c, $(MEM_SRC))) \
			$(addprefix ft_put/, $(addsuffix .c, $(PUT_SRC))) \
			$(addprefix ft_to/, $(addsuffix .c, $(TO_SRC))) \
			$(addprefix ft_str/, $(addsuffix .c, $(STR_SRC))) \
			$(addprefix ft_add/, $(addsuffix .c, $(ADD_SRC)))
OBJ			= ${SRC_FILES:.c=.o}
SRC_BONUS	= \
			$(addprefix ft_lst/, $(addsuffix .c, $(LST_SRC)))
OBJ_BONUS	= ${SRC_BONUS:.c=.o}

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes

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
# ft_lstnew.c ft_lstsize.c ft_lstlast.c
# ft_lstdelone.c ft_lstclear.c ft_lstiter.c
# ft_lstadd_front.c
# ft_lstadd_back.c
# ft_lstmap.c fails paco