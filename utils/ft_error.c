/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/20 11:16:43 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_malloc_err(void *ptr, char *str)
{
	if (!ptr)
	{
		dup2(2, 1);
		ft_printf("Error: Unexpected malloc behaviour at %s\n", str);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_error(const char *str, t_error error, int errnbr)
{
	dup2(2, 1);
	if (error == NO_PATH)
		ft_printf("pipex: command not found: %s\n", str);
	else if (error == DUP)
		ft_printf("%s failed to duplicate file descriptor\n", str);
	else if (error == EXECVE)
		perror("pipex: execve error");
	else if (error == PIPE)
		perror("pipex: pipe error");
	else if (error == FORK)
		perror("pipex: fork error");
	else if (error == ACCESS)
		perror("pipex: access error");
	else if (error == OPEN)
		perror("pipex: open error");
	else
		perror("pipex: unknown error");
	exit(errnbr);
}
// Path: utils/utils.h