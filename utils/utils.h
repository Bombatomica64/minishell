/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:11:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/20 12:11:55 by lmicheli         ###   ########.fr       */
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
	FALSE,
	TRUE,
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
	char			*node;
	char			*path;
	t_type			type;
	struct s_input	*prev;
	struct s_input	*next;
}	t_input;

typedef struct s_pipex_data
{
	char	**cmds; //name
	char	**files; //name
	int		fds[2]; // 2 fd (i/o)
}	t_pi_d;

typedef struct s_pipex
{
	char	***cmd;
	char	**path;
	char	*filein;
	char	*fileout;
	int		fd_in;
	int		fd_out;
}				t_pipex;

typedef struct s_data
{
	int		nb_total; // total number of commands and files in input
	int		nb_files; // number of files
	int		nb_cmds; // number of commands
	int		fd_in; // input file descriptor
	int		fd_out; // output file descriptor
	int		original_stdin;
	int		original_stdout;
	char	*directory;
	char	**envp;
	t_bool	input_found; // true if there is an input file, false if there isn't
	t_pi_d	in_p; // pipex input data
	t_pipex	pipex; // pipex data
	t_input	*input; // array of commands and files
}	t_data;

void	free_matrix(char **matrix);
void	ft_error(const char *str, t_error error, int errnbr);
t_bool	ft_malloc_err(void *ptr, char *str);
void	ft_freenclose(t_data *data);

// list functions
t_input	*ft_inputnew(char *node, char *path, t_type type);
void	ft_inputclear(t_input **lst);
void	ft_inputadd_back(t_input **lst, t_input *news);
void	ft_inputadd_front(t_input **lst, t_input *news);
t_input	*ft_inputlast(t_input **stack);

/**
 * @brief: funtion outputs a copy of a string allocated with no quoutes
 * @param: str, string to be copied
 * @param: start, start index of the string
 * @param: end, end index of the string
 * @return: a copy of the string without quotes
*/
char	*ft_strncpy_noquote(char *str, int start, int end);
char	*ft_strjoin_2free(char *old_str, char *buf);
char	**matrix_dup(char **matrix);
t_bool	is_not_limiter(char c);
void	skip_spaces(char **str);

#endif