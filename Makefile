# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 11:49:23 by ccompote          #+#    #+#              #
#    Updated: 2023/04/20 12:24:25 by ccompote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = main.c get_next_line.c get_next_line_utils.c create_map.c check_before_map.c 

NAME =  cub3d
OBJ	= $(SRCS:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
MLX42 = ./MLX42

all: libft MLX42 $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

# MLX42:
# 	@$(MAKE) -C $(MLX42)

$(NAME): $(OBJ)
	$(CC) $(OBJ) MLX42/build/libmlx42.a $(LIBFT)/libft.a -Iinclude -ldl -lglfw -L "$(shell brew --prefix glfw)/lib/" -pthread -lm -o $(NAME)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean
	# @$(MAKE) -C $(MLX42)/build clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(MLX42) fclean

re: fclean all

.PHONY: all clean fclean re libft MLX42 