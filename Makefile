# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:05:48 by lmicheli          #+#    #+#              #
#    Updated: 2024/02/20 11:11:12 by lmicheli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -g

PIPEX = pipex/pipex.c \
	pipex/process.c

UTILS = utils/ft_error.c \
	utils/free_matrix.c \
	utils/list_funct.c \
	utils/utils.c

SRCS = srcs/main.c \
	srcs/splut.c \
	srcs/fd_inout.c \
	srcs/input_pipex.c \
	srcs/input_init.c \
	srcs/tty_run.c

SRC = $(PIPEX) $(UTILS) $(SRCS)

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
	@echo "Cleaned "$(NAME)" and libft objects successfully!"
	
fclean: clean
	@make fclean -C $(FT_PRINTF)
	@rm -f $(NAME)
	@echo "FCleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all
	make re -C $(FT_PRINTF)

replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "ReCompiled "$(NAME)" successfully!"

.PHONY: all clean fclean re replay