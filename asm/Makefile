#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlequien <hlequien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/03 19:15:09 by hlequien          #+#    #+#              #
#    Updated: 2018/08/20 18:53:40 by snassour         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -g -Wall -Wextra -Og
#-fsanitize=address

SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC_NAME = asm.c\
data.c\
op.c\
parse.c\
parse_cmd.c\
check_arguments.c\
asm_list.c\
asm_write_color.c\
asm_error.c\
asm_tools.c\
asm_checklabel.c\
corewar_list.c

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_PATH = ./inc/\
./libft/includes/

INC_FILES = ./inc/asm.h\
./inc/op.h

NAME = asm

LIB = -L./libft -lft
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all:$(NAME)

$(NAME):$(OBJ) $(INC_FILES)
#	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c $(INC_FILES)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rfv $(OBJ_PATH)

fclean:clean
	rm -fv $(NAME)

re:fclean all
