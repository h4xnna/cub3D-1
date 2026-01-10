# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 17:00:05 by pacda-si          #+#    #+#              #
#    Updated: 2026/01/10 17:26:23 by pacda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD            = "\033[1m"
RESET           = "\033[0m"
GREEN           = "\033[0;32m"
CYAN            = "\033[0;36m"
LIGHT_RED       = "\033[91m"
LIGHT_GREEN     = "\033[92m"
LIGHT_CYAN      = "\033[96m"
BROWN           = "\033[38;5;94m"

NEON_GREEN      = "\033[38;5;46m"
ELECTRIC_BLUE   = "\033[38;5;51m"
HOT_PINK        = "\033[38;5;198m"
BLOOD_RED       = "\033[38;5;196m"
SUNBURST_YELLOW = "\033[38;5;226m"
DEEP_ORANGE     = "\033[38;5;208m"
PURPLE_RAVE     = "\033[38;5;129m"
CYAN_SHOCK      = "\033[38;5;51m"

NAME	= cub3D_bonus
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3 -Ofast -march=native -ffast-math -Wno-cast-function-type
# CFLAGS	= -Wall -Wextra -Werror -O3 -march=native -ffast-math

PARSING 	=		parsing/
GAME		=		game/
RAYCASTING	=		$(GAME)raycasting/
UTILS 		=		utils/
LIBS		=		assets/libs/

SRCS	=	$(LIBS)gnl/get_next_line.c\
			main.c \
			$(PARSING)checker.c\
			$(PARSING)file_parsing.c\
			$(PARSING)flood_fill.c\
			$(PARSING)map_parsing.c\
			$(PARSING)parsing_utils.c\
			$(PARSING)parsing_utils2.c\
			$(PARSING)storage.c\
			$(PARSING)doors.c \
			$(GAME)animations.c\
			$(GAME)animation_loading.c\
			$(GAME)doors.c\
			$(GAME)drawing.c\
			$(GAME)events.c\
			$(GAME)minimap.c\
			$(GAME)movement.c\
			$(GAME)player.c\
			$(GAME)render.c\
			$(GAME)textures.c\
			$(GAME)utils.c\
			$(GAME)window.c\
			$(RAYCASTING)dda.c\
			$(RAYCASTING)init.c\
			$(RAYCASTING)raycasting.c\
			$(RAYCASTING)render_floor.c\
			$(UTILS)exit.c\
			$(UTILS)free.c\
			$(UTILS)free2.c\
			$(UTILS)print_utils.c



# Libraries
MLX         = $(LIBS)minilibx-linux/
MLX_A       = $(MLX_PATH)libmlx.a
MLX_PATH    = $(LIBS)minilibx-linux/
MLX_FLAGS   = -lm -lbsd -lXext -lX11
 

INCL	= -I. -I$(LIBS)libft 


LIBFT_PATH        = $(LIBS)libft/
LIBFT_NAME        = libft.a
LIBFT            = $(LIBFT_PATH)$(LIBFT_NAME)

HEADERS = cub3d.h

# Object files
OBJ_DIR = objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: ${NAME}

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I. -c $< -o $@ $(INCL)

$(MLX_PATH) : 
	@if [ ! -d $(MLX_PATH) ]; then git clone https://github.com/42Paris/minilibx-linux.git $(LIBS)minilibx-linux; fi;

$(MLX_A) :
	@echo $(LIGHT_CYAN)$(BOLD)"\nCompiling MiniLibX..."
	@make -sC $(MLX_PATH) -j
	@echo $(NEON_GREEN)$(BOLD)"Library Compiled. ✔\n"

${NAME}: $(MLX_PATH) $(MLX_A) $(HEADERS) ${OBJS} $(LIBFT)
	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) $(MLX_A) $(MLX_FLAGS) -o ${NAME}
	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -C $(LIBFT_PATH)
	@echo $(BROWN)clean reussi

leak : all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cube ./assets/maps/map.cub

fclean: clean
	@rm -rf ${NAME}
	@rm -rf $(LIBFT)
	@rm -rf $(MLX_PATH)
	@echo $(BROWN)fclean reussi

re: fclean all

.PHONY : re fclean clean all
