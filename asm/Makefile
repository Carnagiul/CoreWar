#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlequien <hlequien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/03 19:15:09 by hlequien          #+#    #+#              #
#    Updated: 2018/08/20 08:26:32 by snassour         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -g  # -Wall -Wextra -Werror
#-fsanitize=address

SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC_NAME = asm.c\
data.c\
op.c\
parse.c\
parse_cmd.c\
check_arguments.c

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_PATH = ./inc/\
./libft/includes/
NAME = asm

LIB = -L./libft -lft
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all:$(NAME)

$(NAME):$(OBJ)
#	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rfv $(OBJ_PATH)

fclean:clean
	rm -fv $(NAME)

re:fclean all
