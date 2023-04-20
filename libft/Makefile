# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 14:59:49 by ccompote          #+#    #+#              #
#    Updated: 2022/05/26 19:01:20 by ccompote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =  ft_atoi.c		ft_bzero.c		ft_calloc.c			ft_isalnum.c\
			ft_isalpha.c	ft_isascii.c	ft_isdigit.c		ft_isprint.c\
			ft_memchr.c		ft_memcmp.c		ft_memcpy.c			ft_memmove.c\
			ft_memset.c		ft_strchr.c		ft_strdup.c			ft_strjoin.c\
			ft_strlcat.c	ft_strlcpy.c	ft_strlen.c			ft_strncmp.c\
			ft_strnstr.c	ft_strrchr.c	ft_substr.c			ft_tolower.c\
			ft_toupper.c	ft_putchar_fd.c	ft_putnbr_fd.c		ft_putendl_fd.c\
			ft_putstr_fd.c	ft_substr.c		ft_strtrim.c		ft_itoa.c\
			ft_striteri.c	ft_strmapi.c	ft_split.c

SRCS_B = ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c	ft_lstdelone.c\
			ft_lstiter.c	ft_lstlast.c	ft_lstmap.c			ft_lstnew.c\
			ft_lstsize.c

OBJ	= $(patsubst %.c,%.o,$(SRCS))
OBJ_B = $(patsubst %.c,%.o,$(SRCS_B))
 
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $?

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

bonus :
	@make OBJ="$(OBJ_B)" all

clean :
	@rm -f $(OBJ) $(OBJ_B)
	
fclean : clean
	@rm -f $(NAME)
		
re : fclean all

.PHONY : all clean fclean re bonus