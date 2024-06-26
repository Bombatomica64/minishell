/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 16:11:36 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"
# include "colours.h"
# pragma once

extern int	g_duranti;

typedef enum e_error
{
	NO_PATH,
	DUP,
	EXECVE,
	PIPE,
	FORK,
	ACCESS,
	ACCESS_NOFREE,
	WRITE,
	NO_EXST,
	NO_EST_NOFREE,
	OPEN,
	BUILTIN,
	DIR
}	t_error;

typedef struct s_curs
{
	int		i;
	int		j;
	int		k;
	int		status;
}	t_curs;
typedef struct s_quote
{
	t_bool	open;
	char	type;
}	t_quote;

/**
 * @brief enum that defines the type of the node
 * @note INPUT: file in input
 * @note TRUNC: file, rewrites the lines in  the output file
 * @note APPEND: file, add more lines in the output file
 * @note COMMAND: command to be executed with execve
 * @note HEREDOC: limiter, terminal input until limiter
 * @note BUILT_IN: command to be executed without execve
 * @note PIPPE: pipe
 * @note FINISH: end of the list
 * @note USELESS: useless node
 * @note the type of the node is used to determine the action to be taken
*/
typedef enum e_type
{
	INPUT = 0,
	TRUNC = O_TRUNC,
	APPEND = O_APPEND,
	COMMAND,
	HEREDOC,
	BUILT_IN,
	PIPPE,
	FINISH = 69,
	USELESS
}	t_type;

typedef struct s_parser
{
	char	*tmp;
	char	*tmp_path;
	t_type	tmp_type;
}	t_parser;

typedef struct s_input
{
	char			*node;
	char			*path;
	t_type			type;
	struct s_input	*prev;
	struct s_input	*next;
}	t_input;

typedef struct s_pipex
{
	char	**cmd;
	char	*path;
	char	*filein;
	char	*fileout;
	int		fd_in;
	int		fd_out;
}				t_pipex;

typedef struct s_bonus
{
	int				type;
	t_bool			outcome;
	char			*str;
	struct s_bonus	*next;
}	t_bonus;

typedef struct s_data
{
	int		original_stdin;
	int		original_stdout;
	int		error_codes;
	int		**fd;
	int		counter;
	int		cmd_nbr;
	int		pipe_nbr;
	t_bool	in_pipe;
	char	**envp;
	char	*home;
	char	*pwd;
	t_input	*input;
	t_bonus	*bonus;
}	t_data;

// free and error functions

/**
 * @brief Function that frees a string matrix
 * @param matrix matrix to be freed
*/
void	free_matrix(char ***matrix);

/**
 * @brief Function that frees an integer matrix
 * @param matrix matrix to be freed
 * @param size size of the matrix
*/
void	free_array_matrix(int **matrix, int size);

/**
 * @brief Function that outputs an error message, 
 * frees the data and exits current command
 * @param str, string to help identify the error
 * @param error, type of error
 * @param errnbr, exit error number
 * @param data, data to be freed
 * @return int the error number
*/
int		ft_error(char *str, t_error error, int errnbr, t_data *data);

/**
 * @brief Function that checks if a malloc has failed
 * @param ptr pointer to be checked
 * @param str string to help identify where is the error
 * @return TRUE if malloc has failed, FALSE if it hasn't
*/
t_bool	ft_malloc_err(void *ptr, char *str);

/**
 * @brief Function that frees the data and closes the file descriptors
 * @param data, data to be freed
 * @return void
*/
void	free_close(t_data **data, int status);

/**
 * @brief Function that frees the data and returns the error number
 * @param data, data to be freed
 * @param status, error number
 * @return int the error number
 * @note this will free everything except envp 
*/
int		free_return(t_data **data, int status);

// list functions

/**int	g_duranti = -1;
 * @brief Function that creates a new node of t_input type
 * @param node command or file name
 * @param path path of the command or file
 * @param type type of the node
 * @return a new node of t_input type
*/
t_input	*ft_inputnew(t_parser prs);

/**
 * @brief Function that clears the input double linked list
 * @param lst list to be cleared
*/
void	ft_inputclear(t_input **lst);

/**
 * @brief Function that adds a new node at the end of the list
 * @param lst list to add too
 * @param news node to be added
*/
void	ft_inputadd_back(t_input **lst, t_input *news);

/**
 * @brief Function that adds a new node at the front of the list
 * @param lst lst to add too
 * @param news node to be added
*/
void	ft_inputadd_front(t_input **lst, t_input *news);

/**
 * @brief Function that returns the last node of the list
 * @param lst list to be checked
 * @return A pointer to the last node of the list
*/
t_input	*ft_inputlast(t_input **lst);

/**
 * @brief Function that returns the first node of the list
 * @param lst list to be checked
 * @return A pointer to the first node of the list
*/
t_input	*ft_inputfirst(t_input **lst);

/**
 * @brief Function that returns the number of nodes in the list
 * @param input list to be checked
 * @return the number of nodes in the list
*/
int		input_size(t_input *input);

/**
 * @brief Function that returns the number of commands in the list
 * @param input list to be checked
 * @return the number of commands in the list
*/
int		input_nbr_of_cmd(t_input *input);

// string functions
/**
 * @brief Funtion outputs a copy of a string allocated with no quoutes
 * @param str, string to be copied
 * @param start, start index of the string
 * @param end, end index of the string
 * @return a copy of the string without quotes
*/
char	*ft_strncpy_noquote(char *str, int start, int end, t_quote qte);

/**
 * @brief Function that skips spaces in a string
 * @param str a pointer to the string
 * @note space is defined as : " " \\t \\n \\v \\f \\r
 * @note The string WILL be modified
*/
void	skip_spaces(char **str);

/**
 * @brief Function that checks how many spaces to skip are in a string
 * @param str a pointer to the string
 * @return the number of spaces to skip
 * @note space is defined as : " " \\t \\n \\v \\f \\r
 * @note The string will NOT be modified
*/
int		skip_spaces2(char *str);

/**
 * @brief Function that checks if a character is a space
 * @param c character to be checked
 * @return TRUE if the character is a space, FALSE if it isn't
 * @note space is defined as : " " \\t \\n \\v \\f \\r
*/
t_bool	ft_isspace(char c);

/**
 * @brief Function that checks the command name is a builtin
 * @param str string to be checked
 * @return TRUE if the command is a builtin, FALSE if it isn't
*/
t_bool	ft_isbuiltin(char *str);

/**
 * @brief Function that prints the list of commands and files
 * @param input list to be printed
 * Example:
 * @code
 * --------------------
 *		type: 2
 * 		node: ls
 * 	path: /bin/ls
 * --------------------
 * @endcode
*/
void	print_list(t_input *input);

//envp utils

/**
 * @brief Function that returns the index of a string in a matrix
 * @param envp matrix to be checked
 * @param to_find string to be found
 * @return the index of the string in the matrix or -1 if it isn't found
*/
int		find_in_env(char **envp, char *to_find);

/**
 * @brief Function that searches for a string in a matrix and returns the value
 * @param envp matrix to be checked
 * @param to_find string to be found
 * @return a copy of the string in the matrix or NULL if it isn't found
*/
char	*get_env_value(char **envp, char *to_find);

/**
 * @brief Function that prints a matrix
 * @param mtx matrix to be printed
 * @return TRUE if the matrix is printed, FALSE if it isn't
*/
t_bool	print_matrix(char **mtx);

/**
 * @brief Function that returns the length of a matrix
 * @param matrix matrix to be checked
 * @return the length of the matrix
*/
int		ft_matrix_len(char **matrix);

void	ft_builtin_error(char *com);
int		ft_isinset(char c, char *set);
int		check_access(char *file, t_type type, t_data *data);
void	close_fds(t_pipex *comm);

//math utils

int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	print_intmatrix(int **matrix, int rows, int cols);
t_bool	ft_atoibool(char *str, unsigned int *nbr, int i, int sign);

t_bool	ft_iscmd(t_input *input, t_data *data);

void	free_parser(t_parser *prs);
char	**ft_neosplitarg(char *str);

char	*ft_input2str(t_input **input);
t_bool	file_check(char *line, t_data *data);
t_pipex	comm_error(t_data **data);
char	*ft_rowgen(char *str);
void	sort_matrix(char ***mtx);

//quotes
void	quote_start(t_bool *quote, char c, char *quote_type);
t_bool	check_quote(char *tmp, char quote_type, t_type type, int index);

//accounting

/**
 * @brief Function that returns the number of commands in the list
*/
int		nbr_cmds(t_data *data);

/**
 * @brief Function that returns the number of commands that are not builtins
*/
int		nbr_cmds_notb(t_data *data);

#endif
