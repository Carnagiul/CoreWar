# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: piquerue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 14:20:07 by piquerue          #+#    #+#              #
#    Updated: 2018/08/07 05:08:13 by piquerue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = core_war
NAME2 = asm

LIBFT = libft
CFLAGS = -Wall -Werror -Wextra -Ofast -Wunreachable-code
INCLUDE = Include
C = corewar/op.c main.c
COUNT = $(shell find . -type f | grep "\.o" | wc -l)
COUNT_MAX = 1
H = Include/ft_corewar.h Include/op.h
O = $(C:%.c=%.o)
T = 0
INC = -I $(LIBFT)/$(INCLUDE) -I $(INCLUDE)

.PHONY : all clean fclean re libfclean libclean $(LIBFT)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT)

%.o: %.c $(H)
	@gcc $(CFLAGS) $(INC) -o $@ -c $<
	$(call plus,$(COUNT), 1)
	@printf "\033[1A\033[KCompiling Source \033[32m%d\033[37m / \033[31m%d\033[37m\n" $(COUNT) $(COUNT_MAX)

$(NAME): $(LIBFT) check display $(O)
	@gcc -o $(NAME) $(O) $(INC) $(LIBFT)/libft.a
	@cp $(NAME) $(NAME2)
	@printf "\033[1A\033[KCompiling Project \033[33m%s\033[37m\n" $(NAME)

libclean:
	@make -C $(LIBFT) clean

clean: libclean display
	@rm -rf $(O)

libfclean:
	@make -C $(LIBFT) fclean

fclean: libfclean clean
	@rm -f $(NAME)

re: fclean all

display:
	@sh .sh_tool/display.sh

check:
	@sh .sh_tool/check.sh

test:
	@printf "%d fichier .c trouver" $(COUNT)

music_start:
	@afplay ./ressources/music/music.mp3 &

music_end:
	@say -v thomas Fin de la compilation Merci d\'avoir patienter
	@killall afplay







#@printf "\033[1A\033[KCompiling Source \033[32m%s\033[37m =====> \033[31m%s\033[37m\n" $< $@
