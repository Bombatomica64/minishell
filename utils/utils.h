/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:11:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/09 12:45:13 by gduranti         ###   ########.fr       */
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

void	free_matrix(char **matrix);
void	ft_error(const char *str, t_error error);

#endif