# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:05:48 by lmicheli          #+#    #+#              #
#    Updated: 2024/03/20 10:06:48 by gduranti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -g -Wuninitialized

PIPEX = pipex/pipex.c \
	pipex/process.c

BUILT_IN = built_in/echo.c \
	built_in/cd.c \
	built_in/unset.c \
	built_in/ft_exit.c \
	built_in/export.c \
	built_in/cd_utils.c \

UTILS = utils/ft_error.c \
	utils/close_funct.c \
	utils/list_funct.c \
	utils/utils.c \
	utils/str_utils.c \
	utils/str_utils2.c \
	utils/str_utils3.c \
	utils/matrix_utils.c \
	utils/arg_to_mtx.c \
	utils/neo_argtomtx.c \
	utils/heredoc.c \
	utils/list_utils.c \
	utils/space_utils.c \
	utils/math_utils.c \
	utils/file_check.c

LEXER = lexer/lexer.c \
		lexer/quote.c \
		lexer/redir.c \
		lexer/pipe.c

PARSER = parser/parser.c \
	parser/parser_utils.c \
	parser/quotehandler.c \
	parser/expand_variables.c \
	parser/get_hicat.c

SRCS = srcs/main.c \
	srcs/input_init.c \
	srcs/tty_run.c \
	srcs/fd_inout.c \
	srcs/input_exec.c

BONUS = bonus/input_bonus.c

SRC = $(PIPEX) $(BUILT_IN) $(UTILS) $(PARSER) $(SRCS) $(LEXER) $(BONUS)

FT_PRINTF = libft
LIB = libft/libftprintf.a

all: $(NAME)

bonus: $(NAME)

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

play:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mRe-compiled "$(NAME)" successfully!\033[0m"
	@echo "\033[30mPlease work🙏\033[0m"
	@./$(NAME)

val:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mAre you ready for debugging?\033[0m 😈"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s --track-fds=yes ./$(NAME)

bash:
	@bash

.PHONY: all clean fclean re play