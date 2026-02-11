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

DLIB = lib/libft

INCLUDE = -Iinc -I$(DLIB)

LIBRARIES = -L$(DLIB) -lft

DSRC64 = src/64
DSRC32 = src/32
DSRCSHARED = src/shared

LIB = $(DLIB)/libft.a

SRC = src/main.c $(DSRC64)/nm.c $(DSRC64)/sort.c $(DSRC64)/utils_elf.c $(DSRC64)/print.c \
					$(DSRC32)/nm.c $(DSRC32)/sort.c $(DSRC32)/utils_elf.c $(DSRC32)/print.c \
					$(DSRCSHARED)/utils.c

NAME = ft_nm

all : copy $(NAME)

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

copy :
	mkdir -p src/32
	cp src/64/* src/32/
	cp inc/nm64.h inc/nm32.h
	sed -i "s/64/32/g" src/32/*
	sed -i "s/64/32/g" inc/nm32.h

.PHONY: all clean fclean re
