# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 16:52:41 by tsantana          #+#    #+#              #
#    Updated: 2024/07/30 14:43:59 by tsantana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		:= cc

CFLAGS	:= -pthread -Wall -Wextra -Werror -g3

HEADERS	:= -I include/ -I lib/libft/

SRC		:= src/main.c \
			src/main_utils.c \
			src/ft_atoi.c \
			src/correct_input.c \
			src/free_struct.c \
			src/task_routine.c \
			src/timer_def.c \
			src/correct_input_utils.c

OBJ		:= $(SRC:%.c=%.o)

%.o: &.c 
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) && printf "Compiling: $(notdir $<)"

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	clean all

PHONY: all, clean, fclean, re
