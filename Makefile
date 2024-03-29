# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 11:49:23 by ccompote          #+#    #+#              #
#    Updated: 2023/05/01 12:11:21 by inovomli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = main.c get_next_line.c get_next_line_utils.c create_map.c fill_map.c  open_file.c  handle_colors.c \
		map_utils.c handle_images.c map_utils_2.c nm_main1.c nm_main2.c nm_main3.c nm_main4.c

NAME =  cub3d
OBJ_DIR = ./obj/
OBJ_FILES = $(patsubst %.c, %.o, $(SRCS))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
MLX42 = ./MLX42
SRCS_DIR = ./

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: obj libft MLX42 $(NAME)

obj: 
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) MLX42/build/libmlx42.a $(LIBFT)/libft.a -Iinclude -ldl -lglfw -L "$(shell brew --prefix glfw)/lib/" -pthread -lm -o $(NAME) 

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