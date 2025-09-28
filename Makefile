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

SRCS	=	gnl/get_next_line.c\
			main.c \
			info_pars1.c\
			info_pars2.c\
			info_pars3.c\
			pars_map.c \
			free_pars1.c \
			utils_map_pars1.c  \



INCL	= -I. -Ilibft


LIBFT_PATH        = libft/
LIBFT_NAME        = libft.a
LIBFT            = $(LIBFT_PATH)$(LIBFT_NAME)

HEADERS = cub3d.h

OBJS = ${SRCS:.c=.o}

all: ${NAME}


%.o: %.c 
	@$(CC) $(CFLAGS) -I. -c $< -o $@ $(INCL)

${NAME}: ${OBJS} $(LIBFT) $(HEADERS)

	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) -o ${NAME}
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
	@rm -f ${NAME}$(LIBFT_PATH)$(LIBFT_NAME)
	@echo $(BROWN)fclean reussi

re: fclean all

.PHONY : re fclean clean all