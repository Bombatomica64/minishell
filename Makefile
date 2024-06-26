# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:05:48 by gduranti          #+#    #+#              #
#    Updated: 2024/04/30 15:00:31 by mruggier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Wextra -Werror -g

PIPEX = pipex/pipex.c \
	pipex/process.c

BUILT_IN = built_in/echo.c \
	built_in/cd.c \
	built_in/unset.c \
	built_in/ft_exit.c \
	built_in/export.c \
	built_in/cd_utils.c

UTILS = utils/ft_error.c \
	utils/close_funct.c \
	utils/list_funct.c \
	utils/matrix_utils.c \
	utils/list_utils.c \
	utils/space_utils.c \
	utils/math_utils.c \
	utils/file_check.c \
	utils/input_utils.c \
	utils/quotehandler.c \
	utils/utils.c \
	utils/accounting.c

LEXER = lexer/lexer.c \
		lexer/quote.c \
		lexer/redir.c \
		lexer/pipe.c

PARSER = parser/parser.c \
	parser/parser_utils.c \
	parser/expand_variables.c \
	parser/get_hicat.c

SRCS = srcs/main.c \
	srcs/input_init.c \
	srcs/ft_action.c \
	srcs/tty_run.c \
	srcs/fd_inout.c \
	srcs/heredoc.c \
	srcs/heredoc_utils.c \
	srcs/arg_to_mtx.c \
	srcs/neo_argtomtx.c \
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
	@rm -f $(OBJ)
	@echo "Cleaned "$(NAME)" and libft objects successfully!"
	
fclean: clean
	@make fclean -C $(FT_PRINTF)
	@rm -f $(NAME)
	@echo "Fcleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all

play: clean $(SRC)
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mRe-compiled "$(NAME)" successfully!\033[0m"
	@echo "\033[30mPlease work🙏\033[0m"
	@./$(NAME)

val: clean $(SRC)
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mAre you ready for debugging?\033[0m 😈"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s --track-fds=yes ./$(NAME)

bash:
	@bash

.PHONY: all clean fclean re play