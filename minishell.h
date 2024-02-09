/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/09 18:37:34 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "pipex/pipex.h"

// typedef enum e_error
// {
// 	NO_PATH,
// 	DUP,
// 	EXECVE,
// 	PIPE,
// 	FORK,
// 	ACCESS,
// 	OPEN
// }	t_error;

typedef enum e_io
{
	INPUT = 0, // < file
	HEREDOC,   // << limiter
	TRUNC,     // > file rewrites
	APPEND     // >> file add more lines

}	t_io;

typedef struct s_file
{
	int		fd;
	t_io	type;
	char	*file;

}	t_file;



#endif
