# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pthorell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/23 21:25:55 by pthorell          #+#    #+#              #
#    Updated: 2018/08/21 16:39:08 by pthorell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -I minilibx_macos -I libft -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -O3

LIB1DIR = libft/
LIB1 = $(LIB1DIR)libft.a

LIB2DIR = minilibx_macos/
LIB2 = $(LIB2DIR)libmlx.a

SRC = src/main.c \
	  src/error.c \
	  src/get_map.c \
	  src/event_handler.c \
	  src/raycast.c \
	  src/color.c \
	  src/draw.c \
	  src/movement.c \
	  src/texture_handler.c \
	  src/floorcast.c \
	  src/spritecast.c \
	  src/sprite_controller.c \
	  src/timing.c \
	  src/raycast_util.c \
	  src/spritecast_util.c

all: $(NAME)

$(NAME): $(SRC)
	make -C $(LIB1DIR)
	make -C $(LIB2DIR)
	gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB1) $(LIB2)

clean:
	make clean -C $(LIB1DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB1DIR)
	make clean -C $(LIB2DIR)

re: fclean all
