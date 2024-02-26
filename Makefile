# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:05:48 by lmicheli          #+#    #+#              #
#    Updated: 2024/02/26 18:27:48 by lmicheli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -g -Wuninitialized

PIPEX = pipex/pipex.c \
	pipex/process.c

BUILT_IN = built_in/echo.c \
	built_in/cd.c \
	built_in/unset.c

UTILS = utils/ft_error.c \
	utils/close_funct.c \
	utils/list_funct.c \
	utils/utils.c \
	utils/str_utils.c \
	utils/matrix_utils.c \
	utils/arg_to_mtx.c \
	utils/heredoc.c \
	utils/list_utils.c

PARSER = parser/parser.c \
	parser/parser_utils.c \
	parser/quotehandler.c

SRCS = srcs/main.c \
	srcs/input_init.c \
	srcs/tty_run.c \
	srcs/fd_inout.c \
	srcs/input_exec.c

SRC = $(PIPEX) $(BUILT_IN) $(UTILS) $(PARSER) $(SRCS)

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
	@echo "Fcleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all

replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[35mRe-compiled "$(NAME)" successfully!\033[0m"

.PHONY: all clean fclean re replay