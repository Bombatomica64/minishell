
NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = ft_atoi.c     ft_isascii.c      ft_lstadd_front.c  ft_lstmap.c   ft_memcpy.c        ft_putchar_fd.c   ft_split.c     ft_strlcat.c  ft_strnstr.c  ft_toupper.c \
ft_bzero.c    ft_isdigit.c      ft_lstclear.c      ft_lstnew.c   ft_memmove.c       ft_putendl_fd.c   ft_strchr.c    ft_strlcpy.c  ft_strrchr.c  ft_unsigned_itoa.c \
ft_calloc.c   ft_isprint.c      ft_lstdelone.c     ft_lstsize.c  ft_memset.c        ft_putnbr_base.c  ft_strdup.c    ft_strlen.c   ft_strtrim.c  get_next_line_bonus.c \
ft_isalnum.c  ft_itoa.c         ft_lstiter.c       ft_memchr.c   ft_printf.c        ft_putnbr_fd.c    ft_striteri.c  ft_strmapi.c  ft_substr.c   get_next_line_utils_bonus.c \
ft_isalpha.c  ft_lstadd_back.c  ft_lstlast.c       ft_memcmp.c   ft_printf_utils.c  ft_putstr_fd.c    ft_strjoin.c   ft_strncmp.c  ft_tolower.c	ft_strcmp.c ft_freesubstr.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) 
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Compiled "$(NAME)" successfully!"
$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@rm -f $(OBJS)
	@echo "Cleaned objects successfully!"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned "$(NAME)" successfully!"
	
re: fclean all

.PHONY: NAME all clean fclean re
