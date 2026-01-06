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


NAME	= cube
CC		= cc 
CFLAGS	= -Wall -Werror -Wextra -g3

PARSING =	parsing/
EXEC	=	exec/
UTILS	=	utils/

SRCS	=	./assets/libs/gnl/get_next_line.c\
			main.c \
			$(PARSING)checker.c\
			$(PARSING)file_parsing.c\
			$(PARSING)flood_fill.c\
			$(PARSING)map_parsing.c \
			$(PARSING)parsing_utils.c  \
			$(PARSING)parsing_utils2.c \
			$(PARSING)storage.c\
			$(EXEC)camera.c\
			$(EXEC)keys.c\
			$(EXEC)player.c\
			$(EXEC)raycasting_helper.c\
			$(EXEC)raycasting.c\
			$(EXEC)render.c\
			$(EXEC)texture.c\
			$(EXEC)window.c\
			$(UTILS)exit.c\
			$(UTILS)free.c\
			$(UTILS)print_utils.c


# Libraries
MLX         = ./assets/libs/minilibx-linux/
MLX_A       = $(MLX_PATH)libmlx.a
MLX_PATH    = ./assets/libs/minilibx-linux/
MLX_FLAGS   = -lm -lbsd -lXext -lX11
 

INCL	=	-I. -I./assets/libs/libft 


LIBFT_PATH        = ./assets/libs/libft/
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
	@if [ ! -d $(MLX_PATH) ]; then git clone https://github.com/42Paris/minilibx-linux.git ./assets/libs/minilibx-linux; fi;

$(MLX_A) :
	@echo $(LIGHT_CYAN)$(BOLD)"\nCompiling MiniLibX..."
	@make -sC $(MLX_PATH) -j
	@echo $(NEON_GREEN)$(BOLD)"Library Compiled. ✔\n"

${NAME}: $(MLX_PATH) $(MLX_A) $(HEADERS) ${OBJS} $(LIBFT)
	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) $(MLX_A) $(MLX_FLAGS) -o ${NAME}
	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

# ${NAME}: $(HEADERS) ${OBJS} $(LIBFT)
# 	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
# 	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) $(MLX_A) $(MLX_FLAGS) -o ${NAME}
# 	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -C $(LIBFT_PATH)
	@echo $(BROWN)clean reussi

leak : all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cube ./maps/map.cub

fclean: clean
	@rm -rf ${NAME}
	@rm -rf $(LIBFT_NAME)
	@rm -rf $(MLX_PATH)
	@echo $(BROWN)fclean reussi

re: fclean all

.PHONY : re fclean clean all
