# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 14:37:38 by taqi              #+#    #+#              #
#    Updated: 2025/02/16 15:13:13 by oettaqi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME    = fractol

# Compiler
CC      = cc
#CFLAGS  = -Werror -Wextra -Wall

# Minilibx
MLX_PATH    = minilibx-linux/
MLX_NAME    = libmlx.a
MLX         = $(MLX_PATH)$(MLX_NAME)

# Includes
INC = -I ./includes/ -I ./minilibx-linux/ -I .


# Sources
SRC         = parsing/parsing.c parsing/utils_parsing.c  parsing/verif_input.c  parsing/ft_atod.c  main.c
SRCS        = $(SRC)

# Objects
OBJ_PATH    = obj/
OBJ         = $(SRC:.c=.o)
OBJS        = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(MLX) $(NAME)

# Pour compiler les fichiers objets, on crée le dossier contenant $@ (ex: obj/parsing/)
$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)

$(NAME): $(OBJS)
	@echo "Compiling fractol..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(INC) -lXext -lX11 -lm
	@echo "Fractol ready."

bonus: all

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	@echo "Removing fractol..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
