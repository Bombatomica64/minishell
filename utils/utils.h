/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:11:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/23 10:49:29 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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
# include "../ft_printf/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../ft_printf/get_next_line_bonus.h"

typedef enum e_bool
{
	FALSE, // 0
	TRUE, // 1
	ERROR = -1
}	t_bool;

typedef enum e_error
{
	NO_PATH,
	DUP,
	EXECVE,
	PIPE,
	FORK,
	ACCESS,
	OPEN
}	t_error;

typedef enum e_type
{
	INPUT = 0,// < file in input
	HEREDOC,// << limiter, terminal input until limiter
	COMMAND,//command to be executed with execve
	BUILT_IN,//command to be executed without execve
	TRUNC = O_TRUNC,// > file, rewrites the lines in  the output file
	APPEND = O_APPEND// >> file, add more lines in the output file
}	t_type;

typedef struct s_input
{
	char			*node; // command or file name
	char			*path; // path of the command or file
	t_type			type; // type of the node
	struct s_input	*prev; // previous node
	struct s_input	*next; // next node
}	t_input;

typedef struct s_pipex_data
{
	char	**cmds; //name
	char	**files; //name
	int		fds[2]; // 2 fd (i/o)
}	t_pi_d;

// pipex input data
typedef struct s_pipex
{
	char	***cmd; // array of matrix of commands
	char	**path; // array of paths
	char	*filein; // input file name
	char	*fileout; // output file name
	int		fd_in; // input file descriptor
	int		fd_out;// output file descriptor
}				t_pipex;

typedef struct s_data
{
	int		nb_total; // total number of commands and files in input
	int		nb_files; // number of files
	int		nb_cmds; // number of commands
	int		fd_in; // input file descriptor
	int		fd_out; // output file descriptor
	int		original_stdin; // dupped stdin
	int		original_stdout; // dupped stdout
	char	*directory; // current working directory
	char	**envp; // current environment
	char	*home; // home directory (~)
	t_bool	input_found; // true if there is an input file, false if there isn't
	t_pi_d	in_p; // pipex input data
	t_pipex	pipex; // pipex data
	t_input	*input; // list of commands and files
}	t_data;

// free and error functions

/**
 * @brief Function that frees a string matrix
 * @param matrix matrix to be freed
*/
void	free_matrix(char ***matrix);

/**
 * @brief Function that outputs an error message, 
 * frees the data and exits current command
 * @param str, string to help identify the error
 * @param error, type of error
 * @param errnbr, exit error number
 * @param data, data to be freed
 * @return void
*/
void	ft_error(const char *str, t_error error, int errnbr, t_data *data);

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
void	freenclose(t_data *data);

// list functions

/**
 * @brief Function that creates a new node of t_input type
 * @param node command or file name
 * @param path path of the command or file
 * @param type type of the node
 * @return a new node of t_input type
*/
t_input	*ft_inputnew(char *node, char *path, t_type type);

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
 * @param stack list to be checked
 * @return A pointer to the last node of the list
*/
t_input	*ft_inputlast(t_input **stack);

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
*/
void	skip_spaces(char **str);

/**
 * @brief Function that checks if a character is a space
 * @param c character to be checked
 * @return TRUE if the character is a space, FALSE if it isn't
 * @note space is defined as ' ', '\t', '\n', '\v', '\f', '\r'
*/
t_bool	ft_isspace(char c);

/**
 * @brief Function that checks if a character is a quote
 * @param c character to be checked
 * @return TRUE if the character is a quote, FALSE if it isn't
 * @note quote is defined as '"' or '\''
*/
t_bool	ft_isquote(char c);

/**
 * @brief adds the heredoc functionality to the program
 * @param limiter string that will be used as a limiter
 * @note the function will create a temp file with everything 
 * that is written until the limiter 
*/
void	heredoc_creat(char *limiter);
void	print_list(t_input *input);

//envp utils

/**
 * @brief Function that returns the index of a string in a matrix
 * @param envp matrix to be checked
 * @param to_find string to be found
 * @return the index of the string in the matrix or -1 if it isn't found
*/
int		find_in_env(char **envp, char *to_find);
char	*get_env_value(char **envp, char *to_find);

// mtx functions
int		ft_arg_count(char *str, char c, int i, int nbr_args);
char	*ft_rowfill(char **str, char c, int i);
char	**ft_splitarg(char *str);
t_bool	ft_printmtx(char **mtx);

#endif