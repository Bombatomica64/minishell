# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:05:48 by lmicheli          #+#    #+#              #
#    Updated: 2024/02/19 10:36:59 by gduranti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -g

PIPEX = pipex/pipex.c \
	pipex/process.c

UTILS = utils/ft_error.c \
	utils/free_matrix.c

SRC = $(PIPEX) $(UTILS) \
	main.c \
	splut.c \
	fd_inout.c \
	input_pipex.c 

FT_PRINTF = ft_printf
LIB = ft_printf/libftprintf.a

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): 
	@make all -C $(FT_PRINTF)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "Compiled "$(NAME)" successfully!"

clean:
	@make clean -C $(FT_PRINTF)
	@rm -f $(NAME)
	@echo "Cleaned "$(NAME)" and libft objects successfully!"
	
fclean: clean
	@make fclean -C $(FT_PRINTF)
	@echo "FCleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all
	make re -C $(FT_PRINTF)

replay: clean
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "ReCompiled "$(NAME)" successfully!"

.PHONY: all clean fclean re replay