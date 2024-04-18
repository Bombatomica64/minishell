/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef enum e_bool
{
	FALSE, // 0
	TRUE, // 1
	ERROR = -1
}	t_bool;

int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_lstsize(t_list *lst);
size_t		ft_strlen(char *s);
size_t		ft_strlcat(char *dst, char *src, size_t size);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
char		*ft_strdup(char *s);
char		*ft_itoa(int n);
char		*ft_strnstr(const char *big, char *little, size_t len);
char		*ft_strchr(char *str, int c);
char		*ft_strrchr(char *str, int c);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_freesubstr(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		*ft_freestrtrim(char *s1, char *set);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_strcmp(const char *s1, const char *s2);

//str_utils.c

// char		*ft_strncpy_noquote(char *str, int start, int end);
char		*ft_strjoin_2free(char *old_str, char *buf);
char		*ft_strjoin_2(char *old_str, char *buf);
char		*ft_strndup(char *str, int i);
int			ft_strlen_noquote(char *str);

//str_utils2.c

int			ft_isinset(char c, char *set);
char		*ft_strtrimfree(char *s1, char *set, int *trimmed);
int			find_first(char *str, char c);
int			find_last(char *str, char c);

//str_utils3.c

char		*free_strrchr(char *str, char c, int **offset);
char		*join_char(char *str, char c);
char		*cut_string(int len, char *str);
char		*strjoin_n_free1(char *line, char *buff, int index);
char		*ft_strncpy(char *str, int start, int end);

//str_utils4.c

char		*free_strdup(char *str, char **freestr);
char		*ft_skipstring(int offset, char *str);

//type_check

t_bool		ft_islimiter(char c);
t_bool		ft_isquote(char c);

#endif
