/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:13:02 by marvin            #+#    #+#             */
/*   Updated: 2024/02/13 21:13:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

#include <fcntl.h>
#include <unistd.h>

typedef enum e_bool
{
    FALSE = 0,
    TRUE = 1
} t_bool;

typedef enum e_io
{
	INPUT = 0, // < file in input
	HEREDOC,   // << limiter, terminal input until limiter
	TRUNC = O_TRUNC,     // > file, rewrites the lines in  the output file
	APPEND = O_APPEND    // >> file, add more lines in the output file

}	t_io;

typedef struct s_file
{
	int		fd;
	t_io	type;
	char	*name; // file name without the type (> >> < <<)

}	t_file;

typedef struct s_cmd
{
	char	*name;

}	t_cmd;

typedef struct s_input
{
	//int		i; // position of the command or file [1: grep e] {2: < file 2}
	t_cmd	cmd; // command, set to NULL if it's a file
	t_file	file; // file, set to NULL if it's a command
	t_bool	is_a_file; // true if it's a file, false if it's a command

}	t_input;

typedef struct s_data
{
	int		nb_total; // total number of commands and files in input
	int		nb_files; // number of files
	int		nb_cmds; // number of commands
	int		fd_in; // input file descriptor
	int		*fd_out; // all output file descriptor
	t_input	*input; // array of commands and files

}	t_data;

#endif