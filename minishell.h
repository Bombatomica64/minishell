/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/08 18:34:08 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "./ft_printf/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./ft_printf/get_next_line_bonus.h"
# include "./pipex/pipex.h"
# include "./utils/utils.h"

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

#endif
