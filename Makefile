# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 15:05:20 by lorenzo           #+#    #+#              #
#    Updated: 2024/07/01 18:04:03 by lorenzo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc -g
FLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I./includes/
SRC_DIR		= ./src/
OBJ_DIR 	= ./obj/
SRC_FILES	= philo.c utils.c init.c threads.c routine.c
OBJ_FILES	= $(SRC_FILES:.c=.o)
SRCS		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBRARIES	= -lpthread

all: $(NAME)

$(shell mkdir -p $(OBJ_DIR))

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBRARIES)

$(OBJ_DIR)%o: $(SRC_DIR)%c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(LIBRARIES)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all