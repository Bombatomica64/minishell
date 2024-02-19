/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:11:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/19 15:23:11 by gduranti         ###   ########.fr       */
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

typedef	enum e_bool
{
	TRUE,
	FALSE,
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

typedef enum e_io
{
	INPUT = 0,// < file in input
	HEREDOC,// << limiter, terminal input until limiter
	TRUNC = O_TRUNC,// > file, rewrites the lines in  the output file
	APPEND = O_APPEND// >> file, add more lines in the output file
}	t_io;

typedef struct s_file
{
	int		fd;
	t_io	type;
	char	*name; // file name without the type (> >> < << UwU)
}	t_file;

typedef struct s_cmd
{
	char	*name;
	char	*path;
}	t_cmd;

typedef struct s_input
{
	//int		i; // position of the command or file [1: grep e] {2: < file 2}
	t_cmd	cmd; // command, set to NULL if it's a file
	t_file	file; // file, set to NULL if it's a command
	t_bool	is_a_file; // true if it's a file, false if it's a command
}	t_input;

typedef struct s_pipex_data
{
	char	**cmds; //name
	char	**files; //name
	int		fds[2]; // 2 fd (i/o)
}	t_pi_d;

typedef struct s_data
{
	int		nb_total; // total number of commands and files in input
	int		nb_files; // number of files
	int		nb_cmds; // number of commands
	int		fd_in; // input file descriptor
	int		fd_out; // output file descriptor
	int		original_stdin;
	int		original_stdout;
	t_bool	input_found; // true if there is an input file, false if there isn't
	t_pi_d	in_p; // pipex data
	t_input	*input; // array of commands and files
}	t_data;

void	free_matrix(char **matrix);
void	ft_error(const char *str, t_error error);
t_bool	ft_malloc_err(void *ptr, char *str);
void	ft_freenclose(t_data *data);

#endif