# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 21:22:06 by sunakim           #+#    #+#              #
#    Updated: 2019/05/26 10:59:02 by mnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
VISU_NAME = visu

CC = gcc -g
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./includes -I libftprintf/includes `pkg-config --cflags sdl2`
LDIR = -L libftprintf/ -lftprintf `pkg-config --libs sdl2` `pkg-config --libs sdl2_image` `pkg-config --libs sdl2_ttf`

LIBFT = libftprintf.a

HEADER = ./includes/lemin.h ./includes/visu.h

SRC = $(addprefix src/, edge.c room.c input.c main.c output.c cmp.c path.c del_cp.c algo.c q_util.c bfs.c flow.c printsimple.c)
OBJ = $(SRC:.c=.o)

VISU_SRC = $(addprefix src/visu/, main.c  lemin_input.c  input.c lemin.c cmp.c draw_map.c init_visu.c load_visu.c util_visu.c free_visu.c  dot.c read_sol.c del_cp.c)
VISU_OBJ = $(VISU_SRC:.c=.o)

.PHONY: all fclean clean re

RM = rm -f

all: $(NAME) $(VISU_NAME)

$(LIBFT):
	make -C libftprintf/

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(LDIR) $(INCLUDES)

$(VISU_NAME) : $(LIBFT) $(VISU_OBJ)
	$(CC) $(CFLAGS)  -o $(VISU_NAME) $(VISU_OBJ) $(LDIR) $(INCLUDES)

clean:
	$(RM) $(OBJ) $(VISU_OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(NAME) $(VISU_NAME)
	make -C libftprintf/ fclean

re: fclean all
