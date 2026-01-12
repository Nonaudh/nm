# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahuge <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 13:54:46 by ahuge             #+#    #+#              #
#    Updated: 2023/11/14 17:47:58 by ahuge            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

NAME = libft.a

SOURCES = ft_atoi.c ft_atol.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
ft_atof.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c \
ft_strchr.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
ft_calloc.c ft_strdup.c ft_strlcat.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_strmapi.c ft_striteri.c ft_strtrim.c \
../get_next_line/get_next_line_bonus.c ../get_next_line/get_next_line_utils_bonus.c \
../ft_printf/ft_printf.c ../ft_printf/ft_print_character.c \
../ft_printf/ft_print_decimal.c ../ft_printf/ft_print_hexadecimal.c

SOURCES_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c

all : $(NAME)

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

bonus : $(OBJECTS) $(OBJECTS_BONUS)
	ar -rcs $(NAME) $(OBJECTS) $(OBJECTS_BONUS)

clean :
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean : clean
	@rm -f $(NAME)

re: fclean all

.PHONY : clean fclean all re
