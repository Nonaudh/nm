# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cblonde <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 16:57:56 by cblonde           #+#    #+#              #
#    Updated: 2024/11/25 08:12:17 by cblonde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g #-Werror -Wextra -Wall

INCLUDE = -Iinc -Ilib/libft

LIBRARIES = -Llib/libft -lft

DSRC64 = src/64/

DSRC23 = src/32/

DLIB = lib/libft/

LIB = $(DLIB)libft.a

SRC = src/main.c $(DSRC64)nm.c $(DSRC64)sort.c $(DSRC64)utils_elf.c $(DSRC64)print.c

NAME = ft_nm

all : $(NAME)

DBUILD = build/

OBJ = $(addprefix $(DBUILD),$(SRC:%.c=%.o))

$(DBUILD)%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBRARIES) -o $(NAME)

$(LIB) :
	@make -C $(DLIB)

clean :
	@make clean -C $(DLIB)
	@rm -rf $(DBUILD)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(LIB)

re : fclean $(NAME)

.PHONY: all clean fclean re
