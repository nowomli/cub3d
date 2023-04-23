# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 11:49:23 by ccompote          #+#    #+#              #
#    Updated: 2023/04/23 18:00:08 by ccompote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = main.c get_next_line.c get_next_line_utils.c create_map.c check_before_map.c fill_map.c 

NAME =  cub3d
OBJ_DIR = ./obj/
OBJ_FILES = $(patsubst %.c, %.o, $(SRCS))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
# CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
MLX42 = ./MLX42
SRCS_DIR = ./

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) -c $< -o $@

all: obj libft MLX42 $(NAME)

obj: 
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) MLX42/build/libmlx42.a $(LIBFT)/libft.a -Iinclude -ldl -lglfw -L "$(shell brew --prefix glfw)/lib/" -pthread -lm -o $(NAME) 

libft:
	@$(MAKE) -C $(LIBFT)

# MLX42:
# 	@$(MAKE) -C $(MLX42)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean
	# @$(MAKE) -C $(MLX42)/build clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	# @$(MAKE) -C $(MLX42) fclean

re: fclean all

.PHONY: all clean fclean re libft MLX42 