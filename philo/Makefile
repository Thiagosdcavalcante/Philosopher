# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 16:52:41 by tsantana          #+#    #+#              #
#    Updated: 2024/10/10 19:50:44 by tsantana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		:= cc

CFLAGS	:= -pthread -Wall -Wextra -Werror -g3 -fsanitize=thread

HEADERS	:= -I ./include

SRC		:= src/main.c \
			src/general_utils/main_utils.c \
			src/correct_input.c \
			src/routines/task_routine.c \
			src/correct_input_utils.c \
			src/general_utils/general_utils.c \
			src/general_utils/sup_for_philos.c \
			src/routines/monitoring.c \
			src/routines/monitoring2.c

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
