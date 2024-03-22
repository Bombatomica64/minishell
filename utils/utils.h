/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:11:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 12:49:59 by mruggier         ###   ########.fr       */
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
# pragma once

typedef enum e_error
{
	NO_PATH,
	DUP,
	EXECVE,
	PIPE,
	FORK,
	ACCESS,
	WRITE,
	NO_EXST,
	OPEN,
	BUILTIN,
	DIR
}	t_error;

typedef struct s_quote
{
	t_bool	open;
	char	type;
}	t_quote;

typedef enum e_type
{
	INPUT = 0,// < file in input
	TRUNC = O_TRUNC,// > file, rewrites the lines in  the output file
	APPEND = O_APPEND,// >> file, add more lines in the output file
	COMMAND,//command to be executed with execve
	HEREDOC,// << limiter, terminal input until limiter
	BUILT_IN,//command to be executed without execve
	FINISH = 69// end of the list
}	t_type;

typedef struct s_parser
{
	char	*tmp;
	char	*tmp_path;
	t_type	tmp_type;
}	t_parser;

typedef struct s_input
{
	char			*node; // command or file name
	char			*path; // path of the command or file
	t_type			type; // type of the node
	struct s_input	*prev; // previous node
	struct s_input	*next; // next node
}	t_input;

// pipex input data
typedef struct s_pipex
{
	char	**cmd; // command in matrix status
	char	*path; // command path
	char	*filein; // input file name
	char	*fileout; // output file name
	int		fd_in; // input file descriptor
	int		fd_out; // output file descriptor
	char	*connector; // the connector to the next command (NULL, |, &&, ||)
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
	int		original_stdin; // dupped stdin
	int		original_stdout; // dupped stdout
	int		error_codes; // sum of the error codes
	int		**fd; // pipe
	int		last_pipe; // last pipe
	int		cmd_nbr; // number of commands
	int		pipe_nbr; // number of pipes
	t_bool	in_pipe; // if the command is in a pipe
	char	**envp; // current environment
	char	*home; // home directory (~)
	char	*pwd; // current directory
	t_input	*input; // list of commands and files
	t_bonus	*bonus; // list of commands seprated by && and ||
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

/**
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
char	*ft_strncpy_noquote(char *str, int start, int end);

// string functions

/**
 * Finds the index of the first occurrence of a character in a string.
 *
 * @param str The string to search in.
 * @param c The character to find.
 * @return The index of the first occurrence 
 * of the character, or -1 if not found.
 */
int		find_first(char *str, char c);

/**
 * Concatenates two strings and frees the first string.
 *
 * @param line The first string to be concatenated.
 * @param buff The second string to be concatenated.
 * @param index The index at which to stop concatenating.
 * @return The concatenated string, or NULL if memory allocation fails.
 */
char	*strjoin_n_free1(char *line, char *buff, int index);

/**
 * @brief Function that mimics the behaviour of strjoin but frees both strings
 * @param old_str string to join to , will be freed
 * @param buf string that will be joined, will be freed 
 * @return a new string with the joined strings
 * @note both strings will be freed
 * @note the new string will be allocated
 */
int		ft_strlen_noquote(char *str);

/**
 * @brief Function that mimics the behaviour of strjoin but frees both strings
 * @param old_str string to join to , will be freed
 * @param buf string that will be joined, will be freed 
 * @return a new string with the joined strings
 * @note both strings will be freed
 * @note the new string will be allocated
 */

char	*ft_strjoin_2free(char *old_str, char *buf);

/**
 * @brief Function that allocates a copy of a matrix and returns it
 * @param matrix matrix to be copied
 * @return a copy of the matrix
 */

char	*ft_strncpy(char *str, int start, int end);

/**
 * @brief Function that allocates a copy of a matrix and returns it
 * @param matrix matrix to be copied
 * @return a copy of the matrix
 */

char	**matrix_dup(char **matrix);

/**
 * @brief Function that checks if a character is a limiter
 * @param c character to be checked
 * @n
 * @return TRUE if the character is a limiter, FALSE if it isn't
 */
t_bool	ft_islimiter(char c);

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
 * @brief Function that checks if a character is a quote
 * @param c character to be checked
 * @return TRUE if the character is a quote, FALSE if it isn't
 * @note quote is defined as " or '\''
*/
t_bool	ft_isquote(char c);

/**
 * @brief Function that checks the command name is a builtin
 * @param str string to be checked
 * @return TRUE if the command is a builtin, FALSE if it isn't
*/
t_bool	ft_isbuiltin(char *str);

/**
 * @brief adds the heredoc functionality to the program
 * @param limiter string that will be used as a limiter
 * @param data data envp to be passed to the function
 * @param pid pid to be passed to the function
 * @return fd with the file descriptor of the pipe fd[0]
*/
int		heredoc_creat(char *limiter, t_data *data, pid_t pid);

/**
 * Removes leading and trailing characters specified in
 * #include "str_utils2.h"
the 'set' parameter from the string 's1'.
 * Additionally, frees the memory allocated for 's1'.
 *
 * @param s1 The string to be trimmed and freed.
 * @param set The set of characters to be removed from the string.
 * @return A pointer to the trimmed string, or NULL if memory allocation fails.
 */
char	*ft_strtrimfree(char *s1, char *set, int *trimmed);

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

// mtx functions

/**
 * @brief Function that returns the number of arguments in a command string
 * @param str string to be checked
 * @param i index of the string
 * @param nbr_args number of arguments
 * @return the number of arguments in the string
*/
int		ft_arg_count(char *str, int i, int nbr_args);

char	*ft_rowgen(char *str);

/**
 * @brief Function that allocates a new string with the argument
 * @param str string to be checked
 * @param c character used as a check for quotes
 * @param i index of the new string
 * @param j index of the old string
 * @return a new string with the length of the argument
*/
char	*ft_rowfill(char *str, int *j, int i);

/**
 * @brief Function that creates the matrix of a command and arguments
 * @param str string to be splitted
 * @return the matrix with command and arguments
*/
char	**ft_splitarg(char *str);

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

/**
 * @brief Function that copies a string until len and allocates it
 * @param str string to be copied
 * @param len length of the string to be copied
 * @return a copy of the string until len
 * @note the new string will be allocated
*/
char	*ft_strndup(char *str, int len);

/**
 * Concatenates two strings and returns the result.
 * If the first string is NULL, it is treated as an empty string.
 * If either string is NULL, the function returns NULL.
 *
 * @param old_str The first string to concatenate.
 * @param buf The second string to concatenate.
 * @return The concatenated string, or NULL if an error occurred.
 */
char	*ft_strjoin_2(char *old_str, char *buf);

char	*free_strrchr(char *str, char c, int **offset);

char	*join_char(char *str, char c);

void	ft_builtin_error(char *com);

int		ft_isinset(char c, char *set);

int		check_access(char *file, t_type type, t_data *data);

//math utils

int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	print_intmatrix(int **matrix, int rows, int cols);
t_bool	ft_atoibool(char *str, int *nbr);

t_bool	ft_iscmd(t_input *input, t_data *data);
char	*cut_string(int len, char *str);
int		find_last(char *str, char c);

void	free_parser(t_parser *prs);
char	**ft_neosplitarg(char *str);

char	*ft_input2str(t_input **input);

#endif