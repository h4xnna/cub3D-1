BOLD            = "\033[1m"
RESET           = "\033[0m"
GREEN           = "\033[0;32m"
CYAN            = "\033[0;36m"
LIGHT_RED       = "\033[91m"
LIGHT_GREEN     = "\033[92m"
LIGHT_CYAN      = "\033[96m"
BROWN           = "\033[38;5;94m"

NEON_GREEN      = "\033[38;5;46m"
ELECTRIC_BLUE   = "\033[38;5;51mare"
HOT_PINK        = "\033[38;5;198m"
BLOOD_RED       = "\033[38;5;196m"
SUNBURST_YELLOW = "\033[38;5;226m"
DEEP_ORANGE     = "\033[38;5;208m"
PURPLE_RAVE     = "\033[38;5;129m"
CYAN_SHOCK      = "\033[38;5;51m"


NAME	= cube
CC		= cc 
CFLAGS	= -Wall -Werror -Wextra -g3

SRCS	=	gnl/get_next_line.c\
			main.c \
			pars/info_pars1.c\
			pars/info_pars2.c\
			pars/info_pars3.c\
			pars/pars_map.c \
			pars/pars_map2.c  \
			pars/free_pars1.c \
			pars/info_pars4.c\
			exec/buttons.c\
			exec/draw_map2D.c\
			exec/raycasting.c\
			exec/texture.c\
			exec/util_win.c\
			exec/animation.c\
			utils_main.c\
			utils_main2.c\
			exec/player_position.c



# Libraries
MLX         = minilibx-linux/
MLX_A       = $(MLX_PATH)libmlx.a
MLX_PATH    = ./minilibx-linux/
MLX_FLAGS   = -lm -lbsd -lXext -lX11
LIBPRINTF   = ft_printf/libftprintf.a
 

INCL	= -I. -Ilibft


LIBFT_PATH        = libft/
LIBFT_NAME        = libft.a
LIBFT            = $(LIBFT_PATH)$(LIBFT_NAME)

HEADERS = cub3d.h

OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c 
	@$(CC) $(CFLAGS) -I. -c $< -o $@ $(INCL)

$(MLX_PATH) : 
	@if [ ! -d $(MLX_PATH) ]; then git clone https://github.com/42Paris/minilibx-linux.git; fi;

$(MLX_A) :
	@echo $(LIGHT_CYAN)$(BOLD)"\nCompiling MiniLibX..."
	@make -sC minilibx-linux -j
	@echo $(NEON_GREEN)$(BOLD)"Library Compiled. ✔\n"

${NAME}: $(MLX_PATH) $(MLX_A) ${OBJS} $(LIBFT) $(HEADERS)

	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) $(MLX_A) $(MLX_FLAGS) -o ${NAME}
	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

clean:
	@rm -f ${OBJS}
	@make clean -C $(LIBFT_PATH)
	@echo $(BROWN)clean reussi

leak : all
	valgrind --leak-check=full ./cube map.cub

fclean: clean
	@rm -rf ${NAME}
	@rm -rf $(LIBFT_NAME)
	@rm -rf $(MLX_PATH)
	@echo $(BROWN)fclean reussi

re: fclean all

.PHONY : re fclean clean all