# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahuge <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 13:54:46 by ahuge             #+#    #+#              #
#    Updated: 2023/12/13 12:20:59 by ahuge            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = libftprintf.a

SOURCES = ft_printf.c ft_print_character.c \
ft_print_decimal.c ft_print_hexadecimal.c

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

$(NAME) : $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

all : $(NAME)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean fclean all re

