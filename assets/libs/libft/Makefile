# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 18:49:03 by hmimouni          #+#    #+#              #
#    Updated: 2026/01/10 16:25:47 by pacda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -I${INCLUDES} -Wall -Wextra -Werror

INCLUDES =	./
OBJS =		${SRCS:.c=.o}
SRCS =		./ft_atoi.c					\
			./ft_atoll.c				\
			./ft_bzero.c				\
			./ft_calloc.c				\
			./ft_isalnum.c				\
			./ft_isalpha.c				\
			./ft_isascii.c				\
			./ft_isdigit.c				\
			./ft_isprint.c				\
			./ft_itoa.c					\
			./ft_memchr.c				\
			./ft_memcmp.c				\
			./ft_memcpy.c				\
			./ft_memmove.c				\
			./ft_memset.c				\
			./ft_putchar_fd.c			\
			./ft_putendl_fd.c			\
			./ft_putnbr_fd.c			\
			./ft_putstr_fd.c			\
			./ft_realloc.c				\
			./ft_split.c				\
			./ft_strchr.c				\
			./ft_strcmp.c				\
			./ft_strdup.c				\
			./ft_striteri.c				\
			./ft_strjoin.c				\
			./ft_strlcat.c				\
			./ft_strlcpy.c				\
			./ft_strlen.c				\
			./ft_strmapi.c				\
			./ft_strncmp.c				\
			./ft_strnstr.c				\
			./ft_strrchr.c				\
			./ft_strtrim.c				\
			./ft_substr.c				\
			./ft_tolower.c				\
			./ft_toupper.c
BOBJS =		${BSRCS:.c=.o}
BSRCS := 	${SRCS}
all: ${NAME}

${NAME}: ${OBJS}
	ar -cr ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}
	rm -f ${BOBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all